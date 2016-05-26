#if !defined(AFX_STRINGS_H__2A4AB8D3_7CEF_4AB3_98FF_9E0C9623106C__INCLUDED_)
#define AFX_STRINGS_H__2A4AB8D3_7CEF_4AB3_98FF_9E0C9623106C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CStrings wrapper class

class CStrings : public COleDispatchDriver
{
public:
	CStrings() {}		// Calls COleDispatchDriver default constructor
	CStrings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CStrings(const CStrings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetControlDefault(long Index);
	void SetControlDefault(long Index, const VARIANT& newValue);
	long Count();
	VARIANT GetItem(long Index);
	void SetItem(long Index, const VARIANT& newValue);
	void Remove(long Index);
	void Clear();
	long Add(const VARIANT& AItem);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGS_H__2A4AB8D3_7CEF_4AB3_98FF_9E0C9623106C__INCLUDED_)
