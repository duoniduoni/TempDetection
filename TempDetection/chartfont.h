#if !defined(AFX_CHARTFONT_H__7975CA61_C8E1_4175_A1C2_475350E2018B__INCLUDED_)
#define AFX_CHARTFONT_H__7975CA61_C8E1_4175_A1C2_475350E2018B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CChartFont wrapper class

class CChartFont : public COleDispatchDriver
{
public:
	CChartFont() {}		// Calls COleDispatchDriver default constructor
	CChartFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartFont(const CChartFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetSize();
	void SetSize(long nNewValue);
	BOOL GetBold();
	void SetBold(BOOL bNewValue);
	BOOL GetItalic();
	void SetItalic(BOOL bNewValue);
	BOOL GetUnderline();
	void SetUnderline(BOOL bNewValue);
	BOOL GetStrikethrough();
	void SetStrikethrough(BOOL bNewValue);
	short GetCharset();
	void SetCharset(short nNewValue);
	unsigned long GetColor();
	void SetColor(unsigned long newValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetPixelsPerInch();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTFONT_H__7975CA61_C8E1_4175_A1C2_475350E2018B__INCLUDED_)