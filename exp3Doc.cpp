// exp3Doc.cpp : implementation of the CExp3Doc class
//

#include "stdafx.h"
#include "exp3.h"

#include "exp3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExp3Doc

IMPLEMENT_DYNCREATE(CExp3Doc, CDocument)

BEGIN_MESSAGE_MAP(CExp3Doc, CDocument)
	//{{AFX_MSG_MAP(CExp3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExp3Doc construction/destruction

CExp3Doc::CExp3Doc()
{
	// TODO: add one-time construction code here

}

CExp3Doc::~CExp3Doc()
{
}

BOOL CExp3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExp3Doc serialization

void CExp3Doc::Serialize(CArchive& ar)
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
// CExp3Doc diagnostics

#ifdef _DEBUG
void CExp3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExp3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExp3Doc commands
