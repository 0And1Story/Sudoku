
// Sudoku2Dlg.h : ͷ�ļ�
//

#pragma once


#define ID_BTN_DEFAULT 10000


// CSudoku2Dlg �Ի���
class CSudoku2Dlg : public CDialogEx
{
// ����
public:
	CSudoku2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SUDOKU2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void dfs (int x, int y);
	CButton mapBtn[10][10];
	afx_msg void OnBnClickedClear();
};
