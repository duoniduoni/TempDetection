#if !defined(AFX_IPLOTLIMITX_H__053AAD18_4F07_4D2D_954F_9934B9771DA1__INCLUDED_)
#define AFX_IPLOTLIMITX_H__053AAD18_4F07_4D2D_954F_9934B9771DA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CiPlotLimitX wrapper class

class CiPlotLimitX : public COleDispatchDriver
{
public:
	CiPlotLimitX() {}		// Calls COleDispatchDriver default constructor
	CiPlotLimitX(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CiPlotLimitX(const CiPlotLimitX& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	unsigned long GetColor();
	void SetColor(unsigned long newValue);
	long GetLineStyle();
	void SetLineStyle(long nNewValue);
	long GetLineWidth();
	void SetLineWidth(long nNewValue);
	long GetFillStyle();
	void SetFillStyle(long nNewValue);
	CString GetXAxisName();
	void SetXAxisName(LPCTSTR lpszNewValue);
	CString GetYAxisName();
	void SetYAxisName(LPCTSTR lpszNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
	double GetLine1Position();
	void SetLine1Position(double newValue);
	double GetLine2Position();
	void SetLine2Position(double newValue);
	void ClearAllElements();
	void AddBandElement(double Position, double UpperLimit, double LowerLimit);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	BOOL GetPopupEnabled();
	void SetPopupEnabled(BOOL bNewValue);
	BOOL GetUserCanMove();
	void SetUserCanMove(BOOL bNewValue);
	long GetLayer();
	void SetLayer(long nNewValue);
	BOOL GetUserSelected();
	void SetUserSelected(BOOL bNewValue);
	BOOL HitTest(long X, long Y);
	void DoEditMenuItemClick();
	BOOL GetUserCanEdit();
	void SetUserCanEdit(BOOL bNewValue);
	BOOL GetCanFocus();
	void SetCanFocus(BOOL bNewValue);
	BOOL GetSelectModeOnlyInteraction();
	void SetSelectModeOnlyInteraction(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPLOTLIMITX_H__053AAD18_4F07_4D2D_954F_9934B9771DA1__INCLUDED_)
