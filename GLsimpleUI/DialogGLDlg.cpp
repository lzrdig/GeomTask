// DialogGLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AppMain.h"
#include "DialogGLDlg.h"
#include "CtrlDlg.h"

#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogGLDlg dialog

CDialogGLDlg::CDialogGLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogGLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogGLDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	m_hGLContext = NULL;
	m_GLPixelIndex = 0;


	m_xRotate = 0;
	m_yRotate = 0;
	m_Rotate = FALSE;

	m_ScaleX = 1.0f;
	m_ScaleY = 1.0f;
	m_ScaleZ = 1.0f;

	m_transX = 0.0f;
	m_transY = 0.0f;
	m_transZ = 0.0f;

	m_size = 1.5;
	m_exp = 9;

	m_RightButtonDown = FALSE;
	m_LeftButtonDown = FALSE;

	dBottomCenter = { 0,0,0 };
	dTopCenter = { 0,0,1 };
	dBottomRadius = 0.5;

	nSlices = 6;
	nStacks = 6;

	m_nGLcurListIndex = 0;
	m_nGLtotalNumOfLists = 10;
}

void CDialogGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogGLDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogGLDlg, CDialog)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CDialogGLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_COMMAND(ID_POPUP_ROTATE, OnPopupRotate)
	ON_COMMAND(ID_POPUP_SIZE_DECREASE, OnPopupSizeDecrease)
	ON_COMMAND(ID_POPUP_SIZE_INCREASE, OnPopupSizeIncrease)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogGLDlg message handlers

BOOL CDialogGLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	nSlices = 8;
	nStacks = 8;


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialogGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDialogGLDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		RenderScene();
		SwapBuffers(dc.m_ps.hdc);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDialogGLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CDialogGLDlg::SetWindowPixelFormat(HDC hDC)
{
PIXELFORMATDESCRIPTOR pixelDesc;

pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
pixelDesc.nVersion = 1;

pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | 
					PFD_SUPPORT_OPENGL |
					PFD_DOUBLEBUFFER |
					PFD_STEREO_DONTCARE;

pixelDesc.iPixelType = PFD_TYPE_RGBA;
pixelDesc.cColorBits = 32;
pixelDesc.cRedBits = 8;
pixelDesc.cRedShift = 16;
pixelDesc.cGreenBits = 8;
pixelDesc.cGreenShift = 8;
pixelDesc.cBlueBits = 8;
pixelDesc.cBlueShift = 0;
pixelDesc.cAlphaBits = 0;
pixelDesc.cAlphaShift = 0;
pixelDesc.cAccumBits = 64;
pixelDesc.cAccumRedBits = 16;
pixelDesc.cAccumGreenBits = 16;
pixelDesc.cAccumBlueBits = 16;
pixelDesc.cAccumAlphaBits = 0;
pixelDesc.cDepthBits = 32;
pixelDesc.cStencilBits = 8;
pixelDesc.cAuxBuffers = 0;
pixelDesc.iLayerType = PFD_MAIN_PLANE;
pixelDesc.bReserved = 0;
pixelDesc.dwLayerMask = 0;
pixelDesc.dwVisibleMask = 0;
pixelDesc.dwDamageMask = 0;

m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
if(m_GLPixelIndex==0) // Choose default
{
	m_GLPixelIndex = 1;
	if(DescribePixelFormat(hDC,m_GLPixelIndex,
		sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
	{
		return FALSE;
	}
}

if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc)==FALSE)
{
	return FALSE;
}

return TRUE;
}

BOOL CDialogGLDlg::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);

	if(m_hGLContext==NULL)
		return FALSE;

	if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)
		return FALSE;

	return TRUE;
}

int CDialogGLDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if(SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	
	if(CreateViewGLContext(hDC)==FALSE)
		return 0;

	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,
				 (float)GetGValue(color)/255.0f,
				 (float)GetBValue(color)/255.0f,
				 1.0);	

	//BuildList();

	

	DrawScene();
	

	//SetTimer(0,10,NULL);

	return 0;
}

void CDialogGLDlg::OnDestroy() 
{	
	CDialog::OnDestroy();

	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);

	if(m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}	

	glDeleteLists(1,m_nGLtotalNumOfLists);
}

void CDialogGLDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	GLsizei width,height;
	GLdouble aspect;

	width = cx;
	height = cy;

	if(cy==0)
		aspect = (GLdouble)width;
	else
		aspect = (GLdouble)width/(GLdouble)height;

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,aspect,1,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glDrawBuffer(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	
}

void CDialogGLDlg::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	// Position / translation / scale
	//glTranslated(m_transX, m_transY, m_transZ);
	glTranslated(0.0, 0.0, -8.0);
	glRotated(m_xRotate, 1.0, 0.0, 0.0);
	glRotated(m_yRotate, 0.0, 1.0, 0.0);
	glRotated(m_zRotate, 0.0, 0.0, 1.0);
	//glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);

	for(int i=1; i<m_nGLcurListIndex;i++)
		::glCallList(i);

	glPopMatrix();
}

void CDialogGLDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LeftButtonDown = TRUE;
	m_LeftDownPos = point;
	KillTimer(0);
	CDialog::OnLButtonDown(nFlags, point);
}

void CDialogGLDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_LeftButtonDown = FALSE;
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDialogGLDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_LeftButtonDown)
	{
		CSize rotate = m_LeftDownPos - point;
		m_LeftDownPos = point;

		m_yRotate -= rotate.cx;
		m_xRotate -= rotate.cy;

		//in case of move
		//m_transX -= 1.0f * (point.x - point.x) / m_width;
		//m_transY += 1.0f * (point.y - point.y) / m_height;

		InvalidateRect(NULL,FALSE);
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CDialogGLDlg::OnContextMenu(CWnd*, CPoint point)
{
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_DIALOG_GLDLG));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CDialogGLDlg::Rotate()
{
	m_yRotate -= 2;
	InvalidateRect(NULL,FALSE);
}

void CDialogGLDlg::OnTimer(UINT nIDEvent) 
{
	m_yRotate -= 3;
	m_xRotate -= 2;
	InvalidateRect(NULL,FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CDialogGLDlg::OnPopupRotate() 
{
	SetTimer(0,10,NULL);
}

void CDialogGLDlg::OnPopupSizeDecrease() 
{
	m_ScaleX /= 1.1f;
	m_ScaleY /= 1.1f;
	m_ScaleZ /= 1.1f;
	InvalidateRect(NULL,FALSE);
}

void CDialogGLDlg::OnPopupSizeIncrease() 
{
	m_ScaleX *= 1.1f;
	m_ScaleY *= 1.1f;
	m_ScaleZ *= 1.1f;
	InvalidateRect(NULL,FALSE);
}

void CDialogGLDlg::DrawScene()
{
	for (int i = 0; i<m_nGLcurListIndex; i++)
	{
		glDeleteLists(i, 1);
	}

	DrawCylinder();
	DrawAxis();
	DrawSphere(m_trgtPt, 0.1);
}

void CDialogGLDlg::DrawCube()
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	// Gouraud
	glShadeModel(GL_SMOOTH);

	m_nGLcurListIndex = 1;
	::glNewList(m_nGLcurListIndex, GL_COMPILE_AND_EXECUTE);

	glShadeModel(GL_SMOOTH);

	float x = m_size;
	float xt = 5.0f;

	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glColor3ub(255,0,0);
		glVertex3d( x,  x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, -x, x);
		glColor3ub(0,0,255);
		glVertex3d(-x, -x, x);
		glColor3ub(255,255,0);
		glVertex3d(-x,  x, x);
	glEnd();

	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,-1.0);
		glColor3ub(255,0,0);
		glVertex3d( -x,  x, -x);
		glColor3ub(0,255,0);
		glVertex3d( -x, -x, -x);
		glColor3ub(0,0,255);
		glVertex3d(  x, -x, -x);
		glColor3ub(255,255,0);
		glVertex3d(  x,  x, -x);
	glEnd();

	glBegin(GL_POLYGON);
		glNormal3d(1.0,0.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( x, x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, x, -x);
		glColor3ub(0,0,255);
		glVertex3d( x, -x, -x);
		glColor3ub(255,255,0);
		glVertex3d( x, -x, x);
	glEnd();

	glBegin(GL_POLYGON);
		glNormal3d(-1.0,0.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( -x, x, x);
		glColor3ub(0,255,0);
		glVertex3d( -x, x, -x);
		glColor3ub(0,0,255);
		glVertex3d( -x, -x, -x);
		glColor3ub(255,255,0);
		glVertex3d( -x, -x, x);
	glEnd();

	glBegin(GL_POLYGON);
		glNormal3d(0.0,-1.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( -x, -x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, -x, x);
		glColor3ub(0,0,255);
		glVertex3d( x, -x, -x);
		glVertex3d( -x, -x, -x);
	glEnd();

	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glColor3ub(255,0,0);
		glVertex3d( -x, x, x);
		glColor3ub(0,255,0);
		glVertex3d( x, x, x);
		glColor3ub(0,0,255);
		glVertex3d( x, x, -x);
		glColor3ub(255,255,0);
		glVertex3d( -x, x, -x);
	glEnd();


	m_ScaleX = 0.5f;
	m_ScaleY = 0.5f;
	m_ScaleZ = 0.5f;


	::glEndList();
}

void CDialogGLDlg::DrawCylinder()
{
	glPushMatrix();

	m_nGLcurListIndex = 1;
	::glNewList(m_nGLcurListIndex, GL_COMPILE_AND_EXECUTE);
	m_nGLcurListIndex++;
	

	GLUquadricObj* q = gluNewQuadric();

	glColor3ub(255, 0, 0);
	glShadeModel(GL_SMOOTH);
	//gluQuadricDrawStyle(q, GLU_FILL);	
	gluQuadricDrawStyle(q, GLU_LINE);
	gluQuadricNormals(q, GLU_SMOOTH);

	double cylHeight = sqrt(
		(dTopCenter.x - dBottomCenter.x)*(dTopCenter.x - dBottomCenter.x) +
		(dTopCenter.y - dBottomCenter.y)*(dTopCenter.y - dBottomCenter.y) +
		(dTopCenter.z - dBottomCenter.z)*(dTopCenter.z - dBottomCenter.z)
	);


	gluCylinder(q, dBottomRadius, dBottomRadius, cylHeight, nSlices, nStacks);
	gluDisk(q, 0, dBottomRadius, 16, 16);
	glTranslatef(0, 0, (float)cylHeight);
	gluDisk(q, 0, dBottomRadius, 16, 16);

	gluDeleteQuadric(q);

	::glEndList();

	glPopMatrix();
}

void CDialogGLDlg::DrawAxis()
{
	double cylHeight = sqrt(
		(dTopCenter.x - dBottomCenter.x)*(dTopCenter.x - dBottomCenter.x) +
		(dTopCenter.y - dBottomCenter.y)*(dTopCenter.y - dBottomCenter.y) +
		(dTopCenter.z - dBottomCenter.z)*(dTopCenter.z - dBottomCenter.z)
	);

	GLfloat m_fC = 2.0f;

	::glNewList(m_nGLcurListIndex, GL_COMPILE_AND_EXECUTE);
	m_nGLcurListIndex++;	

	glPushMatrix();

	glLineWidth(2);
	glColor3f(0, 0, 250);
	glTranslatef(0, 0, -(float)cylHeight);
	Draw3DLine(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 4*(float)dBottomRadius);		// Z axis
	Draw3DLine(0.0f, 0.0f, 0.0f, 0.0f, 4 * (float)dBottomRadius, 0.0f);		// Y axis 
	Draw3DLine(0.0f, 0.0f, 0.0f, 4 * (float)dBottomRadius, 0.0f, 0.0f);		// X axis

	glPopMatrix();

	//glRasterPos3f(0.0f, 0.0f, 2 * dBottomRadius + 0.1);
	//PrintString("Z");
	//glRasterPos3f(-m_fC, 6.6f * m_fC / 5, -m_fC);
	//PrintString("Y");
	//glRasterPos3f(6.3f * m_fC / 5, -m_fC, -m_fC);
	//PrintString("X");

	::glEndList();
}

void CDialogGLDlg::PrintString(const char* str)
{
	GLuint m_nFontOffset = 3;

	::glNewList(m_nGLcurListIndex, GL_COMPILE_AND_EXECUTE);

	m_nGLcurListIndex++;

	glPushAttrib(GL_LIST_BIT);
	glListBase(m_nFontOffset);
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, (GLubyte*)str);
	glPopAttrib();

	::glEndList();
}

void CDialogGLDlg::DrawPoint(Point3D pt)
{
	::glNewList(m_nGLcurListIndex, GL_COMPILE_AND_EXECUTE);
	m_nGLcurListIndex++;

	glBegin(GL_POINT);
	glColor3f(0, 0, 1);
	glPointSize(5);
	glVertex3f(pt.x, pt.y, 1.5);
	glEnd();

	::glEndList();
}

void CDialogGLDlg::DrawSphere(Point3D pt, double radius)
{
	::glNewList(m_nGLcurListIndex, GL_COMPILE_AND_EXECUTE);

	m_nGLcurListIndex++;

	glShadeModel(GL_SMOOTH);

	GLUquadricObj* q = gluNewQuadric();

	glPushMatrix();

	glColor3ub(0, 0, 180);
	gluQuadricDrawStyle(q, GLU_FILL);	
	//gluQuadricDrawStyle(q, GLU_LINE);
	gluQuadricNormals(q, GLU_SMOOTH);
	glTranslatef(pt.x, pt.y, pt.z);
	gluSphere(q, radius, 8, 8);


	glPopMatrix();

	gluDeleteQuadric(q);

	::glEndList();
}

void CDialogGLDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
		{
		case VK_ADD:
			m_ScaleX *= 1.1f;
			m_ScaleY *= 1.1f;
			m_ScaleZ *= 1.1f;
			InvalidateRect(NULL,FALSE);
			break;
		case VK_SUBTRACT:
			m_ScaleX /= 1.1f;
			m_ScaleY /= 1.1f;
			m_ScaleZ /= 1.1f;
			InvalidateRect(NULL,FALSE);
			break;
		default :
			{}

		}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDialogGLDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	((CCtrlDlg*)m_pCtrlDlg)->m_bGLwndOpen = false;

	CDialog::OnClose();
}
