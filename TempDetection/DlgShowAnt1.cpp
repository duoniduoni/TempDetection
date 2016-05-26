// DlgShowAnt1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TempDetection.h"
#include "DlgShowAnt1.h"
#include "afxdialogex.h"
#include "MainFrm.h"

extern double LastRecvTemp[30][4][12];
extern int LastAlarmStatus[30][4][12];
extern int IntUSR;
extern int LastRecvPower[30][4][12];

// CDlgShowAnt1 �Ի���

IMPLEMENT_DYNAMIC(CDlgShowAnt1, CPropertyPage)

CDlgShowAnt1::CDlgShowAnt1()
	: CPropertyPage(CDlgShowAnt1::IDD)
{

}

CDlgShowAnt1::~CDlgShowAnt1()
{
}

void CDlgShowAnt1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART_SHOW01, m_CtlTChart01);
	DDX_Control(pDX, IDC_TCHART_SHOW02, m_CtlTChart02);
	DDX_Control(pDX, IDC_TCHART_SHOW03, m_CtlTChart03);
	DDX_Control(pDX, IDC_TCHART_SHOW04, m_CtlTChart04);
	DDX_Control(pDX, IDC_TCHART_SHOW05, m_CtlTChart05);
	DDX_Control(pDX, IDC_TCHART_SHOW06, m_CtlTChart06);
	DDX_Control(pDX, IDC_TCHART_SHOW07, m_CtlTChart07);
	DDX_Control(pDX, IDC_TCHART_SHOW08, m_CtlTChart08);
	DDX_Control(pDX, IDC_TCHART_SHOW09, m_CtlTChart09);
	DDX_Control(pDX, IDC_TCHART_SHOW10, m_CtlTChart10);
	DDX_Control(pDX, IDC_TCHART_SHOW11, m_CtlTChart11);
	DDX_Control(pDX, IDC_TCHART_SHOW12, m_CtlTChart12);
	DDX_Control(pDX, IDC_TCHART_POWER1, m_CtlPowerChart01);
	DDX_Control(pDX, IDC_TCHART_POWER2, m_CtlPowerChart02);
	DDX_Control(pDX, IDC_TCHART_POWER3, m_CtlPowerChart03);
	DDX_Control(pDX, IDC_TCHART_POWER4, m_CtlPowerChart04);
	DDX_Control(pDX, IDC_TCHART_POWER5, m_CtlPowerChart05);
	DDX_Control(pDX, IDC_TCHART_POWER6, m_CtlPowerChart06);
	DDX_Control(pDX, IDC_TCHART_POWER7, m_CtlPowerChart07);
	DDX_Control(pDX, IDC_TCHART_POWER8, m_CtlPowerChart08);
	DDX_Control(pDX, IDC_TCHART_POWER9, m_CtlPowerChart09);
	DDX_Control(pDX, IDC_TCHART_POWER10, m_CtlPowerChart10);
	DDX_Control(pDX, IDC_TCHART_POWER11, m_CtlPowerChart11);
	DDX_Control(pDX, IDC_TCHART_POWER12, m_CtlPowerChart12);
}


BEGIN_MESSAGE_MAP(CDlgShowAnt1, CPropertyPage)
END_MESSAGE_MAP()


// CDlgShowAnt1 ��Ϣ��������


BOOL CDlgShowAnt1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart01.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart01.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart02.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart02.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart03.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart03.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart04.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart04.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart05.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart05.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart06.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart06.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart07.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart07.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart08.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart08.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart09.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart09.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart10.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart10.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart11.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart11.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);
	m_CtlTChart12.Series(0).GetAsNumericGauge().GetTextMarker().SetText("δ֪λ��");
	m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
	m_CtlTChart12.Series(0).GetAsNumericGauge().GetUnitsMarker().GetShape().GetFont().SetColor(RGB(0,0,0));
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetStartValue(0);
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetEndValue(100);
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,0));
	m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);

	CMainFrame *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgShowAnt1::ShowData(void)
{
	switch (LastAlarmStatus[IntUSR-1][0][0])
	{
	case 0:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][0]);
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][0]);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][0]);
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][0]);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart01.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart01.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart01.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][1])
	{
	case 0:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][1]);
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][1]);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][1]);
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][1]);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart02.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart02.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart02.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][2])
	{
	case 0:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][2]);
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][2]);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][2]);
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][2]);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart03.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart03.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart03.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][3])
	{
	case 0:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][3]);
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][3]);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][3]);
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][3]);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart04.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart04.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart04.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][4])
	{
	case 0:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][4]);
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][4]);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][4]);
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][4]);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart05.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart05.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart05.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][5])
	{
	case 0:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][5]);
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][5]);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][5]);
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][5]);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart06.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart06.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart06.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][6])
	{
	case 0:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][6]);
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][6]);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][6]);
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][6]);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart07.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart07.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart07.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][7])
	{
	case 0:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][7]);
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][7]);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][7]);
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][7]);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart08.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart08.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart08.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][8])
	{
	case 0:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][8]);
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][8]);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][8]);
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][8]);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart09.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart09.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart09.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][9])
	{
	case 0:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][9]);
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][9]);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][9]);
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][9]);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart10.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart10.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart10.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][10])
	{
	case 0:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][10]);
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][10]);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][10]);
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][10]);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart11.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart11.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart11.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

	switch (LastAlarmStatus[IntUSR-1][0][11])
	{
	case 0:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][11]);
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(0,0,255));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][11]);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 1:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(LastRecvTemp[IntUSR-1][0][11]);
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,0,0));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(LastRecvPower[IntUSR-1][0][11]);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(FALSE);
		break;
	case 2:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(255,255,0));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 3:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,255,0));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	case 4:
		m_CtlTChart12.Series(0).GetAsNumericGauge().SetValue(0);
		m_CtlTChart12.Series(0).GetAsNumericGauge().GetValueMarker().GetShape().GetFont().SetColor(RGB(255,255,255));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().SetValue(0);
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().GetGradient().SetStartColor(RGB(0,0,255));
		m_CtlPowerChart12.Series(0).GetAsLinearGauge().GetRedLine().SetVisible(TRUE);
		break;
	default:
		break;
	}

}