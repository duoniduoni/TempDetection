// DlgHistory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgHistory.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "iplotchannelx.h"
#include "iplotaxisx.h"
#include "iplottoolbarx.h"

extern _ConnectionPtr m_pConnection;

// CDlgHistory �Ի���

IMPLEMENT_DYNAMIC(CDlgHistory, CPropertyPage)

CDlgHistory::CDlgHistory()
	: CPropertyPage(CDlgHistory::IDD)
	, m_DataBegin(COleDateTime::GetCurrentTime())
	, m_DataEnding(COleDateTime::GetCurrentTime())
{
	if(!app.CreateDispatch("Excel.Application"))   
    {  
		AfxMessageBox("�޷�����Excel����!"); 
		//GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(TRUE); 
	}
}

CDlgHistory::~CDlgHistory()
{
}

void CDlgHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STARTTIME, m_CtlDateTimeStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_STOPTIME, m_CtlDateTimeStopTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STARTTIME, m_DataBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOPTIME, m_DataEnding);
	DDX_Control(pDX,IDC_TCHART_HISTORY,m_CtlChart);
	DDX_Control(pDX, IDC_COMBO_ANT, m_CtlComboAnt);
	DDX_Control(pDX, IDC_COMBO_SENSOR, m_CtlComboSensor);
	DDX_Control(pDX, IDC_COMBO_READER, m_CtlComboReaderID);
}


BEGIN_MESSAGE_MAP(CDlgHistory, CPropertyPage)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgHistory::OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_ANT, &CDlgHistory::OnCbnSelchangeComboAnt)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR, &CDlgHistory::OnCbnSelchangeComboSensor)
	ON_CBN_SELCHANGE(IDC_COMBO_READER, &CDlgHistory::OnCbnSelchangeComboReader)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgHistory::OnBnClickedButtonExport)
END_MESSAGE_MAP()


// CDlgHistory ��Ϣ�������


void CDlgHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_CtlChart.GetSafeHwnd())   
	{  
		if (nType==SIZE_RESTORED)  
		{  
			CRect rs;  
			GetClientRect(&rs);  
			m_CtlChart.SetWindowPos(NULL,0,rs.bottom/8,rs.right - 20,rs.bottom*7/8 - 25,SWP_SHOWWINDOW | SWP_NOZORDER); 
		}  
	} 
}


BOOL CDlgHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_CtlDateTimeStartTime.SetFormat("yyy-MM-dd HH:mm:ss");
	m_CtlDateTimeStopTime.SetFormat("yyy-MM-dd HH:mm:ss");
	strReader="������1";
	nIndexReader=0;
	nIndexAnt=0;
	nIndexSensor=0;
	CComboBox*   pComb_Ant   =   (CComboBox*)GetDlgItem(IDC_COMBO_ANT);   
	ASSERT(pComb_Ant);   
	pComb_Ant->SetCurSel(nIndexAnt);
	CComboBox*   pComb_Sensor   =   (CComboBox*)GetDlgItem(IDC_COMBO_SENSOR);   
	ASSERT(pComb_Sensor);   
	for(int i = 0; i < 100; i++)
	{
		CString tmp;
		tmp.Format("%d", i+1);
		pComb_Sensor->AddString(tmp);
	}
	pComb_Sensor->SetCurSel(nIndexSensor);
	
	CComboBox*   pComb_Reader   =   (CComboBox*)GetDlgItem(IDC_COMBO_READER);   
	ASSERT(pComb_Reader);   
	pComb_Reader->SetCurSel(nIndexReader);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgHistory::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(FALSE);
	CString AntID,SensorID,StrStartTime,StrStopTime;
	m_CtlChart.GetToolBar(0).DoButtonClickResume();
	m_CtlChart.GetYAxis(0).SetSpan(100);
	m_CtlChart.GetYAxis(0).SetMin(0);
	m_CtlChart.GetXAxis(0).SetMin(72686);
	m_CtlChart.GetXAxis(0).SetSpan(0.00694444444444444);
	m_CtlChart.GetChannel(0).Clear();

	AntID.Format("%d",nIndexAnt+1);
	AntID="����"+AntID;
	SensorID.Format("%d",nIndexSensor+1);
	SensorID="������"+SensorID;
	StrStartTime.Format("%f",m_DataBegin);
	StrStopTime.Format("%f",m_DataEnding);

	_bstr_t bstrSQLdata ="SELECT Temperature,RecordTime FROM DB_Data where ReaderID='"+strReader+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"' and RecordTime<"+StrStopTime+" and RecordTime>"+StrStartTime+" and (Notes='����') order by DataID;";
	_RecordsetPtr m_pRecordsetch;
	m_pRecordsetch.CreateInstance(__uuidof(Recordset));
	m_pRecordsetch->Open(bstrSQLdata,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	if (!m_pRecordsetch->adoEOF)
	{
		while(!m_pRecordsetch->adoEOF)
		{
			CString temper=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("Temperature");
			CString time=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("RecordTime");
			temper.ReleaseBuffer();
			m_CtlChart.GetChannel(0).AddXY(atof(time), atof(temper) / 10);
			m_pRecordsetch->MoveNext();
		}
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		m_CtlChart.GetYAxis(0).ZoomToFitFast();
	} 
	else
	{
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		AfxMessageBox("��ѯ�������ݣ�");
	}
	m_pRecordsetch->Close();
}



void CDlgHistory::OnCbnSelchangeComboAnt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexAnt=m_CtlComboAnt.GetCurSel();

}


void CDlgHistory::OnCbnSelchangeComboSensor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexSensor=m_CtlComboSensor.GetCurSel();
}


void CDlgHistory::OnCbnSelchangeComboReader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nIndexReader=m_CtlComboReaderID.GetCurSel();
	m_CtlComboReaderID.GetLBText(nIndexReader,strReader);
}


void CDlgHistory::OnBnClickedButtonExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(FALSE);
	COleVariant covTrue((short)TRUE),covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR); 
	book.PrintPreview(_variant_t(false));
	CFileDialog FileDialog(FALSE,"xlsx",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Microsoft Excel 2007(*.xlsx)|*.xlsx|�����ļ�(*.*)"),this); 
	if(FileDialog.DoModal()!=IDOK) 
	{
		GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(TRUE);
		return; 
	}
	CString cStrFile=FileDialog.GetPathName();  //ѡ�񱣴�·������
	if(::PathFileExists(cStrFile)) 
		DeleteFile(cStrFile); 
	CString AntID,SensorID,StrStartTime,StrStopTime,tmpData,passWord,StartTime,StopTime,message,strRecordTime,rowCount,strRow,strLimit;
	StrStartTime.Format("%f",m_DataBegin);
	StrStopTime.Format("%f",m_DataEnding);
	CTime m_Startdate;
	m_CtlDateTimeStartTime.GetTime(m_Startdate);
	StartTime.Format("%d%02d%02d",m_Startdate.GetYear(), m_Startdate.GetMonth(),m_Startdate.GetDay());
	_RecordsetPtr m_pRecordsetch;
	m_pRecordsetch.CreateInstance(__uuidof(Recordset));
	books = app.get_Workbooks();
	book = books.Add(covOptional);
	sheets = book.get_Worksheets();
	sheets.Add(vtMissing,vtMissing,vtMissing,vtMissing);
	int nCount;
	char cCell;
	for(int i=1;i<5;i++)
	{
		tmpData.Format("%d",i);
		AntID = "����"+tmpData; 
		sheet = sheets.get_Item(COleVariant((short)i)); //�õ���һ��������
		sheet.put_Name(AntID);
		for(int j=1;j<13;j++)
		{
			nCount = 3;
			tmpData.Format("%d",j);
			SensorID = "������"+tmpData;
			cCell = 'A' + 2*(j-1);
			rowCount.Format(_T("%c"),cCell);
			rowCount+="1";
			range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount)); 
			range.put_Value2(COleVariant(SensorID));
			rowCount.Format(_T("%c"),cCell);
			rowCount+="2";
			range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount)); 
			range.put_Value2(COleVariant("ʱ��"));
			rowCount.Format(_T("%c"),cCell+1);
			rowCount+="2";
			range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount)); 
			range.put_Value2(COleVariant("�¶�"));
			_bstr_t bstrSQLdata ="SELECT Temperature,RecordTime FROM DB_Data where ReaderID='"+strReader+"' and AntID='"+AntID+"' and SensorID='"+SensorID+"' and RecordTime<"+StrStopTime+" and RecordTime>"+StrStartTime+" and (Notes='����' or Notes='����') order by DataID;";
			m_pRecordsetch->Open(bstrSQLdata,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
			while(!m_pRecordsetch->adoEOF)
			{
				CString temper=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("Temperature");
				CString time=(LPCSTR)(_bstr_t)m_pRecordsetch->GetCollect("RecordTime");
				COleDateTime t=atof(time);
				strRecordTime=t.Format("%Y-%m-%d %H:%M:%S");
				rowCount.Format(_T("%c"),cCell);
				strRow.Format(_T("%d"),nCount);
				rowCount+=strRow;
				range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount));
				range.put_NumberFormat(COleVariant("hh:mm:ss"));
				range.put_Value2(COleVariant(strRecordTime));  //����ʱ��
				rowCount.Format(_T("%c"),cCell+1);
				rowCount+=strRow;
				range = sheet.get_Range(COleVariant(rowCount),COleVariant(rowCount));  
				range.put_Value2(COleVariant(temper));  //�����¶�
				time.ReleaseBuffer();
				temper.ReleaseBuffer();
				m_pRecordsetch->MoveNext();
				nCount++;
			}
			m_pRecordsetch->Close();
		}
		range = sheet.get_Range(COleVariant("A3"),COleVariant("A3"));
		COleVariant vResult =range.get_Value2();
		if(vResult.vt==VT_EMPTY)
		{
			passWord="19700101hshiot";
		}
		else
		{
			SYSTEMTIME st;
			VariantTimeToSystemTime(vResult.date, &st);
			passWord.Format("%d%02d%02d",st.wYear,st.wMonth,st.wDay);
			passWord+="hshiot";
		}
		sheet.Protect(_variant_t(passWord),vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);
	}
	book.SaveCopyAs(COleVariant(cStrFile)); //���浽cStrFile�ļ�
	book.put_Saved(true);
	books.Close();
	book.ReleaseDispatch();
	books.ReleaseDispatch(); 
	app.ReleaseDispatch();
	app.Quit();
	message = "�ѵ������ݣ��ļ�λ�� :"+cStrFile;
	AfxMessageBox(message);
	GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(TRUE);
} 



   