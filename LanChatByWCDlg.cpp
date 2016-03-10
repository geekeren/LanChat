
// LanChatByWCDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CLanChatByWCDlg 对话框



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


// CLanChatByWCDlg 消息处理程序

BOOL CLanChatByWCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	DataManager* dataManager;
	dataManager = DataManager::getInstance();
	dataManager->startDiscoverServer();


	sessionManager = SessionManager::GetInstance();

	//添加列表项
	CRect rect;
	UserListControl.GetClientRect(&rect);
	// 获取编程语言列表视图控件的位置和大小   
	UserListControl.SetExtendedStyle(UserListControl.GetExtendedStyle()|LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// 为列表视图控件添加三列   

	UserListControl.InsertColumn(0, _T("用户名"), LVCFMT_CENTER, rect.Width() / 2, 0);
	UserListControl.InsertColumn(1, _T("IP"), LVCFMT_CENTER, rect.Width() / 2, 0);
	UserListControl.InsertColumn(2, _T("ID"), LVCFMT_CENTER,2 , 0);
	// 在列表视图控件中插入列表项，并设置列表子项文本   
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLanChatByWCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLanChatByWCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLanChatByWCDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void CLanChatByWCDlg::OnLbnSelchangeList7()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CLanChatByWCDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
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
