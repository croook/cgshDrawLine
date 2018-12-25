// CgSelectControl.cpp : 实现文件
//

#include "stdafx.h"
#include "cgshDrawLine.h"
#include "CgSelectControl.h"
#include "cgshDrawLine.h"
#include "cgshDrawLineDoc.h"

// CCgSelectControl

IMPLEMENT_DYNCREATE(CCgSelectControl, CFormView)

CCgSelectControl::CCgSelectControl()
	: CFormView(IDD_SELECTCONTROL)
	, exetime(_T(""))
	, analysisdata(_T(""))
{

}

CCgSelectControl::~CCgSelectControl()
{
}

void CCgSelectControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EXETIME, exetime);
	DDX_Text(pDX, IDC_ANALYSIS, analysisdata);
}

BEGIN_MESSAGE_MAP(CCgSelectControl, CFormView)
	ON_BN_CLICKED(IDC_DDALINE, &CCgSelectControl::OnBnClickedDdaline)
	ON_BN_CLICKED(IDC_BLINE, &CCgSelectControl::OnBnClickedBline)
	ON_BN_CLICKED(IDC_MIDPOINT, &CCgSelectControl::OnBnClickedMidpoint)
	ON_BN_CLICKED(IDC_COMPARISION, &CCgSelectControl::OnBnClickedComparision)
	ON_BN_CLICKED(IDC_ARC, &CCgSelectControl::OnBnClickedArc)
END_MESSAGE_MAP()


// CCgSelectControl 诊断

#ifdef _DEBUG
void CCgSelectControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCgSelectControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCgSelectControl 消息处理程序


void CCgSelectControl::OnBnClickedDdaline()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshDrawLineDoc* pDoc = (CcgshDrawLineDoc*)GetDocument();

	pDoc->m_displayMode = 0;

	pDoc->UpdateAllViews(this);

}


void CCgSelectControl::OnBnClickedBline()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshDrawLineDoc* pDoc = (CcgshDrawLineDoc*)GetDocument();

	pDoc->m_displayMode = 1;

	pDoc->UpdateAllViews(this);

}


void CCgSelectControl::OnBnClickedMidpoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshDrawLineDoc* pDoc = (CcgshDrawLineDoc*)GetDocument();

	pDoc->m_displayMode = 2;

	pDoc->UpdateAllViews(this);

}


void CCgSelectControl::OnBnClickedComparision()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshDrawLineDoc* pDoc = (CcgshDrawLineDoc*)GetDocument();

	pDoc->m_displayMode = 3;

	pDoc->UpdateAllViews(this);

}


void CCgSelectControl::OnBnClickedArc()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgshDrawLineDoc* pDoc = (CcgshDrawLineDoc*)GetDocument();

	pDoc->m_displayMode = 4;

	pDoc->UpdateAllViews(this);
}


void CCgSelectControl::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CcgshDrawLineDoc *pDoc = (CcgshDrawLineDoc*)GetDocument();
	UpdateData(TRUE);

	CString str, str1;
	str1.Format(_T("%.5f"), pDoc->m_analysis_data);
	str.Format(_T("%d"), pDoc->m_exeTime);
	this->exetime = str + _T(" ms");
	this->analysisdata = str1;
	UpdateData(FALSE);
}
