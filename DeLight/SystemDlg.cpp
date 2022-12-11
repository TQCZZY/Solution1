﻿// SystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "resource.h"
#include <string>
#include <vector>
#include "List.h"
#include "SystemDlg.h"
#include "PswDlg.h"
#include "GoodsMngmntDlg.h"
#include "ShelfListDlg.h"
#include "QueryDlg.h"
#include "SearchMethodDlg.h"
#include "map.hpp"
#include "Lines.hpp"
#include "Excel.hpp"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// SystemDlg 对话框

IMPLEMENT_DYNAMIC(SystemDlg, CDialogEx)

SystemDlg::SystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSTEMDLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

SystemDlg::~SystemDlg()
{
}

void SystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SYSDLG_LIST, m_List);
}

BEGIN_MESSAGE_MAP(SystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SYSDLG_SLFDTL, &SystemDlg::OnBnClickedSlfDtl)
	ON_BN_CLICKED(IDC_SYSDLG_SEARCH, &SystemDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_REMOTEQUERY, &SystemDlg::OnBnClickedRemotequery)
	ON_BN_CLICKED(IDC_GLBTOEXCEL, &SystemDlg::OnBnClickedGlbtoexcel)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_NM, &SystemDlg::OnBnClickedSortnm)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_DT, &SystemDlg::OnBnClickedSortdt)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_QT, &SystemDlg::OnBnClickedSortqt)
	ON_BN_CLICKED(IDC_SYSDLG_SORT_SF, &SystemDlg::OnBnClickedSortsf)
	ON_BN_CLICKED(IDC_SYSDLG_SELDST, &SystemDlg::OnBnClickedSysdlgSeldst)
	ON_COMMAND(IDM_QUIT, &SystemDlg::OnQuit)
	ON_COMMAND(IDM_INBOUND, &SystemDlg::OnInbound)
	ON_COMMAND(IDM_OUTBOUND, &SystemDlg::OnOutbound)
	ON_COMMAND(IDM_MODIFY, &SystemDlg::OnModify)
	ON_COMMAND(IDM_SELALL, &SystemDlg::OnSelall)
	ON_COMMAND(IDM_REVSEL, &SystemDlg::OnRevsel)
	ON_COMMAND(IDM_SORTBYNAME, &SystemDlg::OnSortbyname)
	ON_COMMAND(IDM_SORTBYTIME, &SystemDlg::OnSortbytime)
END_MESSAGE_MAP()

// SystemDlg 消息处理程序

BOOL SystemDlg::OnInitDialog()
{
	PswDlg d;
	d.DoModal();
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	head->next = NULL;
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT/*整行选中*/ | LVS_EX_CHECKBOXES/*复选框*/);//扩展样式

	m_List.InsertColumn(0, _T("商品名称"),0,200/*宽度*/);
	m_List.InsertColumn(1, _T("进货时间"),0,200);
	m_List.InsertColumn(2, _T("商品库存"),0,200);
	m_List.InsertColumn(3, _T("货架编号"), 0, 200);

	//CString itemName,snum,time,thing;
	for(int i=0;i<Com.size(); i++)
	{
		m_List.InsertItem(i,Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}

	m_Menubar.LoadMenu(IDR_SYSDLG_MENUBAR);
	SetMenu(&m_Menubar);
	m_hAcc = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_SYSDLG_ACCELERATOR));

	return TRUE;  // return TRUE unless you set the focus to a control
}

void SystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void SystemDlg::OnPaint()
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
HCURSOR SystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void SystemDlg::OnBnClickedSlfDtl()//货架详情
{
	// TODO: 在此添加控件通知处理程序代码
	ShelfListDlg dlg;
	dlg.DoModal();
}

void SystemDlg::OnBnClickedSortnm()//排序1
{
}

void SystemDlg::OnBnClickedSortdt()//排序2
{
}

void SystemDlg::OnBnClickedSortqt()//排序3
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(2);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}

void SystemDlg::OnBnClickedSortsf()//排序4
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(3);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}

void SystemDlg::OnBnClickedSearch()
{
	SearchMethodDlg dlg;
	dlg.DoModal();
}

CQueryDlg qd;
void SystemDlg::OnBnClickedRemotequery()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return;
	}
	if (!qd.m_hWnd)
	{
		qd.Create(IDD_REMOTEQUERY_DIALOG, this);
	}
	qd.ShowWindow(SW_SHOW);
}

void SystemDlg::OnBnClickedGlbtoexcel()
{
	int item;
	item = MessageBox(L"导出完毕后,是否自动打开导出的图表?", L"自动启动Excel", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2);
	MessageBox(L"你可以在你选择的目录下新建受支持格式的文档;或者你也可以从存在的文档中选择一个,但是这可能会导致原有的数据因被覆盖而丢失.", L"当心数据丢失", MB_ICONINFORMATION);
	CString Filters = L"Excel 工作簿(*.xlsx)|*.xlsx|Excel 97-2003工作簿(*.xls)|*.xls|文本文档(含有制表符)(*.txt)|*.txt||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_CREATEPROMPT | OFN_HIDEREADONLY, Filters);
	dlg.m_ofn.lpstrTitle = L"打开Excel文档";
	if (dlg.DoModal() == IDOK)
	{
		std::vector<std::string> nm;
		std::vector<std::string> qt;
		std::vector<std::string> dt;
		std::vector<std::string> sf;
		USES_CONVERSION;
		transform(true);
		for (size_t i = 0; i < Com.size(); i++)
		{
			nm.push_back(W2A(Com[i].name));
			qt.push_back(W2A(Com[i].num));
			dt.push_back(W2A(Com[i].time));
			sf.push_back(W2A(Com[i].shelf));
		}
		setInfo(nm, qt, dt, sf);
		global2Excel(dlg.GetPathName());
	}
}

ULONG WINAPI GetRouteThread(LPVOID p) {
	while (true)
	{
		ReceivePoints(GetRoute(SendPoints()));
	}
	return 0;
}

void SystemDlg::OnBnClickedSysdlgSeldst()
{
	CreateThread(NULL, 0, GetRouteThread, NULL, NULL, NULL);//创建一个新线程
	CreateMapWindow(SW_SHOW);
}

BOOL SystemDlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYFIRST <= (pMsg->message) && WM_KEYLAST >= (pMsg->message))
	{
		HACCEL hAccel = m_hAcc;
		if (hAccel && ::TranslateAccelerator(m_hWnd, hAccel, pMsg))
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void SystemDlg::OnQuit()
{
	// TODO: Ask Whether To Save Data
	CDialogEx::OnOK();
}

void SystemDlg::OnInbound()
{
	GoodsMngmntDlg dlg;
	if (IDCANCEL == dlg.DoModal(L"", L"", L"", L"", false) ||//点击增加，弹出子对话框2
		dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty() || dlg.sShelf.IsEmpty())
		return;
	int nCount = m_List.GetItemCount();
	m_List.InsertItem(nCount, dlg.sType);//新建类型
	m_List.SetItemText(nCount, 1, dlg.sDate);
	m_List.SetItemText(nCount, 2, dlg.sNumber);
	m_List.SetItemText(nCount, 3, dlg.sShelf);
	Good_Info new_good;
	USES_CONVERSION;
	new_good.name = W2A(dlg.sType);

	std::string sou4 = W2A(dlg.sDate);
	Time t = { 0,0,0 };
	int p = 0;
	while (sou4[p] != '-') {
		t.year *= 10;
		t.year += sou4[p++] - '0';
	}
	p++;
	while (sou4[p] != '-') {
		t.month *= 10;
		t.month += sou4[p++] - '0';
	}
	p++;
	while (sou4[p] != '\0') {
		t.date *= 10;
		t.date += sou4[p++] - '0';
	}
	new_good.time.year = t.year;
	new_good.time.month = t.month;
	new_good.time.date = t.date;

	new_good.amount = _ttoi(dlg.sNumber);
	new_good.location = _ttoi(dlg.sShelf);
	Insert(new_good);
	transform(true);
}

void SystemDlg::OnOutbound()
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			Delete(Com[i].code);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
	transform(true);
}

void SystemDlg::OnModify()
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			GoodsMngmntDlg dlg;
			if (IDCANCEL == dlg.DoModal(Com[i].name, Com[i].num, Com[i].time, Com[i].shelf, false) ||//弹窗
				dlg.sType.IsEmpty() || dlg.sDate.IsEmpty() || dlg.sNumber.IsEmpty() || dlg.sShelf.IsEmpty())
				return;
			m_List.SetItemText(i, 0, dlg.sType);
			m_List.SetItemText(i, 1, dlg.sDate);
			m_List.SetItemText(i, 2, dlg.sNumber);
			m_List.SetItemText(i, 3, dlg.sShelf);
			Delete(Com[i].code);
			Good_Info new_good;
			USES_CONVERSION;
			new_good.name = W2A(dlg.sType);

			std::string sou4 = W2A(dlg.sDate);
			Time t = { 0,0,0 };
			int p = 0;
			while (sou4[p] != '-') {
				t.year *= 10;
				t.year += sou4[p++] - '0';
			}
			p++;
			while (sou4[p] != '-') {
				t.month *= 10;
				t.month += sou4[p++] - '0';
			}
			p++;
			while (sou4[p] != '\0') {
				t.date *= 10;
				t.date += sou4[p++] - '0';
			}
			new_good.time.year = t.year;
			new_good.time.month = t.month;
			new_good.time.date = t.date;

			new_good.amount = _ttoi(dlg.sNumber);
			new_good.location = _ttoi(dlg.sShelf);
			Insert(new_good, i);
		}
	}
	transform(true);
}

void SystemDlg::OnSelall()
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}
}

void SystemDlg::OnRevsel()
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, !m_List.GetCheck(i));
	}
}

void SystemDlg::OnSortbyname()
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}
	Sort(1);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}

void SystemDlg::OnSortbytime()
{
	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		m_List.SetCheck/*设置选中状态*/(i, TRUE);
	}

	for (int i = 0; i < m_List.GetItemCount/*获取条目的数量*/(); i++)
	{
		BOOL state = m_List.GetCheck(i);
		if (state)
		{
			m_List.DeleteItem(i);
			i--;//若不i--则不能多项同时删除，因为当删除0栏后，1栏会为0栏，就删不掉了
		}
	}

	Sort(4);
	transform(true);
	for (int i = 0; i < Com.size(); i++)
	{
		m_List.InsertItem(i, Com[i].name);//第一列数据
		m_List.SetItemText(i, 1, Com[i].time);
		m_List.SetItemText(i, 2, Com[i].num);
		m_List.SetItemText(i, 3, Com[i].shelf);
	}
}
