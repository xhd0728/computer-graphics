// exp3View.cpp : implementation of the CExp3View class
//

#include "stdafx.h"
#include "exp3.h"

#include "exp3Doc.h"
#include "exp3View.h"
#include "math.h"
#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExp3View

IMPLEMENT_DYNCREATE(CExp3View, CView)

BEGIN_MESSAGE_MAP(CExp3View, CView)
	//{{AFX_MSG_MAP(CExp3View)
	ON_COMMAND(IDD_MDRAW, OnHHDraw)
	ON_COMMAND(ID_MFILL, OnHHFill)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExp3View construction/destruction

CExp3View::CExp3View()
{
	// TODO: add construction code here
	// TODO: add construction code here
	TR=1000,d=1000,Phi=30,Theta=60;

	Tk[1]=sin(PI*Theta/180);
	Tk[2]=sin(PI*Phi/180);
	Tk[3]=cos(PI*Theta/180);
	Tk[4]=cos(PI*Phi/180);
	Tk[5]=Tk[2]*Tk[3];
	Tk[6]=Tk[2]*Tk[1];
	Tk[7]=Tk[4]*Tk[3];
	Tk[8]=Tk[4]*Tk[1];
	ViewPointx=TR*Tk[6];
	ViewPointy=TR*Tk[4];
	ViewPointz=TR*Tk[5];

	Ia=255;
	Ip=255;
	ka=0.2;
	kd=0.6;
	ks=0.7;
	ns=50;
	LPx=TR*sin(PI*45/180)*sin(PI*45/180);
	LPy=TR*cos(PI*45/180);
	LPz=TR*sin(PI*45/180)*cos(PI*45/180);
}

CExp3View::~CExp3View()
{
}

BOOL CExp3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExp3View drawing

void CExp3View::OnDraw(CDC* pDC)
{
	CExp3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExp3View printing

BOOL CExp3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExp3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExp3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExp3View diagnostics

#ifdef _DEBUG
void CExp3View::AssertValid() const
{
	CView::AssertValid();
}

void CExp3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExp3Doc* CExp3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp3Doc)));
	return (CExp3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExp3View message handlers

void CExp3View::HideSphere(CDC *pDC, float R) 
{
	
	double x[4],y[4],z[4];
	double x1[4],y1[4],z1[4];
	double a1,a2;
	double sx[4],sy[4];
	double xn,yn,zn,vn,xv,yv,zv,costheta,mv;
	Tk[1]=sin(PI*Theta/180);
	Tk[2]=sin(PI*Phi/180);
	Tk[3]=cos(PI*Theta/180);
	Tk[4]=cos(PI*Phi/180);
	Tk[5]=Tk[2]*Tk[3];
	Tk[6]=Tk[2]*Tk[1];
	Tk[7]=Tk[4]*Tk[3];
	Tk[8]=Tk[4]*Tk[1];
	
	int idelta = 10;

	for (double i = 0; i < 200; i += idelta)
	{
		for (int j = 0; j < 360; j += 5)
		{
			a1 = j * PI / 180;
			a2 = (j + 5) * PI / 180;
			x[0] = R * cos(a1);
			y[0] = i;
			z[0] = R * sin(a1);
			x[3] = R * cos(a2);
			y[3] = i;
			z[3] = R * sin(a2);
			x[2] = R * cos(a2);
			y[2] = i + idelta;
			z[2] = R * sin(a2);
			x[1] = R * cos(a1);
			y[1] = i + idelta;
			z[1] = R * sin(a1);
			
			xn=(y[1]-y[0])*(z[2]-z[0])-(y[2]-y[0])*(z[1]-z[0]);//计算网格四边形外法向量
			yn=(x[2]-x[0])*(z[1]-z[0])-(x[1]-x[0])*(z[2]-z[0]);
			zn=(x[1]-x[0])*(y[2]-y[0])-(x[2]-x[0])*(y[1]-y[0]);
			vn=sqrt(xn*xn+yn*yn+zn*zn);//外法向量的模
			xn=xn/vn;//规格化外法向量
			yn=yn/vn; 
			zn=zn/vn;
			xv=ViewPointx-x[0];//视向量
			yv=ViewPointy-y[0];
			zv=ViewPointz-z[0];
			mv=sqrt(xv*xv+yv*yv+zv*zv);
			xv=xv/mv;//规格化视向量
			yv=yv/mv;
			zv=zv/mv;
			costheta=xn*xv+yn*yv+zn*zv;
			if (costheta>=0)//根据后向判别法实现消隐,cosθ>=0则画出小四边形
			{
				for (int k=0;k<4;k++)//进行观察变换
				{
					x1[k]=x[k]*Tk[3]-z[k]*Tk[1];//观察坐标系三维坐标
					y1[k]=-x[k]*Tk[8]+y[k]*Tk[2]-z[k]*Tk[7];
					z1[k]=-x[k]*Tk[6]-y[k]*Tk[4]-z[k]*Tk[5]+TR;
					//sx[k]=d*x1[k]/z1[k];//屏幕二维坐标系
					//sy[k]=d*y1[k]/z1[k];
					sx[k]=x1[k];
					sy[k]=y1[k];
				}
				pDC->MoveTo((int)sx[0],(int)sy[0]);
				pDC->LineTo((int)sx[1],(int)sy[1]);
				pDC->LineTo((int)sx[2],(int)sy[2]);
				pDC->LineTo((int)sx[3],(int)sy[3]);
				pDC->LineTo((int)sx[0],(int)sy[0]);
			}
			Sleep(5);
		}
	}
	for (int ii = 0; ii < 360; ii += 5)
	{
		a1 = ii * PI / 180;
		a2 = (ii + 5) * PI / 180;
		y[0] = y[1] = y[2] = 200;
		x[0] = R * cos(a1);
		z[0] = R * sin(a1);
		x[1] = 0;
		z[1] = 0;
		x[2] = R * cos(a2);
		z[2] = R * sin(a2);
		xn=(y[1]-y[0])*(z[2]-z[0])-(y[2]-y[0])*(z[1]-z[0]);//计算网格四边形外法向量
		yn=(x[2]-x[0])*(z[1]-z[0])-(x[1]-x[0])*(z[2]-z[0]);
		zn=(x[1]-x[0])*(y[2]-y[0])-(x[2]-x[0])*(y[1]-y[0]);
		vn=sqrt(xn*xn+yn*yn+zn*zn);//外法向量的模
		xn=xn/vn;//规格化外法向量
		yn=yn/vn; 
		zn=zn/vn;
		xv=ViewPointx-x[0];//视向量
		yv=ViewPointy-y[0];
		zv=ViewPointz-z[0];
		mv=sqrt(xv*xv+yv*yv+zv*zv);
		xv=xv/mv;//规格化视向量
		yv=yv/mv;
		zv=zv/mv;
		costheta=xn*xv+yn*yv+zn*zv;
		if (costheta>=0)//根据后向判别法实现消隐,cosθ>=0则画出小四边形
		{
			for (int k=0;k<4;k++)//进行观察变换
			{
				x1[k]=x[k]*Tk[3]-z[k]*Tk[1];//观察坐标系三维坐标
				y1[k]=-x[k]*Tk[8]+y[k]*Tk[2]-z[k]*Tk[7];
				z1[k]=-x[k]*Tk[6]-y[k]*Tk[4]-z[k]*Tk[5]+TR;
				sx[k]=x1[k];
				sy[k]=y1[k];
			}
			pDC->MoveTo((int)sx[0],(int)sy[0]);
			pDC->LineTo((int)sx[1],(int)sy[1]);
			pDC->LineTo((int)sx[2],(int)sy[2]);
			pDC->LineTo((int)sx[0],(int)sy[0]);
		}
		Sleep(5);
	}
}

void CExp3View::OnHHDraw() 
{
	// TODO: Add your command handler code here
	CDC* pDC=GetDC();
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(),rect.Height());
	pDC->SetViewportExt(rect.Width(),-rect.Height());
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);
	HideSphere(pDC, 100);
	ReleaseDC(pDC);
}

void CExp3View::FillSphere(CDC* pDC, float R)
{
	CPoint rgnpoints[4];
	COLORREF fillColor;
	CBrush brush;
	CPen NewPen;
	double sx[4],sy[4];

	double x[4],y[4],z[4];
	double x1[4],y1[4],z1[4];
	double a1,a2,b1,b2;
	double xn,yn,zn,vn,xv,yv,zv,costheta,mv;
	double Ie,Id,Is,costhita1,cosphi,hx,hy,hz,lx,ly,lz;
	int C=0;

	Ie=Ia*ka;//环境光分量

	int idelta = 10;
	for (double i = 0; i < 200; i += idelta)
	{
		for (int j = 0; j < 360; j += 5)
		{
			a1 = j * PI / 180;
			a2 = (j + 5) * PI / 180;
			x[0] = R * cos(a1);
			y[0] = i;
			z[0] = R * sin(a1);
			x[3] = R * cos(a2);
			y[3] = i;
			z[3] = R * sin(a2);
			x[2] = R * cos(a2);
			y[2] = i + idelta;
			z[2] = R * sin(a2);
			x[1] = R * cos(a1);
			y[1] = i + idelta;
			z[1] = R * sin(a1);
			
			xn=(y[1]-y[0])*(z[2]-z[0])-(y[2]-y[0])*(z[1]-z[0]);//计算网格四边形外法向量
			yn=(x[2]-x[0])*(z[1]-z[0])-(x[1]-x[0])*(z[2]-z[0]);
			zn=(x[1]-x[0])*(y[2]-y[0])-(x[2]-x[0])*(y[1]-y[0]);
			vn=sqrt(xn*xn+yn*yn+zn*zn);//外法向量的模
			xn=xn/vn;//规格化外法向量
			yn=yn/vn; 
			zn=zn/vn;
			xv=ViewPointx-x[0];//视向量
			yv=ViewPointy-y[0];
			zv=ViewPointz-z[0];
			mv=sqrt(xv*xv+yv*yv+zv*zv);
			xv=xv/mv;//规格化视向量
			yv=yv/mv;
			zv=zv/mv;
			costheta=xn*xv+yn*yv+zn*zv;
			if (costheta>=0)//根据后向判别法实现消隐,cosθ>=0则画出小四边形
			{
				lx=LPx-x[0];ly=LPy-y[0];lz=LPz-z[0];//光源向量
			    mv=sqrt(lx*lx+ly*ly+lz*lz);
			    lx=lx/mv;ly=ly/mv;lz=lz/mv;//规格化光源向量
			   
			    costhita1=xn*lx+yn*ly+zn*lz;//法向量与光源向量的夹角余弦
			    hx=lx+xv;hy=ly+yv;hz=lz+zv;//视向量与光源向量的和
			    mv=sqrt(hx*hx+hy*hy+hz*hz);
			    hx=hx/mv;hy=hy/mv;hz=hz/mv;	
			    cosphi=xn*hx+yn*hy+zn*hz;//镜面反射光与视向量的夹角
			    if (costhita1>=0)
					Id=Ip*kd*costhita1;
			    else
				    Id=0;
			    if (cosphi>=0)
					Is=Ip*ks*pow(cosphi,ns);	
			    else
					Is=0;

			    C=(int)(Ie+Id+Is);
			    if (C>255) C=255;

				for (int k=0;k<4;k++)//进行观察变换
				{
					x1[k]=x[k]*Tk[3]-z[k]*Tk[1];//观察坐标系三维坐标
					y1[k]=-x[k]*Tk[8]+y[k]*Tk[2]-z[k]*Tk[7];
					z1[k]=-x[k]*Tk[6]-y[k]*Tk[4]-z[k]*Tk[5]+TR;

					rgnpoints[k].x=x1[k];
					rgnpoints[k].y=y1[k];
				}
				fillColor=RGB(C,C,C);
				if (!brush.CreateSolidBrush(fillColor)) return;
				if (!NewPen.CreatePen(PS_SOLID,1,fillColor)) return;  
				pDC->SelectObject(&NewPen);
				pDC->SelectObject(&brush);
				pDC->Polygon(rgnpoints,4);
				brush.DeleteObject();
				NewPen.DeleteObject();
			}
			Sleep(5);
		}
	}
	for (int ii = 0; ii < 360; ii += 5)
	{
		a1 = ii * PI / 180;
		a2 = (ii + 5) * PI / 180;
		y[0] = y[1] = y[2] = 200;
		x[0] = R * cos(a1);
		z[0] = R * sin(a1);
		x[1] = 0;
		z[1] = 0;
		x[2] = R * cos(a2);
		z[2] = R * sin(a2);
		xn=(y[1]-y[0])*(z[2]-z[0])-(y[2]-y[0])*(z[1]-z[0]);//计算网格四边形外法向量
		yn=(x[2]-x[0])*(z[1]-z[0])-(x[1]-x[0])*(z[2]-z[0]);
		zn=(x[1]-x[0])*(y[2]-y[0])-(x[2]-x[0])*(y[1]-y[0]);
		vn=sqrt(xn*xn+yn*yn+zn*zn);//外法向量的模
		xn=xn/vn;//规格化外法向量
		yn=yn/vn; 
		zn=zn/vn;
		xv=ViewPointx-x[0];//视向量
		yv=ViewPointy-y[0];
		zv=ViewPointz-z[0];
		mv=sqrt(xv*xv+yv*yv+zv*zv);
		xv=xv/mv;//规格化视向量
		yv=yv/mv;
		zv=zv/mv;
		costheta=xn*xv+yn*yv+zn*zv;
		if (costheta>=0)//根据后向判别法实现消隐,cosθ>=0则画出小四边形
		{
			lx=LPx-x[0];ly=LPy-y[0];lz=LPz-z[0];//光源向量
			mv=sqrt(lx*lx+ly*ly+lz*lz);
			lx=lx/mv;ly=ly/mv;lz=lz/mv;//规格化光源向量
		   
			costhita1=xn*lx+yn*ly+zn*lz;//法向量与光源向量的夹角余弦
			hx=lx+xv;hy=ly+yv;hz=lz+zv;//视向量与光源向量的和
			mv=sqrt(hx*hx+hy*hy+hz*hz);
			hx=hx/mv;hy=hy/mv;hz=hz/mv;	
			cosphi=xn*hx+yn*hy+zn*hz;//镜面反射光与视向量的夹角
			if (costhita1>=0)
				Id=Ip*kd*costhita1;
			else
				Id=0;
			if (cosphi>=0)
				Is=Ip*ks*pow(cosphi,ns);	
			else
				Is=0;

			C=(int)(Ie+Id+Is);
			if (C>255) C=255;

			for (int k=0;k<3;k++)//进行观察变换
			{
				x1[k]=x[k]*Tk[3]-z[k]*Tk[1];//观察坐标系三维坐标
				y1[k]=-x[k]*Tk[8]+y[k]*Tk[2]-z[k]*Tk[7];
				z1[k]=-x[k]*Tk[6]-y[k]*Tk[4]-z[k]*Tk[5]+TR;

				rgnpoints[k].x=x1[k];
				rgnpoints[k].y=y1[k];
			}
			fillColor=RGB(C,C,C);
			if (!brush.CreateSolidBrush(fillColor)) return;
			if (!NewPen.CreatePen(PS_SOLID,1,fillColor)) return;  
			pDC->SelectObject(&NewPen);
			pDC->SelectObject(&brush);
			pDC->Polygon(rgnpoints,3);
			brush.DeleteObject();
			NewPen.DeleteObject();
		}
		Sleep(5);
	}
}

void CExp3View::OnHHFill() 
{
	// TODO: Add your command handler code here
	CDC* pDC=GetDC();
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(),rect.Height());
	pDC->SetViewportExt(rect.Width(),-rect.Height());
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);
	FillSphere(pDC, 100);
	ReleaseDC(pDC);
}
