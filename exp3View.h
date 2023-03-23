// exp3View.h : interface of the CExp3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXP3VIEW_H__38071FD5_E6E6_4CD0_9A3C_2005D95BA9C6__INCLUDED_)
#define AFX_EXP3VIEW_H__38071FD5_E6E6_4CD0_9A3C_2005D95BA9C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PI 3.1415926

class CExp3View : public CView
{
protected: // create from serialization only
	CExp3View();
	DECLARE_DYNCREATE(CExp3View)

// Attributes
public:
	CExp3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExp3View)
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
	double ViewPointz;
	double ViewPointy;
	double ViewPointx;
	double Tk[9];
	double TR,Theta,Phi,d;//视点在用户坐标系中的球坐标
	double Ia,Ip,ka,kd,ks,ns,LPx,LPy,LPz;

	virtual ~CExp3View();
	void HideSphere(CDC* pDC, float R);
	void CExp3View::FillSphere(CDC* pDC, float R);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExp3View)
	afx_msg void OnHHDraw();
	afx_msg void OnHHFill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in exp3View.cpp
inline CExp3Doc* CExp3View::GetDocument()
   { return (CExp3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXP3VIEW_H__38071FD5_E6E6_4CD0_9A3C_2005D95BA9C6__INCLUDED_)
