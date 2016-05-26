// ContentSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "TempDetection.h"
#include "ContentSheet.h"


// CContentSheet

IMPLEMENT_DYNAMIC(CContentSheet, CPropertySheet)

CContentSheet::CContentSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CContentSheet::CContentSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	pDlgMainShow = new CDlgMainShow;
	pDlgMainShow1 = new CDlgMainShow;
	pDlgMainShow2 = new CDlgMainShow;
	pDlgMainShow3 = new CDlgMainShow;
	pDlgAlarmShow = new CDlgAlarmShow;
	pDlgHistory = new CDlgHistory;
	pDlgMainShow->m_psp.dwFlags   |=   PSP_PREMATURE;
	pDlgMainShow->m_psp.dwFlags |= PSP_USETITLE ;
	pDlgMainShow->m_psp.pszTitle = _T("Page 1");
	pDlgMainShow1->m_psp.dwFlags |= PSP_USETITLE ;
	pDlgMainShow1->m_psp.pszTitle = _T("Page 2");
	pDlgMainShow2->m_psp.dwFlags |= PSP_USETITLE ;
	pDlgMainShow2->m_psp.pszTitle = _T("Page 3");
	pDlgMainShow3->m_psp.dwFlags |= PSP_USETITLE ;
	pDlgMainShow3->m_psp.pszTitle = _T("Page 4");

	AddPage(pDlgMainShow);	// First page
	AddPage(pDlgMainShow1);
	AddPage(pDlgMainShow2);
	AddPage(pDlgMainShow3);
	AddPage(pDlgAlarmShow);
	AddPage(pDlgHistory);
}

CContentSheet::~CContentSheet()
{
	delete pDlgMainShow;
	delete pDlgMainShow1;
	delete pDlgMainShow2;
	delete pDlgMainShow3;
	delete pDlgAlarmShow;
	delete pDlgHistory;
}


BEGIN_MESSAGE_MAP(CContentSheet, CPropertySheet)
END_MESSAGE_MAP()


// CContentSheet 消息处理程序
