
// LanChatByWC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLanChatByWCApp: 
// �йش����ʵ�֣������ LanChatByWC.cpp
//

class CLanChatByWCApp : public CWinApp
{
public:
	CLanChatByWCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLanChatByWCApp theApp;