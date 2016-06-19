// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
#include "MainFrm.h"
extern int LoginDomainSet;
extern CString LoginName;

// CDlgLogin 对话框

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DEFAULT, m_BtnDefault);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CDlgLogin::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_CHECK_, &CDlgLogin::OnBnClickedCheck)
END_MESSAGE_MAP()


// CDlgLogin 消息处理程序


void CDlgLogin::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString StrName,StrPassword;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowTextA(StrName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowTextA(StrPassword);
	_bstr_t bstrSQL ="SELECT UserPassword,Domain FROM db_user where UserName='"+StrName+"'";
	_RecordsetPtr m_pRecordset1;
	m_pRecordset1.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordset1->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	if(!m_pRecordset1->adoEOF)
	{
		CString pass=m_pRecordset1->GetCollect("UserPassword");
		if (!pass.Compare(StrPassword))
		{
			CString domain=m_pRecordset1->GetCollect("Domain");
			LoginDomainSet=atoi(domain);
			LoginName=StrName;
			OnBnClickedCheck();
			OnOK();
		}else
		{
			AfxMessageBox("请输入正确的密码！");
		}		
	}else
	{
		AfxMessageBox("请输入正确的用户名！");
	}
}


BOOL CDlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

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


	HMODULE Positionmodule = GetModuleHandle(0); 
	char pPositionFileName[MAX_PATH]; 
	GetModuleFileName(Positionmodule, pPositionFileName, MAX_PATH); 

	CString csPositionFullPath(pPositionFileName); 
	int nPos = csPositionFullPath.ReverseFind( _T('\\') ); 
	if( nPos < 0 ) 
		AfxMessageBox("找不到SystemInstall.ini配置文件"); 
	strFN=csPositionFullPath.Left( nPos ); 
	strFN=strFN+"\\SystemInstall.ini";

	CString strName,strPassword,strDefault;
	GetPrivateProfileString("LOGIN","Name","default",strName.GetBuffer(MAX_PATH),MAX_PATH,strFN); 
	GetPrivateProfileString("LOGIN","Password","default",strPassword.GetBuffer(MAX_PATH),MAX_PATH,strFN); 
	GetPrivateProfileString("LOGIN","Default","default",strDefault.GetBuffer(MAX_PATH),MAX_PATH,strFN); 
	strName.ReleaseBuffer();
	strPassword.ReleaseBuffer();
	strDefault.ReleaseBuffer();
	if (atoi(strDefault)==1)
	{
		GetDlgItem(IDC_EDIT_USERNAME)->SetWindowTextA(strName);
		GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextA(strPassword);
		((CButton*)GetDlgItem(IDC_CHECK_DEFAULT))->SetCheck(BST_CHECKED);
	} 
	else
	{
		GetDlgItem(IDC_EDIT_USERNAME)->SetWindowTextA("");
		GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowTextA("");
		((CButton*)GetDlgItem(IDC_CHECK_DEFAULT))->SetCheck(BST_UNCHECKED);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			OnBnClickedButtonLogin();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgLogin::OnBnClickedCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName,strPassword,strDefault;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowTextA(strName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowTextA(strPassword);
	if(m_BtnDefault.GetCheck() == BST_CHECKED) 
	{
		WritePrivateProfileString ("LOGIN","Name", strName, strFN);   
		WritePrivateProfileString ("LOGIN","Password", strPassword, strFN);   
		strDefault="1";
		WritePrivateProfileString ("LOGIN","Default", strDefault, strFN);   
	} 
	else if(m_BtnDefault.GetCheck() == BST_UNCHECKED) 
	{
		WritePrivateProfileString ("LOGIN","Name", "", strFN);   
		WritePrivateProfileString ("LOGIN","Password", "", strFN);   
		strDefault="0";
		WritePrivateProfileString ("LOGIN","Default", strDefault, strFN);   
	}		
}
