
// TempDetectionView.cpp : CTempDetectionView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CTempDetectionView ����/����

CTempDetectionView::CTempDetectionView()
	: CFormView(CTempDetectionView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CTempDetectionView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();

	pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd;

	m_CtlBtnStartMem.SetIcon(IDI_ICON_START);
	m_CtlBtnStartMem.SetFlat(TRUE);
	m_CtlBtnStartMem.SetTooltipText("��ʼ����");
	m_CtlBtnStopMem.SetIcon(IDI_ICON_STOP);
	m_CtlBtnStopMem.SetFlat(TRUE);
	m_CtlBtnStopMem.SetTooltipText("ֹͣ����");

	GetDlgItem(IDC_BUTTON_START_MEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_MEM)->EnableWindow(FALSE);

	m_TreeCtl.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT); 
	HTREEITEM hItem = m_TreeCtl.InsertItem("��Դ�����¶ȼ��ϵͳ",NULL,NULL); 

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
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(������0"+str+")",NULL,NULL,hItem); 
			}else
			{
				HTREEITEM Child_hItem=m_TreeCtl.InsertItem(temp+"(������"+str+")",NULL,NULL,hItem); 
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


// CTempDetectionView ���

#ifdef _DEBUG
void CTempDetectionView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTempDetectionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTempDetectionDoc* CTempDetectionView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTempDetectionDoc)));
	return (CTempDetectionDoc*)m_pDocument;
}
#endif //_DEBUG


// CTempDetectionView ��Ϣ�������


void CTempDetectionView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pMain->OnStartMem();
}


void CTempDetectionView::OnBnClickedButtonStopMem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	if (str!="��"&&str!="")
	{
		IntUSR=atoi(str);
		pMain->ShowPosition(IntUSR-1,TRUE);
		pMain->OnRefresh();
		pMain->ShowAllLastData();
		GetDlgItem(IDC_STATIC_SHOW_SELECT)->SetWindowText("��ǰ��ʾ:"+strSelect);
	}else
	{
		pMain->ShowPosition(IntUSR-1,FALSE);
		pMain->OnRefresh();
	}


	*pResult = 0;
}

