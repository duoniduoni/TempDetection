#if !defined(AFX_EXTRALEGENDTOOL_H__3EA5F9E9_0189_4945_B26E_E9EBA72FEE2C__INCLUDED_)
#define AFX_EXTRALEGENDTOOL_H__3EA5F9E9_0189_4945_B26E_E9EBA72FEE2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CLegend;

/////////////////////////////////////////////////////////////////////////////
// CExtraLegendTool wrapper class

class CExtraLegendTool : public COleDispatchDriver
{
public:
	CExtraLegendTool() {}		// Calls COleDispatchDriver default constructor
	CExtraLegendTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CExtraLegendTool(const CExtraLegendTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetSeries();
	void SetSeries(const VARIANT& newValue);
	CLegend GetLegend();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRALEGENDTOOL_H__3EA5F9E9_0189_4945_B26E_E9EBA72FEE2C__INCLUDED_)
