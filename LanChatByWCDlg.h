
// LanChatByWCDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "SessionManager.h"
// CLanChatByWCDlg 对话框
class CLanChatByWCDlg : public CDialogEx
{
// 构造
public:
	vector<Session*> sessions;
	SessionManager* sessionManager;
	CLanChatByWCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LANCHATBYWC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeList7();
	afx_msg void OnBnClickedCancel();
	afx_msg LRESULT HandleMyMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HandleUserListChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeEdit1();
	CListCtrl UserListControl;
	afx_msg void OnLvnItemDClickList(NMHDR *pNMHDR, LRESULT *pResult);
};
