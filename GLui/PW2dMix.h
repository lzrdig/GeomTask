// PW2dMix.h : main header file for the PW2dMix application
//

#if !defined(AFX_PW2dMix_H__D66D9264_4C0C_11D3_9234_00A0240EAC17__INCLUDED_)
#define AFX_PW2dMix_H__D66D9264_4C0C_11D3_9234_00A0240EAC17__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPW2dMixApp:
// See PW2dMix.cpp for the implementation of this class
//

class CPW2dMixApp : public CWinApp
{
public:
	CFrameWnd* pPlotWnd;
	CPW2dMixApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPW2dMixApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPW2dMixApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PW2dMix_H__D66D9264_4C0C_11D3_9234_00A0240EAC17__INCLUDED_)
