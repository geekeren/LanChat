
// LanChatByWCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LanChatByWC.h"
#include "LanChatByWCDlg.h"
#include "ChatDialog.h"
#include "afxdialogex.h"
#include "DataManager.h"
#include "Session.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CLanChatByWCDlg �Ի���



CLanChatByWCDlg::CLanChatByWCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLanChatByWCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLanChatByWCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, UserListControl);
}

BEGIN_MESSAGE_MAP(CLanChatByWCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MY_MESSAGE, &CLanChatByWCDlg::HandleMyMsg)
	ON_MESSAGE(WM_LISTCHANGE_MESSAGE, &CLanChatByWCDlg::HandleUserListChange)

	ON_BN_CLICKED(IDCANCEL, &CLanChatByWCDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CLanChatByWCDlg::OnLvnItemDClickList)
END_MESSAGE_MAP()


// CLanChatByWCDlg ��Ϣ�������

BOOL CLanChatByWCDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	DataManager* dataManager;
	dataManager = DataManager::getInstance();
	dataManager->startDiscoverServer();


	sessionManager = SessionManager::GetInstance();

	//����б���
	CRect rect;
	UserListControl.GetClientRect(&rect);
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	UserListControl.SetExtendedStyle(UserListControl.GetExtendedStyle()|LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// Ϊ�б���ͼ�ؼ��������   

	UserListControl.InsertColumn(0, _T("�û���"), LVCFMT_CENTER, rect.Width() / 2, 0);
	UserListControl.InsertColumn(1, _T("IP"), LVCFMT_CENTER, rect.Width() / 2, 0);
	UserListControl.InsertColumn(2, _T("ID"), LVCFMT_CENTER,2 , 0);
	// ���б���ͼ�ؼ��в����б���������б������ı�   
	UserListControl.InsertItem(0, _T("192.168.23.2"));
	UserListControl.SetItemText(0, 1, _T("192.168.23.2"));
	UserListControl.SetItemText(0, 2, _T("192.168.23.2"));

	UserListControl.InsertItem(1, _T("192.168.23.1"));
	UserListControl.SetItemText(1, 1, _T("192.168.23.1"));
	UserListControl.SetItemText(1, 2, _T("192.168.23.2"));

	UserListControl.InsertItem(2, _T("BrainWang"));
	UserListControl.SetItemText(2, 1, _T("192.168.23.3"));
	UserListControl.SetItemText(2, 2, _T("192.168.23.2"));
	
	UserListControl.InsertItem(3, _T("192.168.23.4"));
	UserListControl.SetItemText(3, 1, _T("192.168.23.4"));
	UserListControl.SetItemText(3, 2, _T("192.168.23.2"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLanChatByWCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLanChatByWCDlg::OnPaint()
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
HCURSOR CLanChatByWCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLanChatByWCDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CLanChatByWCDlg::OnLbnSelchangeList7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CLanChatByWCDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}




LRESULT CLanChatByWCDlg::HandleMyMsg(WPARAM wParam, LPARAM lParam)
{
	Message *msg;
	msg = (Message*)lParam;
	
	AfxMessageBox((CString(msg->content.c_str())));
	return NULL;
}

LRESULT CLanChatByWCDlg::HandleUserListChange(WPARAM wParam, LPARAM lParam)
{
	sessions = sessionManager->getSessions();
	vector<Session*>::iterator iter;
	for (iter = sessions.begin(); iter != sessions.end(); iter++){
		Session* session = *iter;
		User	user = session->m_user;
		long id = user.ID;
		char  idStr[10];
		sprintf(idStr, "%d", id);
		string name = user.name;
	//	long id = user->ID;

		UserListControl.InsertItem(2, CString(name.c_str()));
		UserListControl.SetItemText(2, 1, CString(idStr));
		UserListControl.SetItemText(2, 2, CString(idStr));
	}
	return 0;
}




void CLanChatByWCDlg::OnLvnItemDClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1){
	 //sessions->;
		SessionManager* manager = SessionManager::GetInstance();

		CString selectUserID = UserListControl.GetItemText(pNMListView->iItem, 2);
		long lUserID = 0;
		lUserID = _ttol(selectUserID);

		Session* session = manager->getSessionByUserID(lUserID);


		ChatDialog* chatDialg = new ChatDialog(this, session);
		chatDialg->Create(IDD_CHATDIALOG,this);
		chatDialg->ShowWindow(SW_SHOW);
		//
		//chatDialg_.DoModal();
		//AfxMessageBox(selectUserIp);

	}
}
