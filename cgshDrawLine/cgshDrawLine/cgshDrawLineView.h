
// cgshDrawLineView.h : CcgshDrawLineView ��Ľӿ�
//

#pragma once


class CcgshDrawLineView : public CView
{
protected: // �������л�����
	CcgshDrawLineView();
	DECLARE_DYNCREATE(CcgshDrawLineView)

// ����
public:
	CcgshDrawLineDoc* GetDocument() const;

// ����
public:

// ��д
public:
	void DDAline(int x0, int y0, int x1, int y1, CDC * pDC, int & count, double & distance);
	void Bline(int x0, int y0, int x1, int y1, CDC * pDC, int & count, double & distance);
	void MidPoint(int x0, int y0, int x1, int y1, CDC * pDC, int & count, double & distance, int A, int B, int C);
	void DrawArc(float ar1, float ar2, float R, int part, CDC * pDC);
	void BresenhamArc(float ar1, float ar2, float R, CDC * pDC);
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CcgshDrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // cgshDrawLineView.cpp �еĵ��԰汾
inline CcgshDrawLineDoc* CcgshDrawLineView::GetDocument() const
   { return reinterpret_cast<CcgshDrawLineDoc*>(m_pDocument); }
#endif

