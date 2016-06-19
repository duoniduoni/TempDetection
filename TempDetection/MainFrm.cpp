
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "TempDetection.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <windows.h>
#include "MainFrm.h"
#include "TempDetectionView.h"
#include "OnDrawView.h"
#include "ShowMessageView.h"
#include "CommEdit.h"
#include "DlgCalibrate.h"
#include "DlgConfig.h"
#include "DlgPosition.h"
#include "DlgUserSet.h"
#include "DlgFactorySet.h"
#include "DlgUpdateFirmware.h"
#include "DlgChangeUser.h"
#include "DlgPowerControl.h"
#include "DlgAlarmHistory.h"
#include "DlgSetAlarm.h"
#include "DlgModifyReaderID.h"
#include "DlgCtlSingleReader.h"


static bool EnableTimer=FALSE;
static long SetTime=30;
LARGE_INTEGER litmp;
LONGLONG llQFreq,llQPartOld,llQPartNew;
double fFreq;
int m_page_count = 0;
UINT OneMilliSecondProc(LPVOID lParam); 


IMPLEMENT_DYNAMIC(CCommSplitWnd, CSplitterWnd)

CCommSplitWnd::CCommSplitWnd()
{
}

CCommSplitWnd::~CCommSplitWnd()
{
}
BEGIN_MESSAGE_MAP(CCommSplitWnd, CSplitterWnd)

END_MESSAGE_MAP()

int CCommSplitWnd::HitTest(CPoint pt)const
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ASSERT_VALID(this);
	return 0;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

unsigned char StartCMD[15]       ={0x00,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char StopCMD[15]        ={0x00,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char CallReaderCMD[15]  ={0x00,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char SynchronousCMD[15] ={0x00,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
int pageCount = 0;
int intCF;
int ViewCount = 0;
_ConnectionPtr m_pConnection;
CString strFN;
CString SystemLogPath;
CString strDD;
CString RecordID;
unsigned int m_FreqData[30][4][12]={0};
float m_TempData[30][4][12]={0};
int WrongFlagCount[4][12]={0};
int UserSetAlarmHigh;
int UserSetAlarmLow;
bool IndexReader[30]={0};
int AlarmCount;
bool AlarmSound;
bool intTemp2;
bool intTemp;
bool SearchFlag;
int intRDC;
int LoginDomainSet;
CString LoginName;
int IntUDR[30]={0};
CStringArray strRPA;
CStringArray strSPA;
int AlarmTempSave[2][30]={0};
int SensorPowerSet[30][4][12]={0};
int IntUSR;
int intUST = 200;
double LastRecvTemp[30][4][12]={0};
int LastRecvPower[30][4][12]={0};
int LastAlarmStatus[30][4][12]={0};
int IntUSRForCal;
int USSYN;
int SYNCount;
bool SendCMDStatus;
bool Menu_Communicate;
bool Menu_Exit;
bool Menu_StartMem;
bool Menu_StopMem;
bool Menu_Refresh;
bool Menu_Calibration;
bool Menu_UserSetPosition;
bool Menu_ReaderConfig;
bool Menu_PowerControl;
bool Menu_UpdateFirmware;
bool Menu_FactorySet;
bool Menu_UserSet;
bool Menu_ModifyReaderID;
bool Menu_ScanReader;
bool Menu_CtlSingleReader;
bool Menu_ChangeUser;
bool Menu_ShowAlarmHistory;
bool Menu_SetSilent;
bool Menu_SetAlarmTemp;

#define ID_TIMER_LOOP 1
#define ID_TIMER_WAIT 2
#define ID_TIMER_SEARCH 3
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_UPDATE_COMMAND_UI(ID_COMMUNICATE, &CMainFrame::OnUpdateCommunicate)
	ON_COMMAND(ID_CALIBRATION, &CMainFrame::OnCalibration)
	ON_UPDATE_COMMAND_UI(ID_USER_SET_POSITION, &CMainFrame::OnUpdateUserSetPosition)
	ON_COMMAND(ID_COMMUNICATE, &CMainFrame::OnCommunicate)
	ON_UPDATE_COMMAND_UI(ID_CALIBRATION, &CMainFrame::OnUpdateCalibration)
	ON_COMMAND(ID_USER_SET_POSITION, &CMainFrame::OnUserSetPosition)
	ON_COMMAND(ID_EXIT, &CMainFrame::OnExit)
	ON_UPDATE_COMMAND_UI(ID_EXIT, &CMainFrame::OnUpdateExit)
	ON_COMMAND(ID_READER_CONFIG, &CMainFrame::OnReaderConfig)
	ON_UPDATE_COMMAND_UI(ID_READER_CONFIG, &CMainFrame::OnUpdateReaderConfig)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_USER_SET, &CMainFrame::OnUserSet)
	ON_UPDATE_COMMAND_UI(ID_USER_SET, &CMainFrame::OnUpdateUserSet)
	ON_COMMAND(ID_FACTORY_SET, &CMainFrame::OnFactorySet)
	ON_UPDATE_COMMAND_UI(ID_FACTORY_SET, &CMainFrame::OnUpdateFactorySet)
	ON_COMMAND(ID_UPDATE_FIRMWARE, &CMainFrame::OnUpdateFirmware)
	ON_UPDATE_COMMAND_UI(ID_UPDATE_FIRMWARE, &CMainFrame::OnUpdateUpdateFirmware)
	ON_COMMAND(ID_START_MEM, &CMainFrame::OnStartMem)
	ON_UPDATE_COMMAND_UI(ID_START_MEM, &CMainFrame::OnUpdateStartMem)
	ON_COMMAND(ID_STOP_MEM, &CMainFrame::OnStopMem)
	ON_UPDATE_COMMAND_UI(ID_STOP_MEM, &CMainFrame::OnUpdateStopMem)
	ON_COMMAND(ID_CHANGE_USER, &CMainFrame::OnChangeUser)
	ON_UPDATE_COMMAND_UI(ID_CHANGE_USER, &CMainFrame::OnUpdateChangeUser)
	ON_COMMAND(ID_POWER_CONTROL, &CMainFrame::OnPowerControl)
	ON_UPDATE_COMMAND_UI(ID_POWER_CONTROL, &CMainFrame::OnUpdatePowerControl)
	ON_COMMAND(ID_REFRESH, &CMainFrame::OnRefresh)
	ON_UPDATE_COMMAND_UI(ID_REFRESH, &CMainFrame::OnUpdateRefresh)
	ON_COMMAND(ID_SET_ALARM_TEMP, &CMainFrame::OnSetAlarmTemp)
	ON_UPDATE_COMMAND_UI(ID_SET_ALARM_TEMP, &CMainFrame::OnUpdateSetAlarmTemp)
	ON_COMMAND(ID_SET_SILENT, &CMainFrame::OnSetSilent)
	ON_UPDATE_COMMAND_UI(ID_SET_SILENT, &CMainFrame::OnUpdateSetSilent)
	ON_COMMAND(ID_SHOW_ALARM_HISTORY, &CMainFrame::OnShowAlarmHistory)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ALARM_HISTORY, &CMainFrame::OnUpdateShowAlarmHistory)
	ON_COMMAND(ID_SCAN_READER, &CMainFrame::OnScanReader)
	ON_UPDATE_COMMAND_UI(ID_SCAN_READER, &CMainFrame::OnUpdateScanReader)
	ON_COMMAND(ID_CTL_SINGLE_READER, &CMainFrame::OnCtlSingleReader)
	ON_UPDATE_COMMAND_UI(ID_CTL_SINGLE_READER, &CMainFrame::OnUpdateCtlSingleReader)
	ON_COMMAND(ID_MODIFY_READR_ID, &CMainFrame::OnModifyReadrId)
	ON_UPDATE_COMMAND_UI(ID_MODIFY_READR_ID, &CMainFrame::OnUpdateModifyReadrId)
	ON_WM_TIMER()
	ON_MESSAGE(WM_UPDATETIME,OnUpdateTime)      //创建消息映射
//	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           
	ID_SEPARATOR,          
	ID_CONDITION,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
	: CountLoop(0)
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);

	intTemp2=FALSE;
	intTemp=0;
	intCF=0;
	SearchFlag=0;
	Menu_Communicate=TRUE;
	Menu_Exit=TRUE;
	Menu_StartMem=FALSE;
	Menu_StopMem=FALSE;
	Menu_Refresh=FALSE;
	Menu_Calibration=FALSE;
	Menu_UserSetPosition=FALSE;
	Menu_ReaderConfig=FALSE;
	Menu_PowerControl=FALSE;
	Menu_UpdateFirmware=FALSE;
	Menu_FactorySet=FALSE;
	Menu_UserSet=FALSE;
	Menu_ChangeUser=TRUE;
	Menu_ScanReader=FALSE;
	Menu_CtlSingleReader=FALSE;
	Menu_ShowAlarmHistory=FALSE;
	Menu_SetAlarmTemp=FALSE;
	Menu_ModifyReaderID=FALSE;

	TIMECAPS tc;
	MMRESULT bError;

	bError=timeGetDevCaps(&tc,sizeof(TIMECAPS)); 
	if(!bError==TIMERR_NOERROR) 	
	{ 
		MessageBox("Get system accuracy failed!");
	}
	wAccuracy=min(max(tc.wPeriodMin,TIMER_ACCURACY),tc.wPeriodMax);
	timeBeginPeriod(wAccuracy); 
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CMenu* pMenu=GetSystemMenu(FALSE);
	int x=pMenu->GetMenuItemCount();
	UINT pID=pMenu->GetMenuItemID(x-1);
	pMenu-> EnableMenuItem(pID,MF_DISABLED);

	if (!m_wndStatusBar.Create(this) ||!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // fail to create
	}	

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作:
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("未能创建状态栏\n");
	//	return -1;      // 未能创建
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	//m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	// 启用工具栏和停靠窗口菜单替换
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	//CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 加载用户定义的工具栏图像
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	//CList<UINT, UINT> lstBasicCommands;

	//lstBasicCommands.AddTail(ID_FILE_NEW);
	//lstBasicCommands.AddTail(ID_FILE_OPEN);
	//lstBasicCommands.AddTail(ID_FILE_SAVE);
	//lstBasicCommands.AddTail(ID_FILE_PRINT);
	//lstBasicCommands.AddTail(ID_APP_EXIT);
	//lstBasicCommands.AddTail(ID_EDIT_CUT);
	//lstBasicCommands.AddTail(ID_EDIT_PASTE);
	//lstBasicCommands.AddTail(ID_EDIT_UNDO);
	//lstBasicCommands.AddTail(ID_APP_ABOUT);
	//lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	//lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	//CMFCToolBar::SetBasicCommands(lstBasicCommands);
	
	if(!m_MSComm.Create(NULL,0,CRect(0,0,0,0),this,IDC_MSCOMM1)) 
	{ 
		AfxMessageBox( "创建控件失败 "); 
	} 
	
	HMODULE Positionmodule = GetModuleHandle(0); 
	char pPositionFileName[MAX_PATH]; 
	GetModuleFileName(Positionmodule, pPositionFileName, MAX_PATH); 

	CString csPositionFullPath(pPositionFileName); 
	int nPos = csPositionFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		AfxMessageBox("找不到SystemInstall.ini配置文件"); 
	strFN=csPositionFullPath.Left( nPos ); 
	SystemLogPath=strFN+"\\SysLog.log";
	strFN=strFN+"\\SystemInstall.ini";

	CreateDataBase();
	SetStatusBar(2,"登录用户"+LoginName);
	ReadPositionFromDB();
	ReadINIFile(strFN);	
	QueryPerformanceFrequency(&litmp);
	llQFreq=litmp.QuadPart;
	fFreq=(double)llQFreq;

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	CRect rs;  
	GetClientRect(&rs); 
	m_wndSplitter.CreateStatic( this, 1, 2 );
	m_wndSplitter.SetColumnInfo( 0, rs.right/6, 50 );

	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CTempDetectionView), CSize(rs.right/6, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(COnDrawView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	return TRUE; 
	SetActiveView((CView*)m_wndSplitter.GetPane(0,1));
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN);
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
	cs.y = cs.cy;
	cs.x = cs.cx;
	//cs.style &= ~WS_MAXIMIZEBOX; //禁止窗口最大化

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE );
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnUpdateCommunicate(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_Communicate); 
}


void CMainFrame::OnUpdateUserSetPosition(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_UserSetPosition); 
}


void CMainFrame::OnUpdateCalibration(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_Calibration); 
}

void CMainFrame::OnUpdateFactorySet(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_FactorySet); 
}


void CMainFrame::OnUpdateUserSet(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_UserSet); 
}


void CMainFrame::OnUpdateChangeUser(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_ChangeUser); 
}


void CMainFrame::OnUpdatePowerControl(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_PowerControl); 
}


void CMainFrame::OnUpdateUpdateFirmware(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_UpdateFirmware); 
}


BEGIN_EVENTSINK_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_EVENTSINK_MAP(CAboutDlg)
	ON_EVENT(CMainFrame, IDC_MSCOMM1, 1, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CMainFrame::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len;
	CString TemperText,FreqText,PowerText,temp;
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	//char RecvData[5000]={0};
	int count = 0 , frame = 0, endFlag =0, i = 0;
	
	if(m_MSComm.GetCommEvent()==2)
	{
		Sleep(2000);
		variant_inp=m_MSComm.GetInput(); 
		safearray_inp=variant_inp;  
		len=safearray_inp.GetOneDimSize(); 
		if (intTemp==1)
		{
			for(LONG k=0;k<len;k++)
				safearray_inp.GetElement(&k,&rxdata[k+intRDC]);
			safearray_inp.Clear();

			CString dbgInfo;
			dbgInfo.Format("zhangsong: recv data len is %d", len);
			OutputDebugString(dbgInfo);

			intRDC+=len;
			if (intRDC>=15)
			{
				if(0 ==(intRDC%15))
				{
					
					//for (i = 0; i < intRDC; i++)
					//{
					//	temp.Format(("%c"),rxdata[i]);
					//	m_AllReceiveData[rxdata[0]].Append(temp);
				//		temp.Empty();
				//	}
					//RecvCRC=GetCheckCode(RecvData,13);
					//if ((RecvCRC&0x00ff)==rxdata[14]&&((RecvCRC&0xff00)>>8)==rxdata[13])
					//{
					//	count = 0xffff&rxdata[3]+((0xffff&rxdata[2])<<8);
					//	frame = (0xffff&rxdata[4])<<8;
					//}
					
					if(rxdata[intRDC-11 - 1] & 0x08)
					{
						showData(rxdata[0],intRDC);
						//m_AllReceiveData[rxdata[0]].Empty();
						memset(rxdata,0,5000);
					}
					temp.Empty();
				}
			}
		}
	} 
}
void CMainFrame::showData(char index , int len)
{
	CString tmp("12345678"),battery,tmp_data;
	WORD RecvCRC = 0;
	unsigned char RecvData[15]={0};
	unsigned char *m_Data = new unsigned char[5000];
	memset(m_Data, 0, 5000);

	int index_id =0 , begin_index = 0 ,data_index = 0,data_index_second = 0;
	while(begin_index < len)
	{
		for(int i =0;i<15;i++)
		{
			RecvData[i] = rxdata[begin_index++];
		}
		RecvCRC=GetCheckCode(RecvData,13);
		if ((RecvCRC&0x00ff)!=RecvData[14]||((RecvCRC&0xff00)>>8)!=RecvData[13])
			return;
		for(int i=0;i<15;i++)
			RecvData[i] = 0;
		RecvCRC=0;
	}
	begin_index=0;
	while (begin_index < len)
	{
		begin_index+=5;         //jump to data

		for(int i=0;i<8;i++)
		{
			m_Data[data_index++] = rxdata[begin_index++];
		}

		begin_index+=2;         //jump over CRC
	}

	m_tempData[index].PANID=0xffff&m_Data[1]+((0xffff&m_Data[0])<<8);
	begin_index=2;

	/*
	//pair<map<CString, int>::iterator, bool> ret;  
	while(begin_index < data_index)
	{
		begin_index++;
		for(int i =0;i<8;i++)
		{
			tmp.SetAt(i,m_Data[begin_index++]);
		}
		m_MacAddress[index].insert(make_pair(tmp,index_id));
		data_index_second = m_MacAddress[index][tmp];
		m_tempData[index].dataFlag[data_index_second] = m_Data[begin_index-8];
		m_tempData[index].mac_address[data_index_second] = tmp;
		m_tempData[index].Temp[data_index_second] = 0xffff&m_Data[begin_index+1]+((0xffff&m_Data[begin_index])<<8);
		m_tempData[index].battery_level[data_index_second] = m_Data[begin_index+2];
		m_tempData[index].Power[data_index_second] = 0xffff&m_Data[begin_index+4]+((0xffff&m_Data[begin_index+3])<<8);
//		tmp.Empty();
		begin_index+=5;
	}
	*/
	for(int sensor_index = 0; sensor_index < data_index / 14; sensor_index ++)
	{
		m_tempData[index].dataFlag[sensor_index] = m_Data[begin_index];
		begin_index += 1;

		CString tmp_addr("12345678");
		for(int i =0;i<8;i++)
		{
			tmp_addr.SetAt(i,m_Data[begin_index + i]);
		}
		m_tempData[index].mac_address[sensor_index] = tmp;
		begin_index += 8;

		m_tempData[index].Temp[sensor_index] = 0xffff&m_Data[begin_index+1]+((0xffff&m_Data[begin_index])<<8);
		begin_index += 2;

		m_tempData[index].battery_level[sensor_index] = m_Data[begin_index];
		begin_index += 1;

		m_tempData[index].Power[sensor_index] = 0xffff&m_Data[begin_index+1]+((0xffff&m_Data[begin_index])<<8);
		begin_index += 2;
	}

	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	int power_value,dataCount,pageFlagCount;
	for(int i=0;i<100;i++)
	{
		if(0!=m_tempData[index].dataFlag[i]/* && 1!=m_tempData[index].dataFlag[i]*/)
			continue;
		if(m_tempData[index].Power[i] < -87)
			power_value=0;
		else if(m_tempData[index].Power[i] >= -87 && m_tempData[index].Power[i] < -77)
			power_value =25;
		else if(m_tempData[index].Power[i] >= -77 && m_tempData[index].Power[i] < -67)
			power_value =50;
		else if(m_tempData[index].Power[i] >= -67 && m_tempData[index].Power[i] < -57)
			power_value =75;
		else
			power_value =100;
		dataCount = i%25;
		pageFlagCount = i/25;
		tmp.Format(_T("%3d"),i+1);
		switch(pageFlagCount)
		{
		case 0:
			battery.Format(_T("%d"),m_tempData[index].battery_level[i]);
			pViewMainShow->pSheet->pDlgMainShow->v_Power[dataCount]->CTChart::Series(0).GetAsLinearGauge().SetValue(power_value);
			pViewMainShow->pSheet->pDlgMainShow->v_Temp[dataCount]->CTChart::Series(0).GetAsNumericGauge().SetValue(m_tempData[index].Temp[i]);
			pViewMainShow->pSheet->pDlgMainShow->v_Title[dataCount]->put_TitleText("终端"+tmp+"："+battery+"%");
			break;
		case 1:
			battery.Format(_T("%d"),m_tempData[index].battery_level[i]);
			pViewMainShow->pSheet->pDlgMainShow1->v_Power[dataCount]->CTChart::Series(0).GetAsLinearGauge().SetValue(power_value);
			pViewMainShow->pSheet->pDlgMainShow1->v_Temp[dataCount]->CTChart::Series(0).GetAsNumericGauge().SetValue(m_tempData[index].Temp[i]);
			pViewMainShow->pSheet->pDlgMainShow1->v_Title[dataCount]->put_TitleText("终端"+tmp+"："+battery+"%");
			break;
		case 2:
			battery.Format(_T("%d"),m_tempData[index].battery_level[i]);
			pViewMainShow->pSheet->pDlgMainShow2->v_Power[dataCount]->CTChart::Series(0).GetAsLinearGauge().SetValue(power_value);
			pViewMainShow->pSheet->pDlgMainShow2->v_Temp[dataCount]->CTChart::Series(0).GetAsNumericGauge().SetValue(m_tempData[index].Temp[i]);
			pViewMainShow->pSheet->pDlgMainShow2->v_Title[dataCount]->put_TitleText("终端"+tmp+"："+battery+"%");
			break;
		case 3:
			battery.Format(_T("%d"),m_tempData[index].battery_level[i]);
			pViewMainShow->pSheet->pDlgMainShow3->v_Power[dataCount]->CTChart::Series(0).GetAsLinearGauge().SetValue(power_value);
			pViewMainShow->pSheet->pDlgMainShow3->v_Temp[dataCount]->CTChart::Series(0).GetAsNumericGauge().SetValue(m_tempData[index].Temp[i]);
			pViewMainShow->pSheet->pDlgMainShow3->v_Title[dataCount]->put_TitleText("终端"+tmp+"："+battery+"%");
			break;
		default:
			break;
		}
//		tmp.Empty();
		battery.Empty();
	}

	delete []m_Data;
}

int CMainFrame::getPageCount()
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	return pageCount = pViewMainShow->pSheet->GetActiveIndex();
}

void CMainFrame::OnCommunicate()
{
	// TODO: 在此添加命令处理程序代码
	CString str;  
	str.Format(_T("%s, %s [L%d] "), __FILE__, __FUNCTION__, __LINE__);  
	str += "loging...";  
	OutputLog(SystemLogPath, str); 
	ActivePage();
	CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
	pViewMainShow->m_TreeCtl.EnableWindow(TRUE);
	CCommEdit m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUserSetPosition()
{
	// TODO: 在此添加命令处理程序代码
	CString str;  
	str.Format(_T("%s, %s [L%d] "), __FILE__, __FUNCTION__, __LINE__);  
	str += "loging...";  
	OutputLog(SystemLogPath, str); 

	CDlgPosition m_dlg;
	m_dlg.DoModal();
}




void CMainFrame::OnCalibration()
{
	// TODO: 在此添加命令处理程序代码
	CDlgCalibrate m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::CreateDataBase(void)
{
	CoInitialize(NULL);
	m_pConnection.CreateInstance(__uuidof(Connection));
	try
	{
		m_pConnection->Open(MYSQL_DRIVER,"root","123456",adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}
void CMainFrame::InsertIntoData(CString RecordID,CString ReaderID,CString AntID, CString SensorID,CString Temperature,CString RFPower,CString Frequency,CString RecordTime,CString Notes)
{
	try
	{
		_bstr_t strCmd="INSERT INTO DB_Data (RecordID,ReaderID,AntID,SensorID,Temperature,RFPower,Frequency,RecordTime,Notes) VALUES('"+RecordID+"','"+ReaderID+"','"+AntID+"','"+SensorID+"','"+Temperature+"','"+RFPower+"','"+Frequency+"','"+RecordTime+"','"+Notes+"')";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}
void CMainFrame::InsertIntoTest(CString S_Time)
{
	try
	{
		_bstr_t strCmd="INSERT INTO DB_Record (StartTime) VALUES('"+S_Time+"')";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}

}
CString CMainFrame::GetRecordID()
{
	_bstr_t bSQL ="select RecordID from DB_Record order by RecordID desc limit 0,1";
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open(bSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	return (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("RecordID");
}
void CMainFrame::UpdateTest(CString e_time)
{
	try
	{
		_bstr_t strCmd="UPDATE DB_Record SET EndTime='"+e_time+"' WHERE RecordID="+RecordID;
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}

BOOL CMainFrame::DBisOpen()
{
	if(m_pConnection )
		return m_pConnection->GetState() != adStateClosed;
	return FALSE;
}


void CMainFrame::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	if(MessageBox("确认退出","退出系统",MB_YESNO|MB_ICONQUESTION)==IDYES) 
	{
		this->SendMessage(WM_CLOSE);
	}	
}


void CMainFrame::OnUpdateExit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_Exit); 
}


void CMainFrame::OnReaderConfig()
{
	// TODO: 在此添加命令处理程序代码
	CDlgConfig m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateReaderConfig(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_ReaderConfig); 
}

void CMainFrame::SearchReader()
{
	if(intTemp2)
	{
		if(!intTemp)
		{
			if(AfxMessageBox("检测到端口已打开，是否扫描读卡器？",MB_YESNO)==IDYES)
			{
				StartMem();
				SearchFlag = 1;
				SetTimer(ID_TIMER_SEARCH,45000,NULL);
			}
		}
		else
			AfxMessageBox("请在停止测温的状态下扫描读卡器");
	}
	else
		AfxMessageBox("请先打开端口再继续操作");
}
unsigned int CMainFrame::ascii2hex(char *buf, int len)
{
	int i = 0, j = 0;  
	unsigned int ret = 0;  
	char p[2] = {0};  
	int tmp = 1;  
	for(i = 0; i<len; i++)
	{  
		memcpy(p,&buf[i],1);     
		switch (p[0])
		{  
		case 'A':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 10*tmp;  
			break;  
		case 'B':             
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 11*tmp;  
			break;  
		case 'C':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 12*tmp;  
			break;  
		case 'D':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 13*tmp;  
			break;  
		case 'E':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 14*tmp;  
			break;  
		case 'F':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 15*tmp;  
			break;  
		case 'a':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 10*tmp;  
			break;  
		case 'b':             
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 11*tmp;  
			break;  
		case 'c':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 12*tmp;  
			break;  
		case 'd':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 13*tmp;  
			break;  
		case 'e':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 14*tmp;  
			break;  
		case 'f':                 
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += 15*tmp;  
			break;  
		default:  
			tmp = 1;  
			for(j=0;j<len-1-i;j++)  
				tmp *= 16;  
			ret += atoi(p)*tmp;  
			break;  
		}  
	}  
	return ret;  
}
void CMainFrame::DataOperate(CString Reader,char Ant,char Sensor,unsigned int Power,unsigned int Frequence, int Temp)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	
}

void CMainFrame::DisturbData(char Reader,char Ant,char Sensor,int Temp ,unsigned int Power,unsigned int Frequence, char DataFlag)
{
	CString strTemp,strFreq,strPower,strTime,strDataFlag,strReader,strAnt,strSensor;
	double GetTemp;
	double TimeNow=COleDateTime::GetCurrentTime();
	if (Temp&0x8000)
	{
		unsigned int temp1=(~Temp+1)&0x0000ffff;
		int tempdata=temp1%16;
		GetTemp=(double)(temp1/16)+(double)tempdata/16;
		GetTemp=-GetTemp;
	} 
	else
	{
		unsigned int temp1=Temp;
		int tempdata=temp1%16;
		GetTemp=(double)(temp1/16)+(double)tempdata/16;
	}
	strTemp.Format("%.1f",GetTemp);
	strPower.Format("%d",Power);
	strFreq.Format("%u",Frequence);
	strTime.Format("%f",TimeNow);
	if(DataFlag==0x01)
		strDataFlag="能量低";
	else
		strDataFlag="干扰";
	strReader.Format("读卡器%d",Reader),strAnt.Format("天线%d",Ant+1),strSensor.Format("传感器%d",Sensor+1);
	InsertIntoData(RecordID,strReader,strAnt,strSensor,strTemp,strPower,strFreq,strTime,strDataFlag);
	strPower.ReleaseBuffer();
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int   nFullWidth=GetSystemMetrics(SM_CXSCREEN); 
	int   nFullHeight=GetSystemMetrics(SM_CYSCREEN);
	//lpMMI->ptMinTrackSize.x = nFullWidth ; 
	//lpMMI->ptMinTrackSize.y = nFullHeight ; 
	//lpMMI->ptMaxTrackSize.x = nFullWidth ; 
	//lpMMI->ptMaxTrackSize.y = nFullHeight; 
	lpMMI->ptMinTrackSize.x = 100 ; 
	lpMMI->ptMinTrackSize.y = 100;
	lpMMI->ptMaxTrackSize.x = 1024;
	lpMMI->ptMaxTrackSize.y = 750;
	CFrameWndEx::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::ActivePage(void)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	//pViewMainShow->m_sheet.SetActivePage(6); 
	pViewMainShow->m_sheet.SetActivePage(5); 
	pViewMainShow->m_sheet.SetActivePage(4); 
	pViewMainShow->m_sheet.SetActivePage(3); 
	pViewMainShow->m_sheet.SetActivePage(2); 
	pViewMainShow->m_sheet.SetActivePage(1); 
	pViewMainShow->m_sheet.SetActivePage(0); 
}


void CMainFrame::ClearShowMessage(void)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	pViewMainShow->pSheet->pDlgAlarmShow->m_CtlListAlarm.DeleteAllItems();
	AlarmCount=0;
}


void CMainFrame::OnUserSet()
{
	// TODO: 在此添加命令处理程序代码
	CDlgUserSet m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnFactorySet()
{
	// TODO: 在此添加命令处理程序代码
	CDlgFactorySet m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OutputLog(LPCTSTR logName, CString msg)
{
	try
	{
		CStdioFile outFile(logName, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		CString msLine;
		CTime tt = CTime::GetCurrentTime();

		msLine = tt.Format("[%Y-%B-%d %A, %H:%M:%S] ") + msg;
		msLine += "\n\r";

		outFile.SeekToEnd();
		outFile.WriteString( msLine );
		outFile.Close();
	}
	catch(CFileException *fx)
	{
		fx->Delete();
	}
}


void CMainFrame::OnStartMem()
{
	// TODO: 在此添加命令处理程序代码

	//ActivePage();
	//ClearShowMessage();
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	//pViewMainShow->pSheet->pDlgMainShow->m_Title023.put_TitleText("this");
	//pViewMainShow->pSheet->pDlgMainShow->m_power_001.AddSeries(0);
	
	//pViewMainShow->pSheet->pDlgMainShow->m_power_001.CTChart::Series(0).GetAsLinearGauge().SetValue(60);

	
	//pViewMainShow->pSheet->pDlgMainShow->m_Tchart_temp_001.CTChart::Series(0).GetAsNumericGauge().SetValue(-60.6);
	
		
	if (intTemp2)
	{

		CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
		pViewMainShow->SetButtonStatus(TRUE);
		pViewMainShow->StartMem();
		CTime currenttime=CTime::GetCurrentTime();   
		CString s_time=currenttime.Format("%Y-%m-%d %H:%M:%S"); 
		InsertIntoTest(s_time);	
		RecordID=GetRecordID();
		intRDC=0;
		SetTimer(ID_TIMER_WAIT,2000,NULL);
		intTemp=1;
		for (int k = 0; k < 30; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					m_FreqData[k][i][j]=0;
					m_TempData[k][i][j]=0;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				WrongFlagCount[i][j]=0;
			}
		}
		SetStatusBar(1,"开始测量");
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 12; k++)
				{
					LastRecvTemp[i][j][k]=0;
					LastRecvPower[i][j][k]=0;
					LastAlarmStatus[i][j][k]=0;
				}
			}
		}
		Menu_Exit=FALSE;
		Menu_StartMem=FALSE;
		Menu_StopMem=TRUE;
		Menu_Refresh=TRUE;
		Menu_Calibration=FALSE;
		Menu_UserSetPosition=FALSE;
		Menu_ReaderConfig=FALSE;
		Menu_PowerControl=FALSE;
		Menu_UpdateFirmware=FALSE;
		Menu_FactorySet=FALSE;
		Menu_UserSet=FALSE;
		Menu_ChangeUser=FALSE;
		Menu_ScanReader=FALSE;
		Menu_CtlSingleReader=TRUE;
		Menu_ShowAlarmHistory=FALSE;
		Menu_SetAlarmTemp=TRUE;
		Menu_ModifyReaderID=FALSE;
	}else
	{
		AfxMessageBox("请先打开端口，再进行控制操作！");
	}
}


void CMainFrame::OnUpdateStartMem(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_StartMem); 
}


void CMainFrame::OnStopMem()
{
	// TODO: 在此添加命令处理程序代码
	if (intTemp2)
	{
		if(MessageBox("确认停止温度监测","停止监测",MB_YESNO|MB_ICONQUESTION)==IDYES) 
		{
			while (1)
			{
				if (m_MSComm.GetInBufferCount()==0)
				{
					//KillTimer(ID_TIMER_LOOP);
					StopTimer();
					Sleep(400);
					//SendCMD(StopCMD);
					//Sleep(50);
					m_MSComm.SetInBufferCount(0);

					intTemp=0;
					break;
				}
			}
			CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
			pViewMainShow->SetButtonStatus(FALSE);
			pViewMainShow->StopMem();
			CTime currenttime=CTime::GetCurrentTime();   
			CString e_time=currenttime.Format("%Y-%m-%d %H:%M:%S"); 
			UpdateTest(e_time);
			PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
			SetStatusBar(1,"停止测量");
			Menu_Exit=TRUE;
			Menu_StartMem=TRUE;
			Menu_StopMem=FALSE;
			Menu_Refresh=FALSE;
			Menu_ChangeUser=TRUE;
			Menu_ScanReader=TRUE;
			Menu_CtlSingleReader=TRUE;
			Menu_ShowAlarmHistory=TRUE;
			Menu_SetAlarmTemp=TRUE;
			if (LoginDomainSet==0)
			{
				//Menu_Calibration=TRUE;
				Menu_UserSetPosition=TRUE;
				Menu_ReaderConfig=TRUE;
				Menu_PowerControl=TRUE;
				Menu_UpdateFirmware=TRUE;
				Menu_FactorySet=TRUE;
				Menu_UserSet=TRUE;
				Menu_ModifyReaderID=TRUE;
			} 
			else
			{
				Menu_Calibration=FALSE;
				Menu_UserSetPosition=FALSE;
				Menu_ReaderConfig=FALSE;
				Menu_PowerControl=FALSE;
				Menu_UpdateFirmware=FALSE;
				Menu_FactorySet=FALSE;
				Menu_UserSet=FALSE;
				Menu_ModifyReaderID=FALSE;
			}
		}	
	}else
	{
		AfxMessageBox("请先打开端口，再进行控制操作！");
	}
}


void CMainFrame::OnUpdateStopMem(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_StopMem); 
}


void CMainFrame::OnChangeUser()
{
	// TODO: 在此添加命令处理程序代码
	ActivePage();
	CTempDetectionView *pViewMainShow=(CTempDetectionView*)m_wndSplitter.GetPane(0,0);
	pViewMainShow->m_TreeCtl.EnableWindow(TRUE);

	CDlgChangeUser m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnPowerControl()
{
	// TODO: 在此添加命令处理程序代码
	CDlgPowerControl m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnRefresh()
{
	// TODO: 在此添加命令处理程序代码
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	CString tmp;
	for(int i = 0; i < 25;i++)
	{
		tmp.Format(_T("%03d"),i+1);
		pViewMainShow->pSheet->pDlgMainShow->v_Power[i]->CTChart::Series(0).GetAsLinearGauge().SetValue(0);
		pViewMainShow->pSheet->pDlgMainShow->v_Temp[i]->CTChart::Series(0).GetAsNumericGauge().SetValue(0);
		pViewMainShow->pSheet->pDlgMainShow->v_Title[i]->put_TitleText("终端"+tmp+"：未知");
	}

}


void CMainFrame::OnUpdateRefresh(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_Refresh); 
}

void CMainFrame::MainStatusShowAnt1(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	
}
void CMainFrame::MainStatusShowAnt2(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	

}
void CMainFrame::MainStatusShowAnt3(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	

}
void CMainFrame::MainStatusShowAnt4(char Sensor)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	
}

int CMainFrame::DataFix(CDlgCalibrate* pWndSensorFix,char status,int GetTemperData,int GetFreqData,int StaticTemper,int StaticFreq)
{
	CString TemperTxt,FreqTxt,PowerTxt;
	CString TemperText,FreqText,PowerText;
	if(status==0x01)
	{
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText("");
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText("干扰");
		return 0;
	}else if(status==0x02)
	{
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText("");
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText("功率低");
		return 0;
	}else if(status==0x03)
	{
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText("");
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText("信号弱");
		return 0;
	}else
	{
		double GetTemp;
		if (GetTemperData&0x8000)
		{
			unsigned int temp1=(~GetTemperData+1)&0x0000ffff;
			int tempdata=temp1%16;
			GetTemp=(double)(temp1/16)+(double)tempdata/16;
			GetTemp=-GetTemp;
		} 
		else
		{
			unsigned int temp1=GetTemperData;
			int tempdata=temp1%16;
			GetTemp=(double)(temp1/16)+(double)tempdata/16;
		}
		TemperTxt.Format("%.1f",GetTemp);
		FreqTxt.Format("%d",GetFreqData);
		TemperText="T:"+TemperTxt+"℃";
		FreqText="F:"+FreqTxt;
		pWndSensorFix->GetDlgItem(StaticTemper)->SetWindowText(TemperText);
		pWndSensorFix->GetDlgItem(StaticFreq)->SetWindowText(FreqText);
		return GetFreqData;
	}
}


void CMainFrame::ShowPosition(int ReaderID,bool status)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	
}


void CMainFrame::MainTempShow(CString Temp, int Status, CString Ant,int SensorID)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	
}


void CMainFrame::OnUpdateFirmware()
{
	// TODO: 在此添加命令处理程序代码
	CDlgUpdateFirmware m_dlg;
	m_dlg.DoModal();
}




void CMainFrame::SetStatusBar(int index, CString Str)
{
	m_wndStatusBar.SetPaneText(index,Str); 
}


void CMainFrame::OnSetAlarmTemp()
{
	// TODO: 在此添加命令处理程序代码
	CDlgSetAlarm m_dlg;
	m_dlg.DoModal();
}

WORD CMainFrame::GetCheckCode(const unsigned char * pSendBuf, int nEnd)
{
	WORD wCrc = WORD(0xFFFF);
	for(int i=0; i<nEnd; i++)
	{
		wCrc ^= WORD(BYTE(pSendBuf[i]));
		for(int j=0; j<8; j++)
		{
			if(wCrc & 1)
			{
				wCrc >>= 1; 
				wCrc ^= 0xA001; 
			}
			else
			{
				wCrc >>= 1; 
			}
		}
	}
	return wCrc;
}

void CMainFrame::SendCMD(unsigned char* pSendBuf)
{
	WORD GetCRC=GetCheckCode(pSendBuf,13);
	pSendBuf[14]=GetCRC&0x00ff;
	pSendBuf[13]=(GetCRC&0xff00)>>8;
	CByteArray arraySend;
	arraySend.RemoveAll();
	arraySend.SetSize(15);
	for(int i=0;i<15;i++)
	{
		arraySend.SetAt(i,pSendBuf[i]);
	}
	m_MSComm.SetOutput(COleVariant(arraySend));
}

void CMainFrame::OnUpdateSetAlarmTemp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_SetAlarmTemp); 
}


void CMainFrame::OnSetSilent()
{
	// TODO: 在此添加命令处理程序代码
	Menu_SetSilent=FALSE;
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void CMainFrame::OnUpdateSetSilent(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_SetSilent); 
}


void CMainFrame::OnShowAlarmHistory()
{
	// TODO: 在此添加命令处理程序代码
	CDlgAlarmHistory m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateShowAlarmHistory(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_ShowAlarmHistory); 
}

void CMainFrame::OnScanReader()
{
	// TODO: 在此添加命令处理程序代码
	SearchReader();
}


void CMainFrame::OnUpdateScanReader(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_ScanReader); 
}


void CMainFrame::OnCtlSingleReader()
{
	// TODO: 在此添加命令处理程序代码
	CDlgCtlSingleReader m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateCtlSingleReader(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_CtlSingleReader); 
}


void CMainFrame::OnModifyReadrId()
{
	// TODO: 在此添加命令处理程序代码
	CDlgModifyReaderID m_dlg;
	m_dlg.DoModal();
}


void CMainFrame::OnUpdateModifyReadrId(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(Menu_ModifyReaderID); 
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case ID_TIMER_WAIT:
		KillTimer(ID_TIMER_WAIT);
		StartTimer(m_hWnd,intUST);
		CountLoop=1;
		SYNCount=0;
		SendCMDStatus=TRUE;
		break;
	case ID_TIMER_LOOP:
		CallReaderCMD[0]=CountLoop;
		CountLoop++;
		if (CountLoop==31)
		{
			CountLoop=1;
		}
		SendCMD(CallReaderCMD);
		break;
	case ID_TIMER_SEARCH:
		KillTimer(ID_TIMER_SEARCH);
		StopMem();
		SearchFlag = 0;
		Invalidate();
		AfxMessageBox("已完成扫描");
		break;
	default:
		break;
	}
	CFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::ReadPositionFromDB(void)
{
	CString strPositon,strID,strHigh,strlow;
	strRPA.RemoveAll();
	strRPA.SetSize(30);

	_bstr_t bstrSQLReader ="SELECT ID,Position,HighTemp,LowTemp FROM db_reader_position order by ID;";
	_RecordsetPtr m_pRecordReader;
	m_pRecordReader.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordReader->Open(bstrSQLReader,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	while(!m_pRecordReader->adoEOF)
	{
		strID=(LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("ID");
		strID.ReleaseBuffer();
		strRPA.SetAt(atoi(strID)-1,(LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("Position"));
		AlarmTempSave[0][atoi(strID)-1]=atoi((LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("HighTemp"));
		AlarmTempSave[1][atoi(strID)-1]=atoi((LPCSTR)(_bstr_t)m_pRecordReader->GetCollect("LowTemp"));
		strID.FreeExtra();
		strID.Empty();
		m_pRecordReader->MoveNext();
	}
	m_pRecordReader->Close();

	int i,j,k;
	i=0;
	j=0;
	k=0;
	strSPA.RemoveAll();
	strSPA.SetSize(1440);
	_bstr_t bstrSQLSensor ="SELECT ID,Position,Power FROM db_sensor_position order by ID;";
	_RecordsetPtr m_pRecordSensor;
	m_pRecordSensor.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordSensor->Open(bstrSQLSensor,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	while(!m_pRecordSensor->adoEOF)
	{
		CString strPositon=(LPCSTR)(_bstr_t)m_pRecordSensor->GetCollect("Position");
		CString strID=(LPCSTR)(_bstr_t)m_pRecordSensor->GetCollect("ID");
		CString strPower=(LPCSTR)(_bstr_t)m_pRecordSensor->GetCollect("Power");
		strPositon.ReleaseBuffer();
		strID.ReleaseBuffer();
		strPower.ReleaseBuffer();
		strSPA.SetAt(atoi(strID)-25,strPositon);
		SensorPowerSet[i][j][k]=atoi(strPower);
		k++;
		if (k==12)
		{
			k=0;
			j++;
			if (j==4)
			{
				j=0;
				i++;
				if (i==30)
				{
					i=0;
				}
			}
		}
		m_pRecordSensor->MoveNext();
	}
	m_pRecordSensor->Close();
}


void CMainFrame::UpdateReaderPosition(CString ReaderID, CString Positon)
{
	try
	{
		_bstr_t strCmd="UPDATE db_reader_position SET Position='"+Positon+"' WHERE ReaderID="+ReaderID;
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::UpdateAlarmTemp(CString ReaderID, CString HighTemp, CString LowTemp)
{
	try
	{
		_bstr_t strCmd="UPDATE db_reader_position SET HighTemp='"+HighTemp+"',LowTemp='"+LowTemp+"' WHERE ReaderID="+ReaderID;
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::UpdateSensorPositon(CString ReaderID, CString AntID, CString SensorID, CString Positon)
{
	try
	{
		_bstr_t strCmd="UPDATE db_sensor_position SET Position='"+Positon+"' WHERE ReaderID='"+ReaderID+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"'";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::UpdateSensorPower(CString ReaderID, CString AntID, CString SensorID, CString Power)
{
	try
	{
		_bstr_t strCmd="UPDATE db_sensor_position SET Position='"+Power+"' WHERE ReaderID='"+ReaderID+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"'";
		m_pConnection->Execute(strCmd,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		return;
	}
}


void CMainFrame::ReadINIFile(CString FileName)
{
	for (int i = 0; i < 30; i++)
	{
		CString nindex,temp;
		nindex.Format("%d",i+1);
		GetPrivateProfileString("READER",nindex,"default",temp.GetBuffer(MAX_PATH),MAX_PATH,FileName); 
		temp.ReleaseBuffer();
		IntUDR[i]=atoi(temp);
	}
	CString temp;
	GetPrivateProfileString("LOOPTIME","Time","default",temp.GetBuffer(MAX_PATH),MAX_PATH,FileName); 
	temp.ReleaseBuffer();
	intUST=atoi(temp);
	CString temp2;
	GetPrivateProfileString("SYNCHRONOUS","Set","default",temp2.GetBuffer(MAX_PATH),MAX_PATH,FileName); 
	temp2.ReleaseBuffer();
	USSYN=atoi(temp2);
}


void CMainFrame::ShowAllLastData(void)
{
	COnDrawView *pViewMainShow=(COnDrawView*)m_wndSplitter.GetPane(0,1);
	
}


void CMainFrame::StartTimer(HWND hd,long time)
{
	SetTime=time;
	EnableTimer=TRUE;
	AfxBeginThread(OneMilliSecondProc,this);
}
void CMainFrame::StopTimer()
{
	EnableTimer=FALSE;
}

LRESULT CMainFrame::OnUpdateTime(WPARAM wParam,LPARAM lParam)
{

	QueryPerformanceCounter(&litmp);
	llQPartNew=litmp.QuadPart;
	double x=((double)(llQPartNew-llQPartOld))/fFreq;

	if (EnableTimer)
	{
		CallReaderCMD[0]=CountLoop;
		CountLoop++;
		if (CountLoop==201)
		{
			CountLoop=1;
		}
		if(x>(intUST-5)*0.001)
		{
			llQPartOld=llQPartNew;
			SendCMD(CallReaderCMD);
			
		}else
		{
			CountLoop--;
		}
	}
	return 0;
}
UINT OneMilliSecondProc(LPVOID lParam)
{
	CMainFrame* pDlg = (CMainFrame*)lParam;
	LARGE_INTEGER frequence, privious, current, interval; 
	if(!QueryPerformanceFrequency( &frequence)) 
	{ 
		::MessageBox(NULL, "Your computer hardware doesn't support the high-resolution performance counter", 
			"Not Support", MB_ICONEXCLAMATION | MB_OK); 
		return 0;
	} 
	interval.QuadPart = frequence.QuadPart * SetTime / 1000; 
	QueryPerformanceCounter( &current ); 
	while(EnableTimer)
	{
		privious = current; 
		while( current.QuadPart - privious.QuadPart < interval.QuadPart ) 
			QueryPerformanceCounter(&current);
		::SendMessage(pDlg->m_hWnd,WM_UPDATETIME,0,0);
	}
	return 0;
}


void CMainFrame::StartMem(void)
{
	if (intTemp2)
	{
		intRDC=0;
		//SendCMD(StartCMD);
		Sleep(50);
		m_MSComm.SetInBufferCount(0);
		SetTimer(ID_TIMER_WAIT,2000,NULL);
		intTemp=1;
		for (int k = 0; k < 30; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					m_FreqData[k][i][j]=0;
					m_TempData[k][i][j]=0;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				WrongFlagCount[i][j]=0;
			}
		}

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 12; k++)
				{
					LastRecvTemp[i][j][k]=0;
					LastRecvPower[i][j][k]=0;
					LastAlarmStatus[i][j][k]=0;
				}
			}
		}
	}else
	{
		AfxMessageBox("请先打开端口，再进行控制操作！");
	}
}


void CMainFrame::StopMem(void)
{
	if (intTemp2)
	{
		while (1)
		{
			if (m_MSComm.GetInBufferCount()==0)
			{
				StopTimer();
				//Sleep(400);
				//SendCMD(StopCMD);
				Sleep(50);
				m_MSComm.SetInBufferCount(0);
				intTemp=0;
				break;
			}
		}
	}else
	{
		AfxMessageBox("请先打开端口，再进行控制操作！");
	}
}






