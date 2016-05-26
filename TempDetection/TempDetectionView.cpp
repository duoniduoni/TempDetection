
// TempDetectionView.cpp : CTempDetectionView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TempDetection.h"
#endif

#include "TempDetectionDoc.h"
#include "TempDetectionView.h"

extern bool intTemp2;
extern int IntUDR[30];
extern CStringArray strRPA;
extern int IntUSR;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTempDetectionView

IMPLEMENT_DYNCREATE(CTempDetectionView, CFormView)

BEGIN_MESSAGE_MAP(CTempDetectionView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_START_MEM, &CTempDetectionView::OnBnClickedButtonStartMem)
	ON_BN_CLICKED(IDC_BUTTON_STOP_MEM, &CTempDetectionView::OnBnClickedButtonStopMem)
	ON_NOTIFY(NM_CLICK, IDC_TREE_WINDOWS, &CTempDetectionView::OnNMClickTreeWindows)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TREE_WINDOWS, &CTempDetectionView::OnNMCustomdrawTreeWindows)
END_MESSAGE_MAP()

// CTempDetectionView 构造/析构

CTempDetectionView::CTempDetectionView()
	: CFormView(CTempDetectionView::IDD)
{
	// TODO: 在此处添加构造代码

}

CTempDetectionView::~CTempDetectionView()
{
}

void CTempDetectionView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START_MEM, m_CtlBtnStartMem);
	DDX_Control(pDX, IDC_BUTTON_STOP_MEM, m_CtlBtnStopMem);
	DDX_Control(pDX, IDC_TREE_WINDOWS, m_TreeCtl);
}

BOOL CTempDetectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CTempDetectionView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();

	pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;

	m_CtlBtnStartMem.SetIcon(IDI_ICON_START);
	m_CtlBtnStartMem.SetFlat(TRUE);
	m_CtlBtnStartMem.SetTooltipText("开始测量");
	m_CtlBtnStopMem.SetIcon(IDI_ICON_STOP);
	m_CtlBtnStopMem.SetFlat(TRUE);
	m_CtlBtnStopMem.SetTooltipText("停止测量");

	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);

	m_TreeCtl.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT); 
	HTREEITEM hItem = m_TreeCtl.InsertItem("有源无线温度监控系统",NULL,NULL); 

	for (int i = 0; i < 30; i++)
	{
		if (IntUDR[i]==1)
		{
			CString temp=strRPA.GetAt(i);
			temp.ReleaseBuffer();
			CString str;
			str.Format("%d",i+1);
			if (i<9)
			{
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(读卡器0"+str+")",NULL,NULL,hItem); 
			}else
			{
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(读卡器"+str+")",NULL,NULL,hItem); 
			}
		}	
	
	}
	m_TreeCtl.Expand(hItem,TVE_EXPAND); 
	m_TreeCtl.SetFocus();
	
}

void CTempDetectionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTempDetectionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTempDetectionView 诊断

#ifdef _DEBUG
void CTempDetectionView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTempDetectionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTempDetectionDoc* CTempDetectionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTempDetectionDoc)));
	return (CTempDetectionDoc*)m_pDocument;
}
#endif //_DEBUG


// CTempDetectionView 消息处理程序


void CTempDetectionView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	this->ShowWindow(SW_MAXIMIZE);

	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL){
		CRect rect;
		this->GetWindowRect(&rect);
		pchild->ScreenToClient(&rect);
		pchild->SetWindowPos(NULL, 0, 100, rect.Width(), rect.Height()-100,
			SWP_NOZORDER | SWP_NOACTIVATE);
	}	
}


void CTempDetectionView::OnBnClickedButtonStartMem()
{
	// TODO: 在此添加控件通知处理程序代码
	pMain->OnStartMem();
}


void CTempDetectionView::OnBnClickedButtonStopMem()
{
	// TODO: 在此添加控件通知处理程序代码
	pMain->OnStopMem();
}

void CTempDetectionView::InitImageLists()
{

	CBitmap bmp;
	// normal tree images
	m_imgNormal.Create(16,
		15,
		TRUE,
		20,	// number of initial images
		20);

	ASSERT(m_imgNormal.m_hImageList);

	bmp.LoadBitmap(IDB_BITMAP2);
	m_imgNormal.Add( &bmp, RGB(255,255,255));
	bmp.DeleteObject();
}

void CTempDetectionView::SetButtonStatus(BOOL Flag)
{
	if (Flag)
	{
		GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(TRUE);
	}else
	{
		GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
	}
}


void CTempDetectionView::StopMem(void)
{
	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);
}


void CTempDetectionView::StartMem(void)
{
	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(TRUE);
}


void CTempDetectionView::OnNMClickTreeWindows(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CString strSelect;
	CPoint ptCurSel(0,0);
	TVHITTESTINFO HitTestInfo;
	GetCursorPos(&ptCurSel); 
	m_TreeCtl.ScreenToClient(&ptCurSel);   
	HitTestInfo.pt = ptCurSel;   
	HTREEITEM hSelect = m_TreeCtl.HitTest(&HitTestInfo);

	if(hSelect != NULL)
	{
		str = m_TreeCtl.GetItemText(hSelect);
	}
	strSelect=str;
	m_TreeCtl.SelectItem(hSelect);
	str=str.Right(3);
	str=str.Left(2);
	if (str!="低"&&str!="")
	{
		IntUSR=atoi(str);
		pMain->ShowPosition(IntUSR-1,TRUE);
		pMain->OnRefresh();
		pMain->ShowAllLastData();
		GetDlgItem(IDC_STATIC_SHOW_SELECT)->SetWindowText("当前显示:"+strSelect);
	}else
	{
		pMain->ShowPosition(IntUSR-1,FALSE);
		pMain->OnRefresh();
	}


	*pResult = 0;
}

