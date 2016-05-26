#pragma once
#include "tchart.h"
#include "axis.h"
#include "axes.h"
#include "scroll.h"
#include "series.h"
#include "gaugeseries.h"
#include "numericgauge.h"
#include "numericmarker.h"
#include "teeshapepanel.h"
#include "teefont.h"
#include "lineargauge.h"
#include "gaugepointerrange.h"
#include "gradient.h"
#include "ipanelx.h"
#include "tchart_power.h"
#include <vector>
#include <map>
// CDlgMainShow 对话框
using namespace std;
class CDlgMainShow : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgMainShow)

public:
	CDlgMainShow();
	virtual ~CDlgMainShow();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAIN_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	
	POINT oldSize;
	virtual BOOL OnInitDialog();
	CIpanelx m_Title001;
	CIpanelx m_Title002;
	CIpanelx m_Title003;
	CIpanelx m_Title004;
	CIpanelx m_Title005;
	CIpanelx m_Title006;
	CIpanelx m_Title007;
	CIpanelx m_Title008;
	CIpanelx m_Title009;
	CIpanelx m_Title010;
	CIpanelx m_Title011;
	CIpanelx m_Title012;
	CIpanelx m_Title013;
	CIpanelx m_Title014;
	CIpanelx m_Title015;
	CIpanelx m_Title016;
	CIpanelx m_Title017;
	CIpanelx m_Title018;
	CIpanelx m_Title019;
	CIpanelx m_Title020;
	CIpanelx m_Title021;
	CIpanelx m_Title022;
	CIpanelx m_Title023;
	CIpanelx m_Title024;
	CIpanelx m_Title025;
	CTchart_power m_power_001;
	CTchart_power m_power_002;
	CTchart_power m_power_003;
	CTchart_power m_power_004;
	CTchart_power m_power_005;
	CTchart_power m_power_006;
	CTchart_power m_power_007;
	CTchart_power m_power_008;
	CTchart_power m_power_009;
	CTchart_power m_power_010;
	CTchart_power m_power_011;
	CTchart_power m_power_012;
	CTchart_power m_power_013;
	CTchart_power m_power_014;
	CTchart_power m_power_015;
	CTchart_power m_power_016;
	CTchart_power m_power_017;
	CTchart_power m_power_018;
	CTchart_power m_power_019;
	CTchart_power m_power_020;
	CTchart_power m_power_021;
	CTchart_power m_power_022;
	CTchart_power m_power_023;
	CTchart_power m_power_024;
	CTchart_power m_power_025;
	

	CTchart_power m_Tchart_temp_001;
	CTchart_power m_Tchart_temp_002;
	CTchart_power m_Tchart_temp_003;
	CTchart_power m_Tchart_temp_004;
	CTchart_power m_Tchart_temp_005;
	CTchart_power m_Tchart_temp_006;
	CTchart_power m_Tchart_temp_007;
	CTchart_power m_Tchart_temp_008;
	CTchart_power m_Tchart_temp_009;
	CTchart_power m_Tchart_temp_010;
	CTchart_power m_Tchart_temp_011;
	CTchart_power m_Tchart_temp_012;
	CTchart_power m_Tchart_temp_013;
	CTchart_power m_Tchart_temp_014;
	CTchart_power m_Tchart_temp_015;
	CTchart_power m_Tchart_temp_016;
	CTchart_power m_Tchart_temp_017;
	CTchart_power m_Tchart_temp_018;
	CTchart_power m_Tchart_temp_019;
	CTchart_power m_Tchart_temp_020;
	CTchart_power m_Tchart_temp_021;
	CTchart_power m_Tchart_temp_022;
	CTchart_power m_Tchart_temp_023;
	CTchart_power m_Tchart_temp_024;
	CTchart_power m_Tchart_temp_025;

	vector<CIpanelx*> v_Title;
	vector<CTchart_power*> v_Power;
	vector<CTchart_power*> v_Temp;
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL OnSetActive();
};
