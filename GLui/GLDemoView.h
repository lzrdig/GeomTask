// GLDemoView.h : interface of the CGLDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLDEMOVIEW_H__D1DD87F0_F9F0_11D3_99BD_C08908C10000__INCLUDED_)
#define AFX_GLDEMOVIEW_H__D1DD87F0_F9F0_11D3_99BD_C08908C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGL3D.h"
#include "OpenGL4D.h"
#include "HDibApi.h"


namespace OpenGLui
{

	class CGLDemoView : public CView
	{
	protected: // create from serialization only
		CGLDemoView();
		DECLARE_DYNCREATE(CGLDemoView)

		// Attributes
	public:
		//CGLDemoDoc* GetDocument();

		COpenGL3D	m_OpenGL3D;
		COpenGL4D	m_OpenGL4D;
		COpenGL*	m_pOpenGL;

		CPalette*	m_palDIB;
		HDIB		hDIB;

		enum CSaveBMPFlag { BMPRECT = 0, BMPWINDOW, BMPCLIENT };
		CSaveBMPFlag m_nSaveBMPFlag;
		BOOL		 m_bSaveRectBMP;

		bool m_bBox;
		bool m_bAxis;
		CString m_sMapType;

		RECT		 m_Rect;
		POINT        c_down;
		POINT        c_last;
		POINT 	     Zoom_in_First;
		POINT 	     Zoom_in_Last;

		// Operations
	public:
		void Show3DForm();
		void Show4DForm();
		void Load3DData(FILE* fp, char type);
		void Load4DData(FILE* fp, char type);
		void LoadPlot3Ddata(float* pXgrid, float* pYgrid, float* pArray, int row, int col);
		void SetupScene(Point3D dBottomCenter, Point3D dTopCenter, double dBottomRadius, double dTopRadius, 
			int nSlices, int nStacks, Point3D dTestPt, Point3D dFoundPt);
		BOOL ConfirmOverWrite();

		// Overrides
			// ClassWizard generated virtual function overrides
			//{{AFX_VIRTUAL(CGLDemoView)
	public:
		virtual void OnDraw(CDC* pDC);  // overridden to draw this view
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
		virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
		virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
		virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
		//}}AFX_VIRTUAL

	// Implementation
	public:
		void PrintDIB(CDC* pDC);
		void SaveToBMP();
		virtual ~CGLDemoView();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

	protected:
		void GetDIB();
		void FreeDIB();

		// Generated message map functions
	protected:
		//{{AFX_MSG(CGLDemoView)
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnDestroy();
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnFilePrint();
		afx_msg void OnFilePrintPreview();
		afx_msg void OnRotate();
		afx_msg void OnUpdateRotate(CCmdUI *pCmdUI);
		afx_msg void OnPan();
		afx_msg void OnUpdatePan(CCmdUI *pCmdUI);
		afx_msg void OnZoomIn();
		afx_msg void OnZoomOut();
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	public:
	};

#ifndef _DEBUG  // debug version in GLDemoView.cpp
	inline CGLDemoDoc* CGLDemoView::GetDocument()
	{
		return (CGLDemoDoc*)m_pDocument;
	}
#endif

}
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLDEMOVIEW_H__D1DD87F0_F9F0_11D3_99BD_C08908C10000__INCLUDED_)
