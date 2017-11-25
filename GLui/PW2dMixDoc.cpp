// PW2dMixDoc.cpp : implementation of the CPW2dMixDoc class
//

#include "stdafx.h"
#include "PW2dMix.h"

#include "PW2dMixDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPW2dMixDoc

IMPLEMENT_DYNCREATE(CPW2dMixDoc, CDocument)

BEGIN_MESSAGE_MAP(CPW2dMixDoc, CDocument)
	//{{AFX_MSG_MAP(CPW2dMixDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPW2dMixDoc construction/destruction

CPW2dMixDoc::CPW2dMixDoc()
{
	// TODO: add one-time construction code here

}

CPW2dMixDoc::~CPW2dMixDoc()
{
}

BOOL CPW2dMixDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPW2dMixDoc serialization

void CPW2dMixDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPW2dMixDoc diagnostics

#ifdef _DEBUG
void CPW2dMixDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPW2dMixDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPW2dMixDoc commands
