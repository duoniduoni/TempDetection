#if !defined(AFX_HUELUMSATFILTER_H__62FD86D5_F7D1_4A0B_BE35_6C60469E07D9__INCLUDED_)
#define AFX_HUELUMSATFILTER_H__62FD86D5_F7D1_4A0B_BE35_6C60469E07D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CHueLumSatFilter wrapper class

class CHueLumSatFilter : public COleDispatchDriver
{
public:
	CHueLumSatFilter() {}		// Calls COleDispatchDriver default constructor
	CHueLumSatFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CHueLumSatFilter(const CHueLumSatFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetHue();
	void SetHue(long nNewValue);
	long GetLuminance();
	void SetLuminance(long nNewValue);
	long GetSaturation();
	void SetSaturation(long nNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUELUMSATFILTER_H__62FD86D5_F7D1_4A0B_BE35_6C60469E07D9__INCLUDED_)
