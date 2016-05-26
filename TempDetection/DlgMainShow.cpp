// DlgMainShow.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgMainShow.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "OnDrawView.h"

extern double LastRecvTemp[30][4][12];
extern int LastAlarmStatus[30][4][12];
extern int IntUSR;
extern int LastRecvPower[30][4][12];
extern int ViewCount;
extern int m_page_count;
// CDlgMainShow 对话框

IMPLEMENT_DYNAMIC(CDlgMainShow, CPropertyPage)

CDlgMainShow::CDlgMainShow()
	: CPropertyPage(CDlgMainShow::IDD)
{
	v_Title.push_back(&m_Title001);
	v_Title.push_back(&m_Title002);
	v_Title.push_back(&m_Title003);
	v_Title.push_back(&m_Title004);
	v_Title.push_back(&m_Title005);
	v_Title.push_back(&m_Title006);
	v_Title.push_back(&m_Title007);
	v_Title.push_back(&m_Title008);
	v_Title.push_back(&m_Title009);
	v_Title.push_back(&m_Title010);
	v_Title.push_back(&m_Title011);
	v_Title.push_back(&m_Title012);
	v_Title.push_back(&m_Title013);
	v_Title.push_back(&m_Title014);
	v_Title.push_back(&m_Title015);
	v_Title.push_back(&m_Title016);
	v_Title.push_back(&m_Title017);
	v_Title.push_back(&m_Title018);
	v_Title.push_back(&m_Title019);
	v_Title.push_back(&m_Title020);
	v_Title.push_back(&m_Title021);
	v_Title.push_back(&m_Title022);
	v_Title.push_back(&m_Title023);
	v_Title.push_back(&m_Title024);
	v_Title.push_back(&m_Title025);

	v_Power.push_back(&m_power_001);
	v_Power.push_back(&m_power_002);
	v_Power.push_back(&m_power_003);
	v_Power.push_back(&m_power_004);
	v_Power.push_back(&m_power_005);
	v_Power.push_back(&m_power_006);
	v_Power.push_back(&m_power_007);
	v_Power.push_back(&m_power_008);
	v_Power.push_back(&m_power_009);
	v_Power.push_back(&m_power_010);
	v_Power.push_back(&m_power_011);
	v_Power.push_back(&m_power_012);
	v_Power.push_back(&m_power_013);
	v_Power.push_back(&m_power_014);
	v_Power.push_back(&m_power_015);
	v_Power.push_back(&m_power_016);
	v_Power.push_back(&m_power_017);
	v_Power.push_back(&m_power_018);
	v_Power.push_back(&m_power_019);
	v_Power.push_back(&m_power_020);
	v_Power.push_back(&m_power_021);
	v_Power.push_back(&m_power_022);
	v_Power.push_back(&m_power_023);
	v_Power.push_back(&m_power_024);
	v_Power.push_back(&m_power_025);

	v_Temp.push_back(&m_Tchart_temp_001);
	v_Temp.push_back(&m_Tchart_temp_002);
	v_Temp.push_back(&m_Tchart_temp_003);
	v_Temp.push_back(&m_Tchart_temp_004);
	v_Temp.push_back(&m_Tchart_temp_005);
	v_Temp.push_back(&m_Tchart_temp_006);
	v_Temp.push_back(&m_Tchart_temp_007);
	v_Temp.push_back(&m_Tchart_temp_008);
	v_Temp.push_back(&m_Tchart_temp_009);
	v_Temp.push_back(&m_Tchart_temp_010);
	v_Temp.push_back(&m_Tchart_temp_011);
	v_Temp.push_back(&m_Tchart_temp_012);
	v_Temp.push_back(&m_Tchart_temp_013);
	v_Temp.push_back(&m_Tchart_temp_014);
	v_Temp.push_back(&m_Tchart_temp_015);
	v_Temp.push_back(&m_Tchart_temp_016);
	v_Temp.push_back(&m_Tchart_temp_017);
	v_Temp.push_back(&m_Tchart_temp_018);
	v_Temp.push_back(&m_Tchart_temp_019);
	v_Temp.push_back(&m_Tchart_temp_020);
	v_Temp.push_back(&m_Tchart_temp_021);
	v_Temp.push_back(&m_Tchart_temp_022);
	v_Temp.push_back(&m_Tchart_temp_023);
	v_Temp.push_back(&m_Tchart_temp_024);
	v_Temp.push_back(&m_Tchart_temp_025);
}

CDlgMainShow::~CDlgMainShow()
{
}

void CDlgMainShow::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_IPANELX001, m_Title001);
	DDX_Control(pDX, IDC_IPANELX002, m_Title002);
	DDX_Control(pDX, IDC_IPANELX003, m_Title003);
	DDX_Control(pDX, IDC_IPANELX004, m_Title004);
	DDX_Control(pDX, IDC_IPANELX005, m_Title005);
	DDX_Control(pDX, IDC_IPANELX006, m_Title006);
	DDX_Control(pDX, IDC_IPANELX007, m_Title007);
	DDX_Control(pDX, IDC_IPANELX008, m_Title008);
	DDX_Control(pDX, IDC_IPANELX009, m_Title009);
	DDX_Control(pDX, IDC_IPANELX010, m_Title010);
	DDX_Control(pDX, IDC_IPANELX011, m_Title011);
	DDX_Control(pDX, IDC_IPANELX012, m_Title012);
	DDX_Control(pDX, IDC_IPANELX013, m_Title013);
	DDX_Control(pDX, IDC_IPANELX014, m_Title014);
	DDX_Control(pDX, IDC_IPANELX015, m_Title015);
	DDX_Control(pDX, IDC_IPANELX016, m_Title016);
	DDX_Control(pDX, IDC_IPANELX017, m_Title017);
	DDX_Control(pDX, IDC_IPANELX018, m_Title018);
	DDX_Control(pDX, IDC_IPANELX019, m_Title019);
	DDX_Control(pDX, IDC_IPANELX020, m_Title020);
	DDX_Control(pDX, IDC_IPANELX021, m_Title021);
	DDX_Control(pDX, IDC_IPANELX022, m_Title022);
	DDX_Control(pDX, IDC_IPANELX023, m_Title023);
	DDX_Control(pDX, IDC_IPANELX024, m_Title024);
	DDX_Control(pDX, IDC_IPANELX025, m_Title025);


	DDX_Control(pDX, IDC_TCHART_POWER001, m_power_001);
	DDX_Control(pDX, IDC_TCHART_POWER002, m_power_002);
	DDX_Control(pDX, IDC_TCHART_POWER003, m_power_003);
	DDX_Control(pDX, IDC_TCHART_POWER004, m_power_004);
	DDX_Control(pDX, IDC_TCHART_POWER005, m_power_005);
	DDX_Control(pDX, IDC_TCHART_POWER006, m_power_006);
	DDX_Control(pDX, IDC_TCHART_POWER007, m_power_007);
	DDX_Control(pDX, IDC_TCHART_POWER008, m_power_008);
	DDX_Control(pDX, IDC_TCHART_POWER009, m_power_009);
	DDX_Control(pDX, IDC_TCHART_POWER010, m_power_010);
	DDX_Control(pDX, IDC_TCHART_POWER011, m_power_011);
	DDX_Control(pDX, IDC_TCHART_POWER012, m_power_012);
	DDX_Control(pDX, IDC_TCHART_POWER013, m_power_013);
	DDX_Control(pDX, IDC_TCHART_POWER014, m_power_014);
	DDX_Control(pDX, IDC_TCHART_POWER015, m_power_015);
	DDX_Control(pDX, IDC_TCHART_POWER016, m_power_016);
	DDX_Control(pDX, IDC_TCHART_POWER017, m_power_017);
	DDX_Control(pDX, IDC_TCHART_POWER018, m_power_018);
	DDX_Control(pDX, IDC_TCHART_POWER019, m_power_019);
	DDX_Control(pDX, IDC_TCHART_POWER020, m_power_020);
	DDX_Control(pDX, IDC_TCHART_POWER021, m_power_021);
	DDX_Control(pDX, IDC_TCHART_POWER022, m_power_022);
	DDX_Control(pDX, IDC_TCHART_POWER023, m_power_023);
	DDX_Control(pDX, IDC_TCHART_POWER024, m_power_024);
	DDX_Control(pDX, IDC_TCHART_POWER025, m_power_025);

	DDX_Control(pDX, IDC_TCHART_SHOW_001, m_Tchart_temp_001);
	DDX_Control(pDX, IDC_TCHART_SHOW_002, m_Tchart_temp_002);
	DDX_Control(pDX, IDC_TCHART_SHOW_003, m_Tchart_temp_003);
	DDX_Control(pDX, IDC_TCHART_SHOW_004, m_Tchart_temp_004);
	DDX_Control(pDX, IDC_TCHART_SHOW_005, m_Tchart_temp_005);
	DDX_Control(pDX, IDC_TCHART_SHOW_006, m_Tchart_temp_006);
	DDX_Control(pDX, IDC_TCHART_SHOW_007, m_Tchart_temp_007);
	DDX_Control(pDX, IDC_TCHART_SHOW_008, m_Tchart_temp_008);
	DDX_Control(pDX, IDC_TCHART_SHOW_009, m_Tchart_temp_009);
	DDX_Control(pDX, IDC_TCHART_SHOW_010, m_Tchart_temp_010);
	DDX_Control(pDX, IDC_TCHART_SHOW_011, m_Tchart_temp_011);
	DDX_Control(pDX, IDC_TCHART_SHOW_012, m_Tchart_temp_012);
	DDX_Control(pDX, IDC_TCHART_SHOW_013, m_Tchart_temp_013);
	DDX_Control(pDX, IDC_TCHART_SHOW_014, m_Tchart_temp_014);
	DDX_Control(pDX, IDC_TCHART_SHOW_015, m_Tchart_temp_015);
	DDX_Control(pDX, IDC_TCHART_SHOW_016, m_Tchart_temp_016);
	DDX_Control(pDX, IDC_TCHART_SHOW_017, m_Tchart_temp_017);
	DDX_Control(pDX, IDC_TCHART_SHOW_018, m_Tchart_temp_018);
	DDX_Control(pDX, IDC_TCHART_SHOW_019, m_Tchart_temp_019);
	DDX_Control(pDX, IDC_TCHART_SHOW_020, m_Tchart_temp_020);
	DDX_Control(pDX, IDC_TCHART_SHOW_021, m_Tchart_temp_021);
	DDX_Control(pDX, IDC_TCHART_SHOW_022, m_Tchart_temp_022);
	DDX_Control(pDX, IDC_TCHART_SHOW_023, m_Tchart_temp_023);
	DDX_Control(pDX, IDC_TCHART_SHOW_024, m_Tchart_temp_024);
	DDX_Control(pDX, IDC_TCHART_SHOW_025, m_Tchart_temp_025);


}


BEGIN_MESSAGE_MAP(CDlgMainShow, CPropertyPage)
	ON_WM_SIZE()
//	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CDlgMainShow 消息处理程序


void CDlgMainShow::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	if(nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)//窗体大小发生变动。处理函数resize
	{
		float fsp[2];
		POINT Newp; //获取现在对话框的大小
		CRect recta;  
		GetClientRect(&recta);     //取客户区大小
		Newp.x=recta.right-recta.left;
		Newp.y=recta.bottom-recta.top;
		fsp[0]=(float)Newp.x/oldSize.x;
		fsp[1]=(float)Newp.y/oldSize.y;
		CRect Rect;
		int woc;
		CPoint OldTLPoint,TLPoint; //左上角
		CPoint OldBRPoint,BRPoint; //右下角
		HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件
		while(hwndChild)  
		{  
			woc=::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]);
			BRPoint.y = long(OldBRPoint.y *fsp[1]);
			Rect.SetRect(TLPoint,BRPoint);
			//GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);  
		}
		oldSize=Newp;
	}
	// TODO: 在此处添加消息处理程序代码
}


BOOL CDlgMainShow::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// TODO:  在此添加额外的初始化
	for(vector<CTchart_power*>::iterator i = v_Power.begin(); i != v_Power.end(); ++i)
	{
		(*i)->AddSeries(0);
		(*i)->CTChart::Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
		(*i)->CTChart::Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
		(*i)->CTChart::Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
		(*i)->CTChart::Series(0).GetAsLinearGauge().SetValue(0);
	}
	int client_count = 1;
	CString count;
	for(vector<CIpanelx*>::iterator j = v_Title.begin(); j != v_Title.end(); ++j)
	{
		count.Format(_T("%03d"),client_count++);
		(*j)->put_TitleText("终端"+count+"：未知");
	}

	for(vector<CTchart_power*>::iterator k = v_Temp.begin(); k!= v_Temp.end(); ++k)
	{
		(*k)->CTChart::Series(0).GetAsNumericGauge().SetValue(0);
	}
	CRect rect;  
	GetClientRect(&rect);  
	oldSize.x = rect.right - rect.left;  
	oldSize.y = rect.bottom - rect.top;  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgMainShow::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	int m_count = pMain->getPageCount();
	int client_count = 1;
	CString count;
	switch(m_count)
	{
		case 1:
			client_count=26;
			break;
		case 2:
			client_count=51;
			break;
		case 3:
			client_count=76;
			break;
		default:
			break;
	}
	for(vector<CIpanelx*>::iterator j = v_Title.begin(); j != v_Title.end(); ++j)
	{
		count.Format(_T("%03d"),client_count++);
		(*j)->put_TitleText("终端"+count+"：未知");
	}

	return CPropertyPage::OnSetActive();
}
