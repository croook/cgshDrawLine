
// cgshDrawLineView.h : CcgshDrawLineView 类的接口
//

#pragma once


class CcgshDrawLineView : public CView
{
protected: // 仅从序列化创建
	CcgshDrawLineView();
	DECLARE_DYNCREATE(CcgshDrawLineView)

// 特性
public:
	CcgshDrawLineDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	void DDAline(int x0, int y0, int x1, int y1, CDC * pDC, int & count, double & distance);
	void Bline(int x0, int y0, int x1, int y1, CDC * pDC, int & count, double & distance);
	void MidPoint(int x0, int y0, int x1, int y1, CDC * pDC, int & count, double & distance, int A, int B, int C);
	void DrawArc(float ar1, float ar2, float R, int part, CDC * pDC);
	void BresenhamArc(float ar1, float ar2, float R, CDC * pDC);
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CcgshDrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // cgshDrawLineView.cpp 中的调试版本
inline CcgshDrawLineDoc* CcgshDrawLineView::GetDocument() const
   { return reinterpret_cast<CcgshDrawLineDoc*>(m_pDocument); }
#endif

