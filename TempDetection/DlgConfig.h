#pragma once
#include "afxwin.h"
#include "IconListBox.h"


// CDlgConfig �Ի���

class CDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConfig();
	int nIndexReaderID;
// �Ի�������
	enum { IDD = IDD_DIALOG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonClose();
	CComboBox m_CtlComboAnt;
	CButtonST  m_CtlBtnDown;
	CButtonST  m_CtlBtnClose;

	virtual BOOL OnInitDialog();
	CComboBox m_CtlComboReaderID;
	afx_msg void OnCbnSelchangeComboReader();
};
