#include "stdafx.h"
#include "CMyTreeCtl.h"
extern bool IndexReader[30];
BEGIN_MESSAGE_MAP(CMyTreeCtl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyTreeCtl::OnNMCustomdraw)
END_MESSAGE_MAP()


void CMyTreeCtl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	LPNMTVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);
	CString ItemStr,tmpStr;
	switch (pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	case CDDS_ITEMPREPAINT:
		// 判断
		HTREEITEM hItem= (HTREEITEM)pNMCD->nmcd.dwItemSpec;
		ItemStr = GetItemText(hItem); 
		if("无源无线温度监控系统" == ItemStr)
			break;
		else
		{
			int i = atoi(ItemStr.Mid(ItemStr.GetLength()-3,2));
			if(!IndexReader[i-1])
				pNMCD->clrText = RGB(169, 169, 169); // 设置文字颜色
			//pNMCD->clrTextBk = RGB(0, 0, 0);
			break;
		}
	}
	*pResult = 0;
}
