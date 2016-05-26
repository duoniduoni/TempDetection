#if !defined(AFX_PAGENUMTOOL_H__FA3E621B_476D_406B_BB37_450F2F68CC04__INCLUDED_)
#define AFX_PAGENUMTOOL_H__FA3E621B_476D_406B_BB37_450F2F68CC04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CTeeShapePanel;
class CAnnotationCallout;
class CBrush1;
class CPen1;
class CGradient;

/////////////////////////////////////////////////////////////////////////////
// CPageNumTool wrapper class

class CPageNumTool : public COleDispatchDriver
{
public:
	CPageNumTool() {}		// Calls COleDispatchDriver default constructor
	CPageNumTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPageNumTool(const CPageNumTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetPosition();
	void SetPosition(long nNewValue);
	CTeeShapePanel GetShape();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	CAnnotationCallout GetCallout();
	long GetTextAlignment();
	void SetTextAlignment(long nNewValue);
	BOOL Clicked(long X, long Y);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	short GetCursor();
	void SetCursor(short nNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	BOOL GetAutoSize();
	void SetAutoSize(BOOL bNewValue);
	CBrush1 GetBrush();
	// method 'GetBounds' not emitted because of invalid return type or parameter type
	void SetBounds(long Left, long Top, long Right, long Bottom);
	long GetPositionUnits();
	void SetPositionUnits(long nNewValue);
	CString GetFormat();
	void SetFormat(LPCTSTR lpszNewValue);
	BOOL GetShowButtons();
	void SetShowButtons(BOOL bNewValue);
	CPen1 GetButtonPen();
	long GetButtonWidth();
	void SetButtonWidth(long nNewValue);
	CGradient GetDisabledButton();
	CGradient GetEnabledButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGENUMTOOL_H__FA3E621B_476D_406B_BB37_450F2F68CC04__INCLUDED_)
