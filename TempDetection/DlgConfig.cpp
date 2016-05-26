// DlgConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgConfig.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern bool intTemp2;
unsigned char ConfigReaderCMD[15]={0x00,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

// CDlgConfig �Ի���

IMPLEMENT_DYNAMIC(CDlgConfig, CDialogEx)

CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConfig::IDD, pParent)
{

}

CDlgConfig::~CDlgConfig()
{
}

void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_ANT, m_CtlComboAnt);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_CtlBtnDown);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_CtlBtnClose);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReaderID);
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CDlgConfig::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgConfig::OnBnClickedButtonClose)
//	ON_CBN_SELCHANGE(IDC_COMBO_ANT, &CDlgConfig::OnCbnSelchangeComboAnt)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgConfig::OnCbnSelchangeComboReader)
END_MESSAGE_MAP()


// CDlgConfig ��Ϣ�������


void CDlgConfig::OnBnClickedButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (intTemp2)
	{
		CString strPath,strIndex;
		::GetModuleFileName( NULL, strPath.GetBuffer(MAX_PATH), MAX_PATH );
		strPath.ReleaseBuffer();
		strPath = strPath.Left(strPath.ReverseFind('\\')); 
		strIndex.Format(_T("%03d"),nIndexReaderID+1);
		strPath=strPath+"\\ReaderConfigFiles\\Reader"+strIndex+"\\file.txt";
		
		CStdioFile file;
		int ret = 0;
		if(!file.Open(strPath,CFile::modeRead))
		{
			AfxMessageBox("�����ļ������ڣ���ȷ�������ļ�");
			return;
		}
		CString strLine;
		CString FileStr;
		while(file.ReadString(strLine))
		{
			FileStr=FileStr+strLine;
		}
		file.Close();

		CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
		int strLen = FileStr.GetLength();
		char ch[2000]; 
		for (int i = 0; i < 2000; i++)
		{
			ch[i]=0xff;
		}
		if((strLen%8)==0)
		{
			GetDlgItem(IDC_STATIC_DOWN)->SetWindowText("�����ļ������С���");
			for (int i = 0; i < strLen/2; i++)
			{
				int temp=strtol(FileStr.Mid(2*i,2),NULL,16);
				ch[i]=(char)(temp&0x00ff);
			}
			ConfigReaderCMD[0]=(char)(nIndexReaderID+1);
			strLen=strLen/2;
			int i,j;
			if ((strLen%8)!=0)
			{
				for (j=0;j<=(strLen/8);j++)
				{
					ConfigReaderCMD[3]=(char)(j&0x00ff);
					ConfigReaderCMD[2]=(char)((j&0xff00)>>8);
					if (j==strLen/8)
					{
						ConfigReaderCMD[4]=0x80|(strLen%8);
					} 
					else
					{
						ConfigReaderCMD[4]=0x00;
					}

					for(i=0;i<8;i++)
					{
						if ((j*8+i)>strLen)
						{
							ConfigReaderCMD[5+i]=0x00;
						}
						else
						{
							ConfigReaderCMD[5+i]=ch[j*8+i];
						}
					}
					pMain->SendCMD(ConfigReaderCMD);
					Sleep(2);
				}
			}
			else
			{
				for (j=0;j<(strLen/8);j++)
				{
					ConfigReaderCMD[3]=(char)(j&0x00ff);
					ConfigReaderCMD[2]=(char)((j&0xff00)>>8);
					if (j==(strLen/8)-1)
					{
						ConfigReaderCMD[4]=0xff;
					} 
					else
					{
						ConfigReaderCMD[4]=0x00;
					}
					for(i=0;i<8;i++)
					{
						ConfigReaderCMD[5+i]=ch[j*8+i];
					}
					pMain->SendCMD(ConfigReaderCMD);
					Sleep(50);
				}
			}
			GetDlgItem(IDC_STATIC_DOWN)->SetWindowText("");
			AfxMessageBox("�����ļ��������!");
		}else
		{
			AfxMessageBox("�ļ����ݳ�������");
		}
	} 
	else
	{
		AfxMessageBox("���ȴ򿪶˿ڣ��ٽ��п��Ʋ�����");
	}

}


void CDlgConfig::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}





BOOL CDlgConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	nIndexReaderID=0;
	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReaderID);
	m_CtlBtnDown.SetIcon(IDI_ICON_DOWN);
	m_CtlBtnDown.SetFlat(TRUE);
	m_CtlBtnDown.SetTooltipText("����");
	m_CtlBtnClose.SetIcon(IDI_ICON_CLOSE);
	m_CtlBtnClose.SetFlat(TRUE);
	m_CtlBtnClose.SetTooltipText("����");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgConfig::OnCbnSelchangeComboReader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReaderID = m_CtlComboReaderID.GetCurSel();	
}
