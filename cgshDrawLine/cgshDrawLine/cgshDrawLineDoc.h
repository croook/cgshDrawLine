
// cgshDrawLineDoc.h : CcgshDrawLineDoc ��Ľӿ�
//


#pragma once


class CcgshDrawLineDoc : public CDocument
{
protected: // �������л�����
	CcgshDrawLineDoc();
	DECLARE_DYNCREATE(CcgshDrawLineDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CcgshDrawLineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	int m_width;
	int m_height;
	int m_displayMode;
	int m_exeTime;
	float m_analysis_data;
};
