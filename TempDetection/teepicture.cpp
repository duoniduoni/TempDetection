// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "teepicture.h"

// Dispatch interfaces referenced by this interface
#include "FilterItems.h"


/////////////////////////////////////////////////////////////////////////////
// CTeePicture properties

/////////////////////////////////////////////////////////////////////////////
// CTeePicture operations

CFilterItems CTeePicture::GetFilters()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CFilterItems(pDispatch);
}

void CTeePicture::LoadImage(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

void CTeePicture::AssignImage(long ImageHandle)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ImageHandle);
}

void CTeePicture::ClearImage()
{
	InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CTeePicture::ShowFiltersEditor()
{
	BOOL result;
	InvokeHelper(0xcd, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CTeePicture::GetHandle()
{
	long result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CTeePicture::SaveToFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}
