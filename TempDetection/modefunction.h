#if !defined(AFX_MODEFUNCTION_H__81D285E0_350D_4DB5_B4F9_CEE28B500A2A__INCLUDED_)
#define AFX_MODEFUNCTION_H__81D285E0_350D_4DB5_B4F9_CEE28B500A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CModeFunction wrapper class

class CModeFunction : public COleDispatchDriver
{
public:
	CModeFunction() {}		// Calls COleDispatchDriver default constructor
	CModeFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CModeFunction(const CModeFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIncludeNulls();
	void SetIncludeNulls(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODEFUNCTION_H__81D285E0_350D_4DB5_B4F9_CEE28B500A2A__INCLUDED_)
