// GLDemoView.cpp : implementation of the CGLDemoView class
//

#include "stdafx.h"

#include "resource.h"

#include "GLDemoView.h"

#include <cmath>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace OpenGLui
{
	/////////////////////////////////////////////////////////////////////////////
	// CGLDemoView

	IMPLEMENT_DYNCREATE(CGLDemoView, CView)

	BEGIN_MESSAGE_MAP(CGLDemoView, CView)
		//{{AFX_MSG_MAP(CGLDemoView)
		ON_WM_SIZE()
		ON_WM_TIMER()
		ON_WM_ERASEBKGND()
		ON_WM_CREATE()
		ON_WM_DESTROY()
		ON_WM_LBUTTONDOWN()
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONUP()
		//}}AFX_MSG_MAP
		ON_COMMAND(ID_ROTATE, &CGLDemoView::OnRotate)
		ON_UPDATE_COMMAND_UI(ID_ROTATE, &CGLDemoView::OnUpdateRotate)
		ON_COMMAND(ID_PAN, &CGLDemoView::OnPan)
		ON_UPDATE_COMMAND_UI(ID_PAN, &CGLDemoView::OnUpdatePan)
		ON_COMMAND(ID_ZOOM_IN, &CGLDemoView::OnZoomIn)
		ON_COMMAND(ID_ZOOM_OUT, &CGLDemoView::OnZoomOut)
		// Standard printing commands
		ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CGLDemoView construction/destruction

	CGLDemoView::CGLDemoView()
	{
		m_pOpenGL = &m_OpenGL3D;
		hDIB = NULL;
		m_palDIB = new CPalette;

		m_bSaveRectBMP = FALSE;
		m_nSaveBMPFlag = BMPCLIENT;

		m_bBox  = true;
		m_bAxis = true;
	}

	CGLDemoView::~CGLDemoView()
	{
		if (hDIB != NULL)
		{
			::GlobalUnlock(hDIB);
			::GlobalFree(hDIB);
			hDIB = NULL;
		}
		if (m_palDIB != NULL)
		{
			delete m_palDIB;
			m_palDIB = NULL;
		}
	}

	BOOL CGLDemoView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: Modify the Window class or styles here by modifying
		//  the CREATESTRUCT cs
		cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		return CView::PreCreateWindow(cs);
	}

	void CGLDemoView::PrintDIB(CDC* pDC)
	{
		if (hDIB == NULL || m_palDIB == NULL) return;

		int cxPage = pDC->GetDeviceCaps(HORZRES);
		int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
		int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

		char* pDIB = (char*)::GlobalLock(hDIB);
		int cxDIB = (int)  ::DIBWidth(pDIB);
		int cyDIB = (int)  ::DIBHeight(pDIB);
		if (cxDIB <= 0 || cyDIB <= 0) return;

		RECT rcDst, rcDIB;
		rcDIB.top = 0;
		rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		rcDst.left = 0;
		rcDst.top = 0;
		rcDst.right = cxPage;
		rcDst.bottom = (int)(1.0 * cyDIB * cxPage * cyInch / cxDIB / cxInch);

		::PaintDIB(pDC->m_hDC, &rcDst, (HDIB)hDIB, &rcDIB, (HPALETTE)m_palDIB->m_hObject);
	}

	/////////////////////////////////////////////////////////////////////////////
	// CGLDemoView drawing

	void CGLDemoView::OnDraw(CDC* pDC)
	{
		if (pDC->IsPrinting()) 		PrintDIB(pDC);
		else						m_pOpenGL->OpenGLRendering();
	}

	/////////////////////////////////////////////////////////////////////////////
	// CGLDemoView printing

	BOOL CGLDemoView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		pInfo->SetMaxPage(1);
		m_nSaveBMPFlag = BMPCLIENT;
		return DoPreparePrinting(pInfo);
	}

	void CGLDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: add extra initialization before printing
	}

	void CGLDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: add cleanup after printing
	}

	void CGLDemoView::GetDIB()
	{
		if (hDIB != NULL)
		{
			::GlobalUnlock(hDIB);
			::GlobalFree(hDIB);
			hDIB = NULL;
		}
		switch (m_nSaveBMPFlag)
		{
		case BMPWINDOW:
			hDIB = ::CopyWindowToDIB(AfxGetApp()->m_pMainWnd->GetSafeHwnd(), (WORD)m_nSaveBMPFlag);
			break;
		case BMPCLIENT:
			hDIB = ::CopyWindowToDIB(GetSafeHwnd(), (WORD)m_nSaveBMPFlag);
			break;
		case BMPRECT:
			hDIB = ::CopyRectToDIB(GetSafeHwnd(), &m_Rect);
			break;
		}
	}

	void CGLDemoView::FreeDIB()
	{
		::GlobalUnlock(hDIB);
		::GlobalFree(hDIB);
		hDIB = NULL;
	}

	void CGLDemoView::OnFilePrint()
	{
		m_nSaveBMPFlag = BMPCLIENT;
		GetDIB();

		CView::OnFilePrint();
	}

	void CGLDemoView::OnFilePrintPreview()
	{
		m_nSaveBMPFlag = BMPCLIENT;
		GetDIB();

		CView::OnFilePrintPreview();
	}

	void CGLDemoView::SaveToBMP()
	{
		GetDIB();
		if (hDIB == NULL)
		{
			MessageBox("HDIB handle is NULL, save abort !!!");
			return;
		}
		CFileDialog  dilg(FALSE, NULL, "*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");

		dilg.m_ofn.lpstrTitle = "Save Bitmap Dialog";
		if (dilg.DoModal() != IDOK)
		{
			FreeDIB();
			return;
		}
		CString pszPathName = dilg.GetPathName();

		CFile file;
		CFileException fe;

		if (!file.Open(pszPathName, CFile::modeCreate |
			CFile::modeReadWrite | CFile::shareExclusive, &fe))
		{
			FreeDIB();
			MessageBox("Cannot save the BMP file <" + pszPathName + "> !!!");
			return;
		}

		BOOL bSuccess = FALSE;
		TRY
		{
			BeginWaitCursor();
			bSuccess = ::SaveDIB(hDIB, (HANDLE)file.m_hFile);
			file.Close();
		}
			CATCH(CException, eSave)
		{
			file.Abort(); // will not throw an exception
			EndWaitCursor();
			FreeDIB();
			MessageBox("Cannot save the BMP file <" + pszPathName + "> !!!");
			return;
		}
		END_CATCH
			EndWaitCursor();
		if (!bSuccess)
		{
			FreeDIB();
			MessageBox("Cannot save the BMP file <" + pszPathName + "> !!!");
		}

		FreeDIB();
	}

	/////////////////////////////////////////////////////////////////////////////
	// CGLDemoView diagnostics

#ifdef _DEBUG
	void CGLDemoView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CGLDemoView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}
#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CGLDemoView message handlers

	void CGLDemoView::OnSize(UINT nType, int cx, int cy)
	{
		CView::OnSize(nType, cx, cy);

		m_pOpenGL->OpenGLSize(cx, cy);
	}

	void CGLDemoView::OnTimer(UINT nIDEvent)
	{
		m_pOpenGL->OpenGLTimer((CRotateType)nIDEvent);

		CView::OnTimer(nIDEvent);
	}

	BOOL CGLDemoView::OnEraseBkgnd(CDC* pDC)
	{
		COLORREF tmp = pDC->GetBkColor();

		tmp = 12356748;

		return FALSE;
	}

	int CGLDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)		return -1;

		m_pOpenGL->InitOpenGL(GetSafeHwnd());

		return 0;
	}

	void CGLDemoView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (!m_bSaveRectBMP)		m_pOpenGL->LButtonDown(point);
		else
		{
			c_down = point;
			c_last = point;
			Zoom_in_First = point;        //
			SetCapture();                 //
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE)); //
		}

		CView::OnLButtonDown(nFlags, point);
	}

	void CGLDemoView::OnMouseMove(UINT nFlags, CPoint point)
	{
		if (!m_bSaveRectBMP)		m_pOpenGL->MouseMove(nFlags, point);
		else if (GetCapture() == this)
		{
			CClientDC dc(this);
			OnPrepareDC(&dc);
			dc.DPtoLP(&point);
			//
			CRect rect(c_down.x, c_down.y, c_last.x, c_last.y);
			rect.NormalizeRect();
			dc.DrawFocusRect(rect);
			rect.SetRect(c_down.x, c_down.y, point.x, point.y);
			rect.NormalizeRect();
			dc.DrawFocusRect(rect);
			c_last = point;
		}

		CView::OnMouseMove(nFlags, point);
	}

	void CGLDemoView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		if (!m_bSaveRectBMP)
		{
			//m_pOpenGL->LButtonUp(point);
			m_pOpenGL->LButtonUp();
		}
		else
		{
			Zoom_in_Last = point;           //
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW)); //
			ReleaseCapture();               //
			m_bSaveRectBMP = FALSE;
			m_Rect.left = Zoom_in_First.x + 1;
			m_Rect.top = Zoom_in_First.y + 1;
			m_Rect.right = Zoom_in_Last.x - 1;
			m_Rect.bottom = Zoom_in_Last.y - 1;
			c_down.x = c_down.y = 0;
			c_last.x = c_last.y = 0;
			SaveToBMP();
		}

		CView::OnLButtonUp(nFlags, point);
	}

	void CGLDemoView::OnDestroy()
	{
		m_pOpenGL->DestroyOpenGL();

		CView::OnDestroy();
	}

	BOOL CGLDemoView::ConfirmOverWrite()
	{
		if (m_pOpenGL->m_DataGroup < G4D)
		{
			if (m_OpenGL3D.m_p3D)
			{
				int yn = AfxMessageBox("Are you sure to replace the current map using new data?", MB_YESNO);
				if (yn == IDNO)
					return FALSE;
			}
		}
		else
		{
			if (m_OpenGL4D.m_p4D)
			{
				int yn = AfxMessageBox("Are you sure to replace the current map using new data?", MB_YESNO);
				if (yn == IDNO)
					return FALSE;
			}
		}

		return TRUE;
	}

	void CGLDemoView::Show3DForm()
	{
		if (m_pOpenGL->m_pDS && m_pOpenGL->m_pDS->m_Rotate != NONE)
			m_pOpenGL->KillOpenGLTimer(m_pOpenGL->m_pDS->m_Rotate);
		if (m_pOpenGL->m_DataGroup == G4D)
		{
			m_pOpenGL->DestroyOpenGL();
			m_pOpenGL = &m_OpenGL3D;
			m_pOpenGL->InitOpenGL(GetSafeHwnd());
		}
	}

	void CGLDemoView::Load3DData(FILE* fp, char type)
	{
		if (!ConfirmOverWrite())	   return;

		m_OpenGL3D.Load3DData(fp, type);
		Show3DForm();
	}

	void CGLDemoView::LoadPlot3Ddata(float* pXgrid, float* pYgrid, float* pArray, int row, int col)
	{
		if (!ConfirmOverWrite())	   return;

		m_OpenGL3D.Load3dArray(pXgrid, pYgrid, pArray, row, col);

		Show3DForm();
	}

	void CGLDemoView::Show4DForm()
	{
		if (m_pOpenGL->m_pDS && m_pOpenGL->m_pDS->m_Rotate != NONE)
			m_pOpenGL->KillOpenGLTimer(m_pOpenGL->m_pDS->m_Rotate);
		if (m_pOpenGL->m_DataGroup < G4D)
		{
			m_pOpenGL->DestroyOpenGL();
			m_pOpenGL = &m_OpenGL4D;
			m_pOpenGL->InitOpenGL(GetSafeHwnd());
		}
	}

	void CGLDemoView::Load4DData(FILE* fp, char type)
	{
		if (!ConfirmOverWrite())
			return;

		m_OpenGL4D.Load4DData(fp, type);
		Show4DForm();
	}

	void CGLDemoView::OnRotate()
	{

		if (m_pOpenGL->m_pDS)
		{
			m_pOpenGL->m_pDS->m_Move = RANDROTAT;
			InvalidateRect(NULL, FALSE);
		}
	}

	void CGLDemoView::OnUpdateRotate(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		if (m_pOpenGL->m_pDS)
		{
			if (m_pOpenGL->m_pDS->m_Move == RANDROTAT)
			{
				InvalidateRect(NULL, FALSE);
				pCmdUI->SetCheck(1);
			}
			else
			{
				pCmdUI->SetCheck(0);
			}
		}
	}

	void CGLDemoView::OnPan()
	{
		if (m_pOpenGL->m_pDS)
		{
			m_pOpenGL->m_pDS->m_Move = MOVE;
			InvalidateRect(NULL, FALSE);
		}
	}

	void CGLDemoView::OnUpdatePan(CCmdUI *pCmdUI)
	{
		// TODO: Add your command update UI handler code here
		if (m_pOpenGL->m_pDS)
		{
			if (m_pOpenGL->m_pDS->m_Move == MOVE)
			{
				InvalidateRect(NULL, FALSE);
				pCmdUI->SetCheck(1);
			}
			else
			{
				pCmdUI->SetCheck(0);
			}
		}
	}

	void CGLDemoView::OnZoomIn()
	{

		if (m_pOpenGL->m_pDS)
		{
			if (m_pOpenGL->m_pDS)
				m_pOpenGL->m_pDS->m_zScale = m_pOpenGL->m_pDS->m_yScale
				= m_pOpenGL->m_pDS->m_xScale
				= m_pOpenGL->m_pDS->m_zScale*1.1f;
			InvalidateRect(NULL, FALSE);
		}
	}

	void CGLDemoView::OnZoomOut()
	{

		if (m_pOpenGL->m_pDS)
		{
			if (m_pOpenGL->m_pDS)
				m_pOpenGL->m_pDS->m_zScale = m_pOpenGL->m_pDS->m_yScale
				= m_pOpenGL->m_pDS->m_xScale
				= m_pOpenGL->m_pDS->m_zScale*0.9f;
			InvalidateRect(NULL, FALSE);
		}
	}


	void CGLDemoView::SetupScene(Point3D dBottomCenter, Point3D dTopCenter, double dBottomRadius, double dTopRadius, 
		int nSlices, int nStacks, Point3D dTestPt, Point3D dFoundPt)
	{
		double cylHeight = sqrt(
			(dTopCenter.x - dBottomCenter.x)*(dTopCenter.x - dBottomCenter.x) +
			(dTopCenter.y - dBottomCenter.y)*(dTopCenter.y - dBottomCenter.y) +
			(dTopCenter.z - dBottomCenter.z)*(dTopCenter.z - dBottomCenter.z)
		);

		m_pOpenGL->SetCylinderParams(dBottomCenter, dTopCenter, dBottomRadius, nSlices, nStacks);
		m_pOpenGL->SetTestPointParams(dTestPt, 0.02);
		m_pOpenGL->SetEndPointParams(dFoundPt, 0.02);

#define M_PI 3.14159

		float* pXvals = new float[2 * nStacks];
		float* pYvals = new float[2 * nSlices];
		float* pZvals = new float[2 * nStacks*nSlices];

		//float thetaStep = (float)2*M_PI / nSlices;
		float xstep = (float)cylHeight / (nStacks - 1);
		float maxRadius = dBottomRadius > dTopRadius ? (float)dBottomRadius : (float)dTopRadius;
		float ystep = 2 * maxRadius / (nSlices - 1);
		float rstep = (float)abs((dTopRadius - dBottomRadius) / nSlices);

		for (int j = 0; j < nSlices; j++) {
			pYvals[j] = -maxRadius + j*ystep;
		}
		for (int i = 0; i < nStacks; i++) {
			pXvals[i] = dBottomCenter.x + i*xstep;

			double stackRadius = 0.0;
			stackRadius = dBottomRadius < dTopRadius ? dBottomRadius + i*rstep : dBottomRadius - i*rstep;

			for (int j = 0; j < nSlices; j++) {
				abs(pYvals[j]) > stackRadius ?
					(pZvals[nSlices * i + j] = 0.0f) :
					(pZvals[nSlices * i + j] = (float)sqrt(stackRadius*stackRadius - pYvals[j] * pYvals[j]));
			}
		}

		m_OpenGL3D.Load3dArray(pXvals, pYvals, pZvals, nSlices, nStacks);

		m_pOpenGL->m_pDS->m_Move = RANDROTAT;
		//m_pOpenGL->m_pDS->m_MapType = GRID;

		if (m_sMapType == "Surface") {
			m_pOpenGL->m_pDS->m_MapType = SURFACE;
		}
		else if (m_sMapType == "Grid") {
			m_pOpenGL->m_pDS->m_MapType = GRID;
		}
		else {
			m_pOpenGL->m_pDS->m_MapType = GRID;
		}
		m_pOpenGL->m_pDS->m_bBase = false;
		m_pOpenGL->m_pDS->m_bBorder = m_bBox;
		m_pOpenGL->m_pDS->m_bAxes = m_bAxis;
		m_pOpenGL->m_bMirror = false;
		m_pOpenGL->m_pDS->m_bSide = false;
		m_pOpenGL->m_pDS->m_BackCr.b = 0;
		m_pOpenGL->m_pDS->m_BackCr.g = 0.1f;
		m_pOpenGL->m_pDS->m_BackCr.r = 0.1f;
		m_pOpenGL->m_pDS->m_zRotat = -145.0f;
		m_pOpenGL->m_pDS->m_xScale = m_pOpenGL->m_pDS->m_yScale = m_pOpenGL->m_pDS->m_zScale = 0.8f;

		//m_pOpenGL->m_ptFoundPt
	}
}