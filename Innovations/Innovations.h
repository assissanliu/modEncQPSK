// Innovations_3.h : Innovations_3 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CInnovations_3App
// �йش���ʵ�ֵ���Ϣ������� Innovations_3.cpp
//

class CInnovations_App : public CWinApp
{
public:
	CInnovations_App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
