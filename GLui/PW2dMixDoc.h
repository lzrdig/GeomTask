// PW2dMixDoc.h : interface of the CPW2dMixDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PW2dMixDoc_H__D66D926A_4C0C_11D3_9234_00A0240EAC17__INCLUDED_)
#define AFX_PW2dMixDoc_H__D66D926A_4C0C_11D3_9234_00A0240EAC17__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPW2dMixDoc : public CDocument
{
protected: // create from serialization only
	CPW2dMixDoc();
	DECLARE_DYNCREATE(CPW2dMixDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPW2dMixDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPW2dMixDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPW2dMixDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PW2dMixDoc_H__D66D926A_4C0C_11D3_9234_00A0240EAC17__INCLUDED_)
