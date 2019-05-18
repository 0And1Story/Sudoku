
// Sudoku2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sudoku2.h"
#include "Sudoku2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


bool isFind;
int map[10][10];
bool vis[3][10][10];


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSudoku2Dlg �Ի���



CSudoku2Dlg::CSudoku2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSudoku2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudoku2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSudoku2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CSudoku2Dlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_CLEAR, &CSudoku2Dlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CSudoku2Dlg ��Ϣ�������

BOOL CSudoku2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	for(int i = 1;i <= 9;i ++)
		for(int j = 1;j <= 9;j ++)
		{
			mapBtn[i][j].Create(_T(""),
							  WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
							  CRect(60+j*30+(j>=4?10:0)+(j>=7?10:0),60+i*30+(i>=4?10:0)+(i>=7?10:0),90+j*30+(j>=4?10:0)+(j>=7?10:0),90+i*30+(i>=4?10:0)+(i>=7?10:0) ),
							  this,
							  ID_BTN_DEFAULT+(i-1)*9+j-1);			//������ť
		}
	map[1][0] = -1;
	CFont* f;
	f = new CFont;
	f->CreateFont(30,										//��
				10,											//��
				0,
				0,
				FW_BOLD,
				FALSE,
				FALSE,
				0,
				ANSI_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_SWISS,
				_T("΢���ź�"));								//��������
	for (int i = 1; i <= 9; i ++)
		for (int j = 1; j <= 9; j ++)
			mapBtn[i][j].SetFont (f);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSudoku2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSudoku2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSudoku2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSudoku2Dlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isFind = 0;
	dfs (1, 0);
	if (!isFind) {
		AfxMessageBox (_T ("Failed!"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	for (int i = 1; i <= 9; i ++) {
		for (int j = 1; j <= 9; j ++) {
			CString nstr;
			nstr.Format (_T ("%d"), map[i][j]);
			SetDlgItemText (ID_BTN_DEFAULT+(i-1)*9+j-1, nstr);
		}
	}
	AfxMessageBox (_T ("Successful!"), MB_OK | MB_ICONINFORMATION);
}


void CSudoku2Dlg::OnBnClickedClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isFind = 0;
	for (int i = 1; i <= 9; i ++) {
		for (int j = 1; j <= 9; j ++) {
			map[i][j] = 0;
			vis[0][i][j] = 0;
			vis[1][i][j] = 0;
			vis[2][i][j] = 0;
			SetDlgItemText (ID_BTN_DEFAULT+(i-1)*9+j-1, _T ("") );
		}
	}
}


BOOL CSudoku2Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		UINT nChar = pMsg->wParam;
		CWnd* pWnd = GetFocus ();
		if (!pWnd) return FALSE;
		UINT uID = pWnd->GetDlgCtrlID ();
		if (uID < ID_BTN_DEFAULT || uID > ID_BTN_DEFAULT+80)
			return FALSE;
		if (nChar == '0' || nChar == VK_SPACE) {
			int i, j;
			i = (uID-ID_BTN_DEFAULT)/9+1;
			j = (uID-ID_BTN_DEFAULT)%9+1;
			vis[0][i][map[i][j]] = 0;
			vis[1][j][map[i][j]] = 0;
			vis[2][((i-1)/3)*3+(j-1)/3+1][map[i][j]] = 0;
			map[i][j] = 0;
			SetDlgItemText (uID, _T ("") );
		}
		if (nChar >= '1' && nChar <= '9') {
			int i, j;
			i = (uID-ID_BTN_DEFAULT)/9+1;
			j = (uID-ID_BTN_DEFAULT)%9+1;
			if (vis[0][i][nChar-'0'] || vis[1][j][nChar-'0'] || vis[2][((i-1)/3)*3+(j-1)/3+1][nChar-'0']) {
				//CWnd* pWnd = AfxGetMainWnd ();
				//pWnd->SetFocus ();
				//AfxMessageBox (_T ("Question Error!"), MB_OK | MB_ICONERROR);
				return FALSE;
			}
			vis[0][i][map[i][j]] = 0;
			vis[1][j][map[i][j]] = 0;
			vis[2][((i-1)/3)*3+(j-1)/3+1][map[i][j]] = 0;
			map[i][j] = 0;
			map[i][j] = nChar-'0';
			vis[0][i][map[i][j]] = 1;
			vis[1][j][map[i][j]] = 1;
			vis[2][((i-1)/3)*3+(j-1)/3+1][map[i][j]] = 1;
			CString nstr;
			nstr.Format (_T ("%d"), nChar-'0');
			SetDlgItemText (uID, nstr);
		}
	}
	//return CDialog::PreTranslateMessage(pMsg);
	return FALSE;
}


void CSudoku2Dlg::dfs (int x, int y) {
	if (map[x][y]) {
		if (x == 9 && y == 9) {
			isFind = 1;
			return;
		}
		dfs (x+y/9, y%9+1);
	} else {
		for (int i = 1; i <= 9; i ++) {
			if (vis[0][x][i] || vis[1][y][i] || vis[2][((x-1)/3)*3+(y-1)/3+1][i]) {
				continue;
			}
			map[x][y] = i;
			vis[0][x][map[x][y]] = 1;
			vis[1][y][map[x][y]] = 1;
			vis[2][((x-1)/3)*3+(y-1)/3+1][map[x][y]] = 1;
			if (x == 9 && y == 9) {
				isFind = 1;
				return;
			}
			dfs (x+y/9, y%9+1);
			if (isFind) {
				return;
			}
			vis[0][x][map[x][y]] = 0;
			vis[1][y][map[x][y]] = 0;
			vis[2][((x-1)/3)*3+(y-1)/3+1][map[x][y]] = 0;
			map[x][y] = 0;
		}
	}
}

