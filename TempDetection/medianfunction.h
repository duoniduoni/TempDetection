#if !defined(AFX_MEDIANFUNCTION_H__28BC2CA1_CA54_4FD6_80AE_F70EBD202AB4__INCLUDED_)
#define AFX_MEDIANFUNCTION_H__28BC2CA1_CA54_4FD6_80AE_F70EBD202AB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CMedianFunction wrapper class

class CMedianFunction : public COleDispatchDriver
{
public:
	CMedianFunction() {}		// Calls COleDispatchDriver default constructor
	CMedianFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMedianFunction(const CMedianFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIncludeNulls();
	void SetIncludeNulls(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIANFUNCTION_H__28BC2CA1_CA54_4FD6_80AE_F70EBD202AB4__INCLUDED_)