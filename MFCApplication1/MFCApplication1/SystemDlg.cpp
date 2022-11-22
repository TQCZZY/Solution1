﻿// SystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "SystemDlg.h"
#include "PropertyDlg.h"
#include "ListDlg.h"


// SystemDlg 对话框

IMPLEMENT_DYNAMIC(SystemDlg, CDialogEx)

SystemDlg::SystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SystemDlg::~SystemDlg()
{
}

void SystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(SystemDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &SystemDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_REVERSE, &SystemDlg::OnBnClickedButtonReverse)
	ON_BN_CLICKED(IDC_BUTTON3, &SystemDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &SystemDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &SystemDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &SystemDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// SystemDlg 消息处理程序


void SystemDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog* pdlg = (CDialog*)AfxGetMainWnd();//pdlg为主窗口的的指针
	pdlg->DestroyWindow();
	CDialogEx::OnClose();//关闭主窗口的方式
}


BOOL SystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	m_List.InsertColumn(0, _T("商品类型"),0,200/*宽度*/);
	m_List.InsertColumn(1, _T("进货时间"),0,200);
	m_List.InsertColumn(2, _T("商品库存"),0,200);
	m_List.InsertColumn(3, _T("货架编号"), 0, 200);

	CString itemName,snum,time,thing;
	for(int i=0;i<10;i++)
	{
		itemName.Format(_T("itemName=%d"),i);
		time.Format(_T("2008-05-13 09:0%d"),i);
		snum.Format(_T("%d"), i);
		thing.Format(_T("%d"), i);
		m_List.InsertItem(i,itemName);//第一列数据
		m_List.SetItemText(i, 1, time);
		m_List.SetItemText(i, 2, snum);
		m_List.SetItemText(i, 3, thing);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void SystemDlg::OnBnClickedButton1()//全选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i,TRUE);
	}
}


void SystemDlg::OnBnClickedButtonReverse()//反选
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, !m_List.GetCheck(i));
	}
}


void SystemDlg::OnBnClickedButton3()//增加
{
	// TODO: 在此添加控件通知处理程序代码
	PropertyDlg dlg;
	dlg.DoModal();//点击增加，弹出子对话框2
	int nCount=m_List.GetItemCount();
	if (dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty() || dlg.sThing.IsEmpty())
		return;
	m_List.InsertItem(nCount,dlg.sType);//新建类型
	m_List.SetItemText(nCount, 1, dlg.sDate);
	m_List.SetItemText(nCount, 2, dlg.sNumber);
	m_List.SetItemText(nCount, 3, dlg.sThing);


}


void SystemDlg::OnBnClickedButton4()//删除
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state=m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
}


void SystemDlg::OnBnClickedButton5()//修改
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			PropertyDlg dlg;
			dlg.DoModal();//弹窗
			if (dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty()||dlg.sThing.IsEmpty())
				return;
			m_List.SetItemText(i, 0, dlg.sType);
			m_List.SetItemText(i, 1, dlg.sDate);
			m_List.SetItemText(i, 2, dlg.sNumber);
			m_List.SetItemText(i, 3, dlg.sThing);
		}
		
	}
}


void SystemDlg::OnBnClickedButton2()//货架详情
{
	// TODO: 在此添加控件通知处理程序代码
	ListDlg dlg;
	dlg.DoModal();
}