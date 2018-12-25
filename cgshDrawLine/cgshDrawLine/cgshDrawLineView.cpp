
// cgshDrawLineView.cpp : CcgshDrawLineView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgshDrawLine.h"
#endif

#include "cgshDrawLineDoc.h"
#include "cgshDrawLineView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const double Pi = 3.14159265358979323846264338328;
// CcgshDrawLineView

IMPLEMENT_DYNCREATE(CcgshDrawLineView, CView)

BEGIN_MESSAGE_MAP(CcgshDrawLineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CcgshDrawLineView 构造/析构

CcgshDrawLineView::CcgshDrawLineView()
{
	// TODO: 在此处添加构造代码

}

CcgshDrawLineView::~CcgshDrawLineView()
{
}

BOOL CcgshDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcgshDrawLineView 绘制

void CcgshDrawLineView::DDAline(int x0, int y0, int x1, int y1, CDC *pDC,int &count ,double &distance )
{
	//(y2-y1)x+(x1-x2)y+x2y1-x1y2=0
	CcgshDrawLineDoc *pDoc = (CcgshDrawLineDoc*)GetDocument();
	int steps = abs(x1 - x0) > abs(y1 - y0) ? abs(x1 - x0) : abs(y1 - y0);
	int A = y1 - y0, B = x0 - x1, C = x1*y0 - x0*y1;
	float dx = (float)(x1 - x0) / steps;
	float dy = (float)(y1 - y0) / steps;

	float x = x0, y = y0;
	for (int i = 0; i < steps + 1; i++) {
		pDC->SetPixel(int(x + 0.5), int(y + 0.5), RGB(255, 0, 0));
		count++;
		distance += fabs((A*int(x+0.5) + B*int(y+0.5) + C) / sqrt(A*A + B*B));
		x += dx;
		y += dy;
	}
}

void CcgshDrawLineView::Bline(int x0, int y0, int x1, int y1, CDC *pDC,int &count , double &distance)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x = x0, y = y0;
	int stepX = x0 > x1 ? -1 : 1;
	int stepY = y0 > y1 ? -1 : 1;
	int A = y1 - y0, B = x0 - x1, C = x1*y0 - x0*y1;
	CcgshDrawLineDoc *pDoc = (CcgshDrawLineDoc*)GetDocument();

	if (dx > dy)  //abs(k)<1
	{
		int e = dy * 2 - dx;
		for (int i = 0; i <= dx; i++)
		{
			pDC->SetPixel(x, y, RGB(255, 0, 0));
			count++;
			distance += fabs((A*x + B*y + C) / sqrt(A*A + B*B));
			x += stepX;
			e += 2*dy;
			if (e >= 0)
			{
				y += stepY;
				e -= 2*dx;
			}
		}
	}
	else
	{
		int e = 2 * dx - dy;
		for (int i = 0; i <= dy; i++)
		{
			pDC->SetPixel(x, y, RGB(255, 0, 0));
			count++;
			distance += fabs((A*x + B*y + C) / sqrt(A*A + B*B));
			y += stepY;
			e += 2*dx;
			if (e >= 0)
			{
				x += stepX;
				e -= 2*dy;
			}
		}
	}
}


void CcgshDrawLineView::MidPoint(int x0, int y0, int x1, int y1, CDC *pDC,int &count,double &distance,int A,int B,int C) {

	count++;

	int Midx = (x0+x1) > 0 ? int( ((x0 + x1)/2) + 0.5) : int(((x0 + x1) / 2) - 0.5), Midy = (y0+y1) > 0 ? int( ((y0 + y1)/2 ) + 0.5) : int(((y0 + y1) / 2) - 0.5);
	pDC->SetPixel(Midx, Midy, RGB(255, 0, 0));

	distance += fabs((A*Midx + B*Midy + C) / sqrt(A*A + B*B));

	if (abs(x0 - x1) <= 1 && abs(y0 - y1) <= 1) return;
	MidPoint(x0, y0,Midx, Midy, pDC,count,distance,A,B,C);
	MidPoint(Midx, Midy, x1, y1, pDC,count,distance,A,B,C);
}

/*
void CcgshDrawLineView::BresenhamArc(float ar1, float ar2, float R, CDC* pDC) {
	int x, y, direction;
	float d, d1, d2, endarc, curarc;
	ar1 = -ar1;
	ar2 = -ar2;
	x = R * cos(ar1*Pi / 180) + 0.5;
	y = R * sin(ar1*Pi / 180) + 0.5;
	endarc = ar2*Pi / 180;
	d = (x-1)*(x-1)+(y+1)*(y+1)-R*R;
	while (atan2(y, x)<endarc) {
		pDC->SetPixel(x, y, RGB(255, 0, 0));
		if (d < 0) {
			d1 = 2 * (d + x) - 1;
			if (d1 <= 0) 	direction = 1;
			else            direction = 2;
		}
		else if (d > 0) {
			d2 = 2 * (d - y) - 1;
			if (d2 <= 0)  direction = 2;
			else		  direction = 3;
		}
		else direction = 2;

		if (direction == 1) {
			y++; d += 2 * y + 1;
		}
		else if (direction == 2) {
			x--; y++; d += 2 * (y - x + 1);
		}
		else {
			x--; d += -2 * x + 1;
		}
	}
}
*/

void CcgshDrawLineView::DrawArc(float ar1, float ar2, float R,int part,CDC* pDC) {
	int x, y, direction;
	float d,d1,d2,endarc,curarc;
	x = R * cos(ar1*Pi/180) + 0.5;
	y = R * sin(ar1*Pi/180) + 0.5;
	endarc = ar2*Pi / 180;
	d = (x + 1)*(x + 1) + (y - 1)*(y - 1) - R*R;
	while (atan2(y, x)>endarc) {
		if(part == 1)  pDC -> SetPixel(y, -x, RGB(255, 0, 0));
		if(part == 2)  pDC -> SetPixel(-x, -y, RGB(255, 0, 0));
		if(part == 3)  pDC -> SetPixel(-y, x, RGB(255, 0, 0));
		if(part == 4)  pDC->SetPixel(x, y, RGB(255, 0, 0));
		if (d < 0) {
			d1 = 2 * (d + y) - 1;
			if (d1 <= 0) 	direction = 1;
			else            direction = 2;
		}
		else if (d > 0) {
			d2 = 2 * (d - x) - 1;
			if (d2 <= 0)  direction = 2;
			else		  direction = 3;
		}
		else direction = 2;

		if (direction == 1){
			x++; d += 2 * x + 1;
		}
		else if (direction == 2) {
			x++; y--; d += 2 * (x - y + 1);
		}
		else {
			y--; d += -2 * y + 1;
		}
	}
}

void CcgshDrawLineView::BresenhamArc(float ar1, float ar2, float R, CDC* pDC) {
	if (ar1 < 0 || ar2 > 360 || ar1 >= ar2) return;
	int startpart, endpart;
	startpart = ar1 / 90 + 1;
	endpart = ar2 / 90 + 1;
	for (int i = startpart; i <= endpart; i++) {
		if (i == startpart) {
			if (startpart != endpart) {
				DrawArc(90-(ar1-90*(i-1)),0, R, i, pDC);
			}
			else {
				DrawArc(90-(ar1-90 * (i - 1)), 90-(ar2 - 90 * (i - 1)), R, i, pDC);
				return;
			}
		}
		else {
			if (i != endpart) {
				DrawArc(90, 0, R, i, pDC);
			}
			else {
				DrawArc(90, 90-(ar2 - 90 * (i - 1)), R, i, pDC);
			}
		}
	}
}
void CcgshDrawLineView::OnDraw(CDC* /*pDC*/)
{
	CcgshDrawLineDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pDC = GetDC();

	pDC->MoveTo(0, pDoc->m_height / 2);
	pDC->LineTo(pDoc->m_width, pDoc->m_height / 2);
	pDC->MoveTo(pDoc->m_width / 2, 0);
	pDC->LineTo(pDoc->m_width / 2, pDoc->m_height);

	pDC->SetViewportOrg(pDoc->m_width / 2, pDoc->m_height / 2);

	int opStart, opFinish;
	if (pDoc->m_displayMode == 0) {

		pDoc->m_analysis_data = 0;
		opStart = GetTickCount();

		int count = 0;
		double distance = 0;

		for (int i = 0; i < 10; i++) {

			DDAline(0, 0, 250, 70, pDC,count,distance);
			DDAline(0, 0, 70, 250, pDC,count,distance);
			DDAline(0, 0, -250, 70, pDC,count,distance);
			DDAline(0, 0, -70, 250, pDC,count,distance);
			DDAline(0, 0, 250, -70, pDC,count,distance);
			DDAline(0, 0, 70, -250, pDC,count,distance);
			DDAline(0, 0, -250, -70, pDC,count,distance);
			DDAline(0, 0, -70, -250, pDC,count,distance);
		}

		opFinish = GetTickCount();
		pDoc->m_exeTime = opFinish - opStart;
		pDoc->m_analysis_data = distance / count;
	}
	else if (pDoc->m_displayMode == 1) {

		pDoc->m_analysis_data = 0;
		opStart = GetTickCount();

		int count = 0;
		double distance = 0;

		for (int i = 0; i < 10; i++) {

			Bline(0, 0, 250, 70, pDC,count,distance);
			Bline(0, 0, 70, 250, pDC,count,distance);
			Bline(0, 0, -250, 70, pDC,count,distance);
			Bline(0, 0, -70, 250, pDC,count,distance);
			Bline(0, 0, 250, -70, pDC,count,distance);
			Bline(0, 0, 70, -250, pDC,count,distance);
			Bline(0, 0, -250, -70, pDC,count,distance);
			Bline(0, 0, -70, -250, pDC,count,distance);
		}
		opFinish = GetTickCount();
		pDoc->m_exeTime = opFinish - opStart;
		pDoc->m_analysis_data = distance / count;
	}
	else if (pDoc->m_displayMode == 2) {

		opStart = GetTickCount();
		int count = 0;
		double distance = 0;
		pDoc->m_analysis_data = 0;

		for (int i = 0; i < 50; i++) {
			//A = y1 - y0, B = x0 - x1, C = x1*y0 - x0*y1;
			MidPoint(0, 0, 250, 70, pDC,count,distance,70,-250,0);
			MidPoint(0, 0, 70, 250, pDC,count,distance,250,-70,0);
			MidPoint(0, 0, -250, 70, pDC,count,distance,70,250,0);
			MidPoint(0, 0, -70, 250, pDC,count,distance,250,70,0);
			MidPoint(0, 0, 250, -70, pDC,count,distance,-70,-250,0);
			MidPoint(0, 0, 70, -250, pDC,count,distance,-250,-70,0);
			MidPoint(0, 0, -250, -70, pDC,count,distance,-70,250,0);
			MidPoint(0, 0, -70, -250, pDC,count,distance,-250,70,0);
		}
		opFinish = GetTickCount();
		pDoc->m_exeTime = opFinish - opStart;
		pDoc->m_analysis_data = distance / count;
	}
	else if (pDoc->m_displayMode == 3) {

	}
	else if (pDoc->m_displayMode == 4) {
		BresenhamArc(0, 315, 100, pDC);
		BresenhamArc(0, 360, 150, pDC);
		BresenhamArc(50, 200, 125, pDC);
		BresenhamArc(120, 230, 80, pDC);
		BresenhamArc(230, 345, 60, pDC);
	}
	else {
		int count = 0;
		double distance = 0;

		pDoc->m_analysis_data = 0;
		opStart = GetTickCount();

		DDAline(0, 0, 250, 70, pDC, count, distance);
		DDAline(0, 0, 70, 250, pDC, count, distance);
		DDAline(0, 0, -250, 70, pDC, count, distance);
		DDAline(0, 0, -70, 250, pDC, count, distance);
		DDAline(0, 0, 250, -70, pDC, count, distance);
		DDAline(0, 0, 70, -250, pDC, count, distance);
		DDAline(0, 0, -250, -70, pDC, count, distance);
		DDAline(0, 0, -70, -250, pDC, count, distance);

		opFinish = GetTickCount();
		pDoc->m_exeTime = opFinish - opStart;
		pDoc->m_analysis_data = distance / count;
	}

	pDoc->UpdateAllViews(this);
	ReleaseDC(pDC);
}


// CcgshDrawLineView 打印

BOOL CcgshDrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcgshDrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcgshDrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CcgshDrawLineView 诊断

#ifdef _DEBUG
void CcgshDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CcgshDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgshDrawLineDoc* CcgshDrawLineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgshDrawLineDoc)));
	return (CcgshDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CcgshDrawLineView 消息处理程序


void CcgshDrawLineView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CcgshDrawLineDoc *pDoc = GetDocument();
	pDoc->m_width = cx;
	pDoc->m_height = cy;
}
