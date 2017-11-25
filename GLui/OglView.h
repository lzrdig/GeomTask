// PW2dMixView.h : interface of the CPW2dMixView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWOPOBBVIEW_H__D66D926C_4C0C_11D3_9234_00A0240EAC17__INCLUDED_)
#define AFX_PW2dMixView_H__D66D926C_4C0C_11D3_9234_00A0240EAC17__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

static int iBatchLevel = 0;

#include "Resource.h"

#define MAXSTOREDZOOMS 24

class CPwopobbDoc;
class CBbopo;

class CPW2dMixView : public CFormView
{
protected: // create from serialization only
	CPW2dMixView();
	DECLARE_DYNCREATE(CPW2dMixView)

	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

public:
	//{{AFX_DATA(CPW2dMixView)
	enum { IDD = IDD_PWOPOBB_FORM };

	CProgressCtrl	m_cProgRun;

	double	m_Bottom_Y;
	double	m_Bottom_Z;
	double	m_Bottom_X;

	double	m_Top_Y;
	double	m_Top_Z;
	double	m_Top_X;

	double	m_Point3D_Y;
	double	m_Point3D_Z;
	double	m_Point3D_X;

	double m_BottomRadius;
	double m_TopRadius;

	//}}AFX_DATA

// Attributes
public:
	CPW2dMixDoc* GetDocument();
	CBbopo* m_pBbopo;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPW2dMixView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPW2dMixView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	bool CreatePlotWnd();

	//{{AFX_MSG(CPW2dMixView)
	afx_msg void OnRefresh();

	afx_msg void OnChangeBeamdiamId();
	afx_msg void OnChangeBeamdiamPump();
	afx_msg void OnChangeBeamdiamSig();

	afx_msg void OnChangePulseId();
	afx_msg void OnChangePulsePump();
	afx_msg void OnChangePulseSig();

	afx_msg void OnChangeEnergyIdle();
	afx_msg void OnChangeEnergySignal();
	afx_msg void OnChangeEnergyPump();


	afx_msg void OnSetfocusBeamdiamId();
	afx_msg void OnSetfocusBeamdiamPump();
	afx_msg void OnSetfocusBeamdiamSig();

	afx_msg void OnSetfocusPulseId();
	afx_msg void OnSetfocusPulsePump();
	afx_msg void OnSetfocusPulseSig();

	afx_msg void OnSetfocus3dPtYpos();
	afx_msg void OnSetfocus3dPtZpos();
	afx_msg void OnSetfocus3dPtXpos();


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	bool TestForErrors();
	void SetEnableBtns(bool bEnableBtns);
	
	int m_totalpts, m_NtmSpectra;
	double m_SpNorm_s, m_SpNorm_i, m_SpNorm_p;
	double m_IntNorm_max;
	int m_TotalPts_Zoom;
	long m_Fmin, m_Tmin, m_Tmax;
	bool m_bIntensity, m_bSpectrum;
	bool m_bEnableMouseChart;

	
public:

	afx_msg void OnEnSetfocusRadius();
	afx_msg void OnEnChangeRadius();
	afx_msg void OnEnSetfocusNumslices();
	afx_msg void OnEnSetfocusNumstacks();
	afx_msg void OnBnClickedCalculate();
	int m_nSlices;
	int m_nStacks;
	CString m_sCalcDistance;
	double m_dEndPtX;
	double m_dEndPtY;
	double m_dEndPtZ;
	BOOL m_bBox;
	BOOL m_bAxis;
	CString m_sMapType;
};

#ifndef _DEBUG  // debug version in PW2dMixView.cpp
inline CPwopobbDoc* CPW2dMixView::GetDocument()
   { return (CPwopobbDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PW2dMixView_H__D66D926C_4C0C_11D3_9234_00A0240EAC17__INCLUDED_)
