// CtrlLDlg.h : header file
//

#if !defined(AFX_CTRLDLG_H__A779FD07_4259_11D1_88DD_A4B001C10000__INCLUDED_)
#define AFX_CTRLDLG_H__A779FD07_4259_11D1_88DD_A4B001C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "Cylinder.h"

using namespace SimpleGL;

/////////////////////////////////////////////////////////////////////////////
// CCtrlDlg dialog


class CCtrlDlg : public CDialog
{
	// Construction
public:
	CCtrlDlg(CWnd* pParent = NULL);	// standard constructor

	//BOOL SetWindowPixelFormat(HDC hDC);

	bool m_bGLwndOpen = false;
	BOOL m_bGLwndCreated = false;

	Cylinder m_cylObj;

	int glDisplayList[4];

	bool m_Rotate;

	HGLRC m_hGLContext;
	int m_GLPixelIndex;


	int m_width;
	int m_height;
	int m_exp;

	float m_size;


	CPoint m_RightDownPos;
	CPoint m_LeftDownPos;
	BOOL m_RightButtonDown;
	BOOL m_LeftButtonDown;


	CDialogGLDlg m_dlgGL;

	// Dialog Data
	//{{AFX_DATA(CCtrlDlg)
	enum { IDD = IDD_CTRL_DLG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtrlDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:
	//afx_msg void OnContextMenu(CWnd*, CPoint point);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnTimer(UINT nIDEvent);
	//afx_msg void OnPopupRotate();
	//afx_msg void OnPopupSizeDecrease();
	//afx_msg void OnPopupSizeIncrease();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShowglBtn();
	double m_dPoint3D_X;
	double m_dPoint3D_Y;
	double m_dPoint3D_Z;
	double m_dBottomX;
	double m_dBottomY;
	double m_dBottomZ;
	double m_dTopX;
	double m_dTopY;
	double m_dTopZ;
	double m_dBottomRadius;
	double m_dTopRadius;
	afx_msg void OnEnChangeBottomradius();
	afx_msg void OnEnUpdateBottomradius();
	afx_msg void OnBnClickedUpdateglBtn();
	int m_nSlices;
	int m_nStacks;
	void SendParamsToGLwnd();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRLDLG_H__A779FD07_4259_11D1_88DD_A4B001C10000__INCLUDED_)
