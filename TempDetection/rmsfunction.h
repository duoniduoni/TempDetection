#if !defined(AFX_RMSFUNCTION_H__84C95920_1C20_4953_98E8_5A5C544570AC__INCLUDED_)
#define AFX_RMSFUNCTION_H__84C95920_1C20_4953_98E8_5A5C544570AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CRMSFunction wrapper class

class CRMSFunction : public COleDispatchDriver
{
public:
	CRMSFunction() {}		// Calls COleDispatchDriver default constructor
	CRMSFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CRMSFunction(const CRMSFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetComplete();
	void SetComplete(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMSFUNCTION_H__84C95920_1C20_4953_98E8_5A5C544570AC__INCLUDED_)
