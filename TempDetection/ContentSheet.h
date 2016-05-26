#pragma once

#include "DlgHistory.h"
#include "DlgMainShow.h"
#include "DlgAlarmShow.h"
// CContentSheet

class CContentSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CContentSheet)

public:
	CContentSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CContentSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CContentSheet();
public:
	CDlgHistory *pDlgHistory;
	CDlgMainShow *pDlgMainShow;
	CDlgMainShow *pDlgMainShow1;
	CDlgMainShow *pDlgMainShow2;
	CDlgMainShow *pDlgMainShow3;
	CDlgAlarmShow *pDlgAlarmShow;

	

protected:
	DECLARE_MESSAGE_MAP()
};


