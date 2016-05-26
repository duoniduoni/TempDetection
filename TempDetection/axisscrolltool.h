#if !defined(AFX_AXISSCROLLTOOL_H__8103786A_7A7A_4026_B228_5F18F3A02268__INCLUDED_)
#define AFX_AXISSCROLLTOOL_H__8103786A_7A7A_4026_B228_5F18F3A02268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CAxisScrollTool wrapper class

class CAxisScrollTool : public COleDispatchDriver
{
public:
	CAxisScrollTool() {}		// Calls COleDispatchDriver default constructor
	CAxisScrollTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxisScrollTool(const CAxisScrollTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetAxis();
	void SetAxis(const VARIANT& newValue);
	BOOL GetScrollInverted();
	void SetScrollInverted(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXISSCROLLTOOL_H__8103786A_7A7A_4026_B228_5F18F3A02268__INCLUDED_)
