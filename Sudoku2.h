
// Sudoku2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSudoku2App:
// �йش����ʵ�֣������ Sudoku2.cpp
//

class CSudoku2App : public CWinApp
{
public:
	CSudoku2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSudoku2App theApp;