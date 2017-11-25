// DialogGLDlg.h : header file
//

#if !defined(AFX_DIALOGGLDLG_H__A779FD07_4258_11D1_88DD_A4B001C10000__INCLUDED_)
#define AFX_DIALOGGLDLG_H__A779FD07_4258_11D1_88DD_A4B001C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MathUtils.h"

using namespace SimpleGL;



/////////////////////////////////////////////////////////////////////////////
// CDialogGLDlg dialog


class CDialogGLDlg : public CDialog
{

// Construction
public:
	CDialogGLDlg(CWnd* pParent = NULL);	// standard constructor

	CDialog* m_pCtrlDlg;

	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
	void RenderScene();
	void Rotate();

	BOOL m_Rotate;

	HGLRC m_hGLContext;
	int m_GLPixelIndex;

	double m_transY;
	double m_transX;
	double m_transZ;

	double m_angle1;
	double m_angle2;

	float m_ScaleX;
	float m_ScaleY;
	float m_ScaleZ;

	GLdouble m_xRotate;
	GLdouble m_yRotate;
	GLdouble m_zRotate;

	int m_width;
	int m_height;
	int m_exp;

	float m_size;

	int m_nGLcurListIndex;
	int m_nGLtotalNumOfLists;

	CPoint m_RightDownPos;
	CPoint m_LeftDownPos;
	BOOL m_RightButtonDown;
	BOOL m_LeftButtonDown;

	// Global vars needed for cylinder drawing. Not the best option
	struct Point3D dBottomCenter;
	struct Point3D dTopCenter;
	double dBottomRadius;
	int nSlices;
	int nStacks;

	Point3D m_trgtPt;

	void DrawCube();	//test rutine building a cube
	void DrawCylinder();
	void DrawScene();
	void DrawAxis();
	void DrawPoint(Point3D pt);
	void DrawSphere(Point3D pt, double radius);
	void PrintString(const char* str);

// Dialog Data
	//{{AFX_DATA(CDialogGLDlg)
	enum { IDD = IDD_GLVIEW_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogGLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDialogGLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPopupRotate();
	afx_msg void OnPopupSizeDecrease();
	afx_msg void OnPopupSizeIncrease();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGGLDLG_H__A779FD07_4258_11D1_88DD_A4B001C10000__INCLUDED_)
