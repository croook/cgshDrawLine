#pragma once



// CCgSelectControl ������ͼ

class CCgSelectControl : public CFormView
{
	DECLARE_DYNCREATE(CCgSelectControl)

protected:
	CCgSelectControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCgSelectControl();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTCONTROL };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDdaline();
	afx_msg void OnBnClickedBline();
	afx_msg void OnBnClickedMidpoint();
	afx_msg void OnBnClickedComparision();
	afx_msg void OnBnClickedArc();
	CString exetime;
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	CString analysisdata;
};


