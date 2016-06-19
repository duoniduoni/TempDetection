// CommEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "CommEdit.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern CString strFN;
extern bool intTemp2;
extern bool SearchFlag;
extern bool Menu_Communicate;
extern bool Menu_Exit;
extern bool Menu_StartMem;
extern bool Menu_StopMem;
extern bool Menu_Refresh;
extern bool Menu_Calibration;
extern bool Menu_UserSetPosition;
extern bool Menu_ReaderConfig;
extern bool Menu_PowerControl;
extern bool Menu_UpdateFirmware;
extern bool Menu_FactorySet;
extern bool Menu_UserSet;
extern bool Menu_ModifyReaderID;
extern bool Menu_ScanReader;
extern bool Menu_CtlSingleReader;
extern bool Menu_ShowAlarmHistory;
extern bool Menu_SetAlarmTemp;
extern int LoginDomainSet;

// CCommEdit 对话框

IMPLEMENT_DYNAMIC(CCommEdit, CDialogEx)

CCommEdit::CCommEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommEdit::IDD, pParent)
{

}

CCommEdit::~CCommEdit()
{
}

void CCommEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMM, m_CommSelect);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_CommBaud);
}


BEGIN_MESSAGE_MAP(CCommEdit, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_COMM, &CCommEdit::OnCbnSelchangeComboComm)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, &CCommEdit::OnCbnSelchangeComboBaud)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PORT, &CCommEdit::OnBnClickedButtonOpenPort)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_PORT, &CCommEdit::OnBnClickedButtonClosePort)
END_MESSAGE_MAP()


// CCommEdit 消息处理程序


void CCommEdit::OnCbnSelchangeComboComm()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndex_comm = m_CommSelect.GetCurSel();
	CString StrPort;
	StrPort.Format("%d",nIndex_comm);
	WritePrivateProfileString ("COMM", "Port", StrPort, strFN);   
}


void CCommEdit::OnCbnSelchangeComboBaud()
{
	// TODO: 在此添加控件通知处理程序代码
	nIndex_baud = m_CommBaud.GetCurSel();
	m_CommBaud.GetLBText(nIndex_baud, m_baud);			
	CString StrPort;
	StrPort.Format("%d",nIndex_baud);
	WritePrivateProfileString ("COMM", "Baud", StrPort, strFN);   
}


void CCommEdit::OnBnClickedButtonOpenPort()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;

	if(pMain->m_MSComm.GetPortOpen())	
		pMain->m_MSComm.SetPortOpen(FALSE); 	

	pMain->m_MSComm.SetCommPort(nIndex_comm+1);		
	pMain->m_MSComm.SetInputMode(1);				
	pMain->m_MSComm.SetInBufferSize(20480);			
	pMain->m_MSComm.SetOutBufferSize(5120);		    
	pMain->m_MSComm.SetInputLen(0);				   
	pMain->m_MSComm.SetRThreshold(1);				
	pMain->m_MSComm.SetSettings(m_baud+",n,8,1");  

	if(!pMain->m_MSComm.GetPortOpen())				
	{	
		try
		{
			pMain->m_MSComm.SetPortOpen(TRUE);		
			pMain->m_MSComm.SetInBufferCount(0);
			pMain->m_MSComm.GetInput();				
			intTemp2=TRUE;

			Menu_StartMem=TRUE;
			Menu_StopMem=FALSE;
			Menu_Refresh=FALSE;
			Menu_ScanReader=TRUE;
			Menu_CtlSingleReader=TRUE;
			Menu_ShowAlarmHistory=TRUE;
			Menu_SetAlarmTemp=TRUE;
			switch (LoginDomainSet)
			{
			case 0:
				//Menu_Calibration=TRUE;
				Menu_UserSetPosition=TRUE;
				Menu_ReaderConfig=TRUE;
				Menu_PowerControl=TRUE;
				Menu_UpdateFirmware=TRUE;
				Menu_FactorySet=TRUE;
				Menu_UserSet=TRUE;
				Menu_ModifyReaderID=TRUE;
				break;
			case 1:
				Menu_Calibration=FALSE;
				Menu_UserSetPosition=FALSE;
				Menu_ReaderConfig=FALSE;
				Menu_PowerControl=FALSE;
				Menu_UpdateFirmware=FALSE;
				Menu_FactorySet=FALSE;
				Menu_UserSet=FALSE;
				Menu_ModifyReaderID=FALSE;
				break;
			default:
				break;
			}
			SearchReader();
			OnOK();
		}
		catch (CException *e)
		{
			AfxMessageBox("串口不存在或被其他程序占用，请重新设置串口！");
			intTemp2=FALSE;
		}	
	}
	else
	{
		AfxMessageBox("打开端口失败，请确认端口信息!");
		intTemp2=FALSE;
	}
}


void CCommEdit::OnBnClickedButtonClosePort()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if(pMain->m_MSComm.GetPortOpen())	
		pMain->m_MSComm.SetPortOpen(FALSE); 	
	intTemp2=FALSE;
}


BOOL CCommEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strPort,strBaud;
	GetPrivateProfileString("COMM", "Port", 0,  strPort.GetBuffer(MAX_PATH),MAX_PATH, strFN);  
	GetPrivateProfileString("COMM", "Baud", 0,  strBaud.GetBuffer(MAX_PATH),MAX_PATH, strFN);  
	CComboBox*   pComb_comm   =   (CComboBox*)GetDlgItem(IDC_COMBO_COMM);   
	ASSERT(pComb_comm);   
	pComb_comm->SetCurSel(atoi(strPort));
	nIndex_comm=atoi(strPort);
	CComboBox*   pComb_baud   =   (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);   
	ASSERT(pComb_baud);   
	pComb_baud->SetCurSel(atoi(strBaud));
	nIndex_baud=atoi(strBaud);
	m_CommBaud.GetLBText(nIndex_baud, m_baud);			

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCommEdit::SearchReader()
{
	CMainFrame* pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	pMain->SearchReader();
}

