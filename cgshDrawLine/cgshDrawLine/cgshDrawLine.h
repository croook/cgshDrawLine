
// cgshDrawLine.h : cgshDrawLine Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CcgshDrawLineApp:
// �йش����ʵ�֣������ cgshDrawLine.cpp
//

class CcgshDrawLineApp : public CWinAppEx
{
public:
	CcgshDrawLineApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CcgshDrawLineApp theApp;
