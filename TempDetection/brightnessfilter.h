#if !defined(AFX_BRIGHTNESSFILTER_H__88A8B703_BFE7_43D0_8C46_486D73A0209D__INCLUDED_)
#define AFX_BRIGHTNESSFILTER_H__88A8B703_BFE7_43D0_8C46_486D73A0209D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CBrightnessFilter wrapper class

class CBrightnessFilter : public COleDispatchDriver
{
public:
	CBrightnessFilter() {}		// Calls COleDispatchDriver default constructor
	CBrightnessFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CBrightnessFilter(const CBrightnessFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetPercent();
	void SetPercent(BOOL bNewValue);
	long GetAmount();
	void SetAmount(long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRIGHTNESSFILTER_H__88A8B703_BFE7_43D0_8C46_486D73A0209D__INCLUDED_)
