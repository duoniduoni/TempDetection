#include "StdAfx.h"
#include <afxdisp.h>
#include "Export2Excel.h"
//using namespace O12;
/*
 Email:happyboy200032@163.com
 Blog: http://happyboy200032.blog.163.com

 1.
	�����������й���ź�������һ��Ϊ����1��ʼ
 2.
	��ʹ�ñ����ʱ����Ҫ��ʼ��COM��
	if(CoInitialize(NULL) != NULL)
	{
		AfxMessageBox("��ʼ��COMʧ��!");
	}
 3.
	//�ڳ����˳���ʱ����Ҫ���COM��
	CoUninitialize();
*/
CExport2Excel::CExport2Excel(void)
{
	bSheet = false;
}

CExport2Excel::~CExport2Excel(void)
{
}

/*
	����Excel�ļ�
	sExcelFile:	Excel�ļ���
*/
bool CExport2Excel::CreateExcel(CString sExcelFile)
{
	bCreate = true;
	//ʹ��Excel���Ϳ�ӿڵķ�ʽʵ��
	this->sExcelFile = sExcelFile;
	covOptional = COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if(!m_appExcel.CreateDispatch("Excel.Application",NULL))
	{
		//����Excel����ʧ��
		return false;
	}

	m_wbExcels.AttachDispatch(m_appExcel.get_Workbooks(),true);
	m_wbExcelSingle.AttachDispatch(m_wbExcels.Add(covOptional));

	//�õ�Worksheets 
	m_wsExcels.AttachDispatch(m_wbExcelSingle.get_Worksheets(),true);

	//ɾ���� ֻʣ��һ����
	for (short i = 1; i<= (short)m_wsExcels.get_Count(); i++)
	{
		m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((short)i)));
		m_wsExcelSingle.Delete();
	}

	iSheetIndex = 1;
	bSheet = true;
	return true;
}

//��Excel�ļ�
bool CExport2Excel::OpenExcel(CString sExcelFile)
{
	bCreate = false;
	//ʹ��Excel���Ϳ�ӿڵķ�ʽʵ��
	this->sExcelFile = sExcelFile;
	covOptional = COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if(!m_appExcel.CreateDispatch("Excel.Application",NULL))
	{
		//����Excel����ʧ��
		return false;
	}

	m_wbExcels.AttachDispatch(m_appExcel.get_Workbooks(),true);
	m_wbExcelSingle.AttachDispatch(m_wbExcels.Open(sExcelFile.GetBuffer(), vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing));

	//�õ�Worksheets 
	m_wsExcels.AttachDispatch(m_wbExcelSingle.get_Worksheets(),true);
/*
	long iSheet = m_wsExcels.get_Count();
	long i;
	for (i = 1; i <= iSheet; i++)
	{
		m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((long)(i))));
		if (m_wsExcelSingle.get_Name().CompareNoCase("�ļ�") == 0)
		{
			iSheetIndex = i;
			m_wsExcelSingle.ReleaseDispatch();
			break;
		}
		m_wsExcelSingle.ReleaseDispatch();
	}

	SetSheet(i);
*/

	SetSheet(1);
	return true;
}

/*
	������
	sSheetName:	����
*/
void CExport2Excel::CreateSheet(CString sSheetName)
{
	if (bSheet)
	{
		//��һ����
		m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((short)(1))));
	}else{
		//���ǵ�һ����
		m_wsExcelSingle.AttachDispatch(m_wsExcels.Add(vtMissing, vtMissing, COleVariant((short)(1)), vtMissing));
	}

	bSheet = false;

	iSheetIndex = 1;
	//���ñ���
	m_wsExcelSingle.put_Name(sSheetName);
	m_rangeExcel.AttachDispatch(m_wsExcelSingle.get_UsedRange(), TRUE);
}

void CExport2Excel::SetShowAlert(BOOL bShow)
{
	m_appExcel.put_DisplayAlerts(bShow);
}

/*
	���õ�ǰ������
	iSheetIndex: Ϊ�������˳�򣨵��򣬼���󴴽��ı����Ϊ1��
*/
void CExport2Excel::SetSheet(long iSheetIndex)
{
	m_wsExcelSingle.ReleaseDispatch();
	m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((short)iSheetIndex)));
	m_wsExcelSingle.Activate();

	m_rangeExcel.ReleaseDispatch();
	m_rangeExcel.AttachDispatch(m_wsExcelSingle.get_UsedRange(), TRUE);

	this->iSheetIndex = iSheetIndex;
}

int CExport2Excel::GetSheetIndex()
{
	return iSheetIndex;
}

void CExport2Excel::WriteTitle(LPSTR pszText)
{
	WriteData(0, 1, pszText);
}

/*
	д��ͷ
	iColumn:ָ����
	pszText:�ı�
*/
void CExport2Excel::WriteHeader(long iColumn, LPSTR pszText)
{
	WriteData(1, iColumn, pszText);
}

/*
	iRow:		�к�
	iColumn:	�к�
	pszText:	Ҫд����ı�
*/
void CExport2Excel::WriteData(long iRow, long iColumn, LPSTR pszText)
{
	// ��Excel��д����
	m_rangeExcel.put_Item(_variant_t(iRow + 1), _variant_t(iColumn), COleVariant(pszText));
	//SetAudoColumn();
}

//��ȡ�ı�
CString CExport2Excel::GetText(long iRow, long iColumn)
{
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)(iColumn))).pdispVal, true);

	VARIANT pszText = tRange.get_Text();
	tRange.ReleaseDispatch();

	CString strT;
	char* buf = _com_util::ConvertBSTRToString(pszText.bstrVal);
	strT.Format("%s", buf);
	delete buf;
	return  strT;
}

//��ȡ��ʽ
CString CExport2Excel::GetCalcText(long iRow, long iColumn)
{
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)(iColumn))).pdispVal, true);

	VARIANT pszText = tRange.get_Formula();
	tRange.ReleaseDispatch();

	CString strT;
	char* buf = _com_util::ConvertBSTRToString(pszText.bstrVal);
	strT.Format("%s", buf);
	delete buf;
	return  strT;
}

//��ȡ�ϲ���Ԫ����Ϣ
void CExport2Excel::GetMergeAreaInfo(long iRow, long iColumn, long& MergeRowCount, long& MergeColumnCount, long& MergeStartRow, long& MergeStartColumn)
{
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)(iColumn))).pdispVal, true);

	CRange unionRange;
	unionRange.AttachDispatch(tRange.get_MergeArea());

	//�ϲ���Ԫ�������
	CRange mergeAreaRange_HangCount;
	mergeAreaRange_HangCount.AttachDispatch(unionRange.get_Rows());
	MergeRowCount = mergeAreaRange_HangCount.get_Count();
	mergeAreaRange_HangCount.ReleaseDispatch();

	//�ϲ���Ԫ�������
	CRange mergeAreaRange_LieCount;
	mergeAreaRange_LieCount.AttachDispatch(unionRange.get_Columns());
	MergeColumnCount = mergeAreaRange_LieCount.get_Count();
	mergeAreaRange_LieCount.ReleaseDispatch();

	//��ʼ�У���1��ʼ
	MergeStartRow = unionRange.get_Row();
	//��ʼ�У���1��ʼ
	MergeStartColumn = unionRange.get_Column();

	unionRange.ReleaseDispatch();
	tRange.ReleaseDispatch();
}

// д��ʽ
void CExport2Excel::WriteCalcText(long iRow, long iColumn, LPSTR pszText)
{
	// ��Excel��д����
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow + 1), _variant_t((long)(iColumn))).pdispVal, true);

	tRange.put_Formula(COleVariant(pszText));
	tRange.ReleaseDispatch();
}

// ���õ�Ԫ���ʽ @ = �ı���ʽ
void CExport2Excel::SetNumberFormatLocal(long iRow, long iColumn, LPSTR pszText)
{
	// ��Excel��д����
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow + 1), _variant_t((long)(iColumn))).pdispVal, true);

	tRange.put_NumberFormatLocal(COleVariant(pszText));
	tRange.ReleaseDispatch();
}

// ���õ�Ԫ��ˮƽ�Ҷ���
void CExport2Excel::SetHorizontalAlignment(long iRow, long iColumn, long HAType)
{
	// ��Excel��д����
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow + 1), _variant_t((long)(iColumn))).pdispVal, true);

	tRange.put_HorizontalAlignment(_variant_t(HAType));
	tRange.ReleaseDispatch();
}

/*
	�����п�
	iColumn:	ָ����
	iWidth:		���
*/
void CExport2Excel::SetColWidth(long iColumn, float iWidth)
{
	CRange tRange;
	//�õ���һ��
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t(iColumn)).pdispVal, true);
	//�����п�
	tRange.put_ColumnWidth(_variant_t(iWidth));
	tRange.ReleaseDispatch();
}

/*
	�����п�
	iRow:	ָ����
	iHeight:		�߶�
*/
void CExport2Excel::SetRowHeight(long iRow, float iHeight)
{
	CRange tRange;
	//�õ���һ��
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)1)).pdispVal, true);
	//�����и�
	tRange.put_RowHeight(_variant_t(iHeight));
	tRange.ReleaseDispatch();
}

//error
void CExport2Excel::SetAutoFilter(long iRow)
{
	CRange tRange;
	//�õ���һ��
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)1)).pdispVal, true);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//�����и�
	tRange.AutoFilter(COleVariant((long)1), COleVariant((long)2), 1, COleVariant((long)4), vtMissing);
	tRange.ReleaseDispatch();
}

//�����Զ�����
void CExport2Excel::SetWrapText(long iRow, long iColumn)
{
	CRange tRange;
	//�õ���һ��
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)iColumn)).pdispVal, true);
	COleVariant varTrue((short)TRUE,VT_BOOL);
	tRange.put_WrapText(varTrue);
	tRange.ReleaseDispatch();
}

//�Զ������п�
void CExport2Excel::SetAudoColumn()
{
	//ѡ��������
	CRange range;
	range.AttachDispatch(m_wsExcelSingle.get_Cells());
	range.Select();

	//������Ϊ�Զ������п�
	CRange range1;
	range1.AttachDispatch(range.get_Columns());
	range1.AutoFit();

	range1.ReleaseDispatch();
	range.ReleaseDispatch();

	//ȡ��ѡ�������У���ѡ������һ����Ԫ�񼴿ɣ�
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//�ϲ���Ԫ�� ����1��ʼ
void CExport2Excel::MergeTitleCells(long iRow, long iStartColumn, long iEndColumn)
{
	iStartColumn += 'A' - 1;
	iEndColumn += 'A' - 1;

	CString strT;
	strT.Format("%C%d:%C%d", iStartColumn, iRow, iEndColumn, iRow);

	CRange tRange;
	//tRange.AttachDispatch(m_rangeExcel.get_Range(COleVariant("A2"), COleVariant("A2")));
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();
	COleVariant varTrue((short)TRUE,VT_BOOL);
	tRange.put_MergeCells(varTrue);
	tRange.ReleaseDispatch();

	//ȡ��ѡ�������У���ѡ������һ����Ԫ�񼴿ɣ�
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//�ϲ���Ԫ�� ����1��ʼ
void CExport2Excel::MergeCells(long iRow, long iStartColumn, long iEndColumn)
{
	iStartColumn += 'A' - 1;
	iEndColumn += 'A' - 1;

	CString strT;
	strT.Format("%C%d:%C%d", iStartColumn, iRow + 1, iEndColumn, iRow + 1);

	CRange tRange;
	//tRange.AttachDispatch(m_rangeExcel.get_Range(COleVariant("A2"), COleVariant("A2")));
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();
	COleVariant varTrue((short)TRUE,VT_BOOL);
	tRange.put_MergeCells(varTrue);
	tRange.ReleaseDispatch();

	//ȡ��ѡ�������У���ѡ������һ����Ԫ�񼴿ɣ�
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//�ϲ���Ԫ�� ����1��ʼ
void CExport2Excel::MergeCells(long iStartRow, long iEndRow, long iStartColumn, long iEndColumn)
{
	iStartColumn += 'A' - 1;
	iEndColumn += 'A' - 1;

	CString strT;
	strT.Format("%C%d:%C%d", iStartColumn, iStartRow + 1, iEndColumn, iEndRow + 1);

	CRange tRange;
	//tRange.AttachDispatch(m_rangeExcel.get_Range(COleVariant("A2"), COleVariant("A2")));
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();
	COleVariant varTrue((short)TRUE,VT_BOOL);
	tRange.put_MergeCells(varTrue);
	tRange.ReleaseDispatch();

	//ȡ��ѡ�������У���ѡ������һ����Ԫ�񼴿ɣ�
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//���ñ߿�
//SetBorders(4, 1, iRow, 8, true, true, true, true, true, true, xlMedium, xlMedium, xlMedium, xlMedium, xlThin, xlThin)
void CExport2Excel::SetBorders(long iStartRow, long iStartColumn, long iEndRow, long iEndColumn, // ָ���ĵ�Ԫ��
							   bool bLeft, bool bTop, bool bRight, bool bBottom,				// ָ�����ĸ���
							   bool bInsideVertical, bool bInsideHorizontal,					// �ڲ��߿�
							   long Left_LineType, long Top_LineType, long Right_LineType, long Bottom_LineType, // �ĸ��ߵ�������
							   long InsideVertical_LineType, long InsideHorizontal_LineType)	// �ڲ��߿��������
{
	iStartColumn += 'A' - 1;
	iEndColumn += 'A' - 1;

	CString strT;
	strT.Format("%C%d:%C%d", iStartColumn, iStartRow, iEndColumn, iEndRow);

	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();

	//Ϊ���ܺ��ڲ����ϱ߿�
	m_bordersExcel.AttachDispatch(tRange.get_Borders());

	// �ÿ�
	m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlDiagonalDown));
	m_borderExcel.put_LineStyle(_variant_t(xlNone));
	m_borderExcel.ReleaseDispatch();

	m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlDiagonalUp));
	m_borderExcel.put_LineStyle(_variant_t(xlNone));
	m_borderExcel.ReleaseDispatch();

	// Left
	if (bLeft)
	{
		m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlEdgeLeft));
		m_borderExcel.put_LineStyle(_variant_t(xlContinuous));
		m_borderExcel.put_Weight(_variant_t(Left_LineType));
		m_borderExcel.put_ColorIndex(_variant_t(xlAutomatic));
		m_borderExcel.ReleaseDispatch();
	}

	// Top
	if (bTop)
	{
		m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlEdgeTop));
		m_borderExcel.put_LineStyle(_variant_t(xlContinuous));
		m_borderExcel.put_Weight(_variant_t(Top_LineType));
		m_borderExcel.put_ColorIndex(_variant_t(xlAutomatic));
		m_borderExcel.ReleaseDispatch();
	}

	// Right
	if (bRight)
	{
		m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlEdgeRight));
		m_borderExcel.put_LineStyle(_variant_t(xlContinuous));
		m_borderExcel.put_Weight(_variant_t(Right_LineType));
		m_borderExcel.put_ColorIndex(_variant_t(xlAutomatic));
		m_borderExcel.ReleaseDispatch();
	}

	// Bottom
	if (bBottom)
	{
		m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlEdgeBottom));
		m_borderExcel.put_LineStyle(_variant_t(xlContinuous));
		m_borderExcel.put_Weight(_variant_t(Bottom_LineType));
		m_borderExcel.put_ColorIndex(_variant_t(xlAutomatic));
		m_borderExcel.ReleaseDispatch();
	}

	// InsideVertical
	if ((iEndColumn - iStartColumn) > 1 && bInsideVertical)
	{
		m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlInsideVertical));
		m_borderExcel.put_LineStyle(_variant_t(xlContinuous));
		m_borderExcel.put_Weight(_variant_t(InsideVertical_LineType));
		m_borderExcel.put_ColorIndex(_variant_t(xlAutomatic));
		m_borderExcel.ReleaseDispatch();
	}

	// InsideHorizontal
	if ((iEndRow - iStartRow) > 1 && bInsideHorizontal)
	{
		m_borderExcel.AttachDispatch(m_bordersExcel.get_Item(xlInsideHorizontal));
		m_borderExcel.put_LineStyle(_variant_t(xlContinuous));
		m_borderExcel.put_Weight(_variant_t(InsideHorizontal_LineType));
		m_borderExcel.put_ColorIndex(_variant_t(xlAutomatic));
		m_borderExcel.ReleaseDispatch();
	}
    m_bordersExcel.ReleaseDispatch();
	tRange.ReleaseDispatch();

	//ȡ��ѡ�������У���ѡ������һ����Ԫ�񼴿ɣ�
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
	//http://www.cppblog.com/greatws/archive/2008/09/21/62423.html
}

//���ж���
void CExport2Excel::SetFirstLineFreezePanes()
{
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(COleVariant("A2"), COleVariant("A2")));
	tRange.Select();
	tRange.ReleaseDispatch();

	CWindow0 tWindow;
	tWindow.AttachDispatch(m_appExcel.get_ActiveWindow());
	tWindow.put_FreezePanes(true);
	tWindow.ReleaseDispatch();
}

//������ɫ
void CExport2Excel::SetFirstLineColor(COLORREF color)
{
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t("2:2"), vtMissing), true);
	tRange.Select();

	//���þ���
	tRange.put_HorizontalAlignment(_variant_t((short)-4108));
	//���ô���
	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	tFont.put_Bold(_variant_t(true));
	tFont.put_Name(_variant_t("����"));
	tFont.put_Size(_variant_t(10));
	tFont.ReleaseDispatch();

	//������ɫ
	Cnterior tNterior;
	tNterior.AttachDispatch(tRange.get_Interior());

	tNterior.put_Color(_variant_t(color));
	tNterior.ReleaseDispatch();
	tRange.ReleaseDispatch();
}

void CExport2Excel::SetLineColor(COLORREF color, long iRow, LPSTR pszFontName, int iFontSize, bool bBold)
{
	CString strT;
	strT.Format("%d:%d", iRow, iRow);
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();

	//���þ���
	tRange.put_HorizontalAlignment(_variant_t((short)-4108));
	//���ô���
	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	if (bBold)
		tFont.put_Bold(_variant_t(true));

	if (pszFontName != NULL)
		tFont.put_Name(_variant_t(pszFontName));

	tFont.put_Size(_variant_t(iFontSize));
	tFont.ReleaseDispatch();

	//������ɫ
	Cnterior tNterior;
	tNterior.AttachDispatch(tRange.get_Interior());

	tNterior.put_Color(_variant_t(color));
	tNterior.ReleaseDispatch();
	tRange.ReleaseDispatch();
}

void CExport2Excel::SetFont(long iRow, LPSTR pszFontName, int iFontSize, bool bBold)
{
	CString strT;
	strT.Format("%d:%d", iRow, iRow);
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();

	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	if (bBold)
		tFont.put_Bold(_variant_t(true));
	else
		tFont.put_Bold(_variant_t(false));

	if (pszFontName != NULL)
		tFont.put_Name(_variant_t(pszFontName));

	tFont.put_Size(_variant_t(iFontSize));
	tFont.ReleaseDispatch();

	tRange.ReleaseDispatch();
}

void CExport2Excel::SetFont(long iRow, long iColumn, LPSTR pszFontName, int iFontSize, bool bBold)
{
	CString strT;
	strT.Format("%c%d", iColumn + 'A' - 1, iRow);
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();

	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	if (bBold)
		tFont.put_Bold(_variant_t(true));
	else
		tFont.put_Bold(_variant_t(false));

	if (pszFontName != NULL)
		tFont.put_Name(_variant_t(pszFontName));

	tFont.put_Size(_variant_t(iFontSize));
	tFont.ReleaseDispatch();

	tRange.ReleaseDispatch();
}

void CExport2Excel::SetColor(COLORREF color, long iRow, long iColumn)
{
	CString strT;
	strT.Format("%c%d", iColumn + 'A' - 1, iRow);
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();
/*
	//���þ���
	tRange.put_HorizontalAlignment(_variant_t((short)-4108));
	//���ô���
	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	if (bBold)
		tFont.put_Bold(_variant_t(true));

	if (pszFontName != NULL)
		tFont.put_Name(_variant_t(pszFontName));

	tFont.put_Size(_variant_t(iFontSize));
	tFont.ReleaseDispatch();
*/
	//������ɫ
	Cnterior tNterior;
	tNterior.AttachDispatch(tRange.get_Interior());

	tNterior.put_Color(_variant_t(color));
	tNterior.ReleaseDispatch();
	tRange.ReleaseDispatch();
}

/*
	�����У���ǰ�������ƶ�
*/
void CExport2Excel::InsertRow(long iRow)
{
	CRange tRange;
	CString strT;
	strT.Format("%d:%d", iRow, iRow);
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();

	//Insert(COleVariant((long)-4121)); to shift down
	//Insert(COleVariant((long)-4161)); to shift right.
	tRange.Insert(COleVariant((long)-4121), _variant_t(true));
	tRange.ReleaseDispatch();
}

long CExport2Excel::GetRowCount()
{
	//return m_rangeExcel.get_Count();
	long lRowCount;
	int iSheetIndex = GetSheetIndex();
	m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((long)(iSheetIndex))));

	CRange usedRange;
	usedRange.AttachDispatch(m_wsExcelSingle.get_UsedRange());

	CRange usedRow;
	usedRow.AttachDispatch(usedRange.get_Rows());
	lRowCount = usedRow.get_Count();
	usedRow.ReleaseDispatch();
	m_wsExcelSingle.ReleaseDispatch();

	return lRowCount;
}

void CExport2Excel::Save()
{
	if (bCreate)
	{
		m_wbExcelSingle.SaveAs(COleVariant(sExcelFile),
							_variant_t(vtMissing),
							_variant_t(vtMissing),
							_variant_t(vtMissing),
							_variant_t(vtMissing),
							_variant_t(vtMissing),
							0,
							_variant_t(vtMissing),
							_variant_t(vtMissing),
							_variant_t(vtMissing),
							_variant_t(vtMissing),
							_variant_t(vtMissing));
	}else{
		//app.SetDisplayAlerts(false); // �������Ի���ѯ���Ƿ񱣴�
		m_wbExcelSingle.Save();
	}

	m_wbExcelSingle.Close(covOptional, COleVariant(sExcelFile), covOptional);
	m_wbExcels.Close();

	m_rangeExcel.ReleaseDispatch();
	m_wsExcelSingle.ReleaseDispatch();
	m_wsExcels.ReleaseDispatch();
	m_wbExcelSingle.ReleaseDispatch();
	m_wbExcels.ReleaseDispatch();
}

void CExport2Excel::SaveAs(CString strExcelFile)
{
	m_wbExcelSingle.SaveAs(COleVariant(strExcelFile),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						0,
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing));

	m_wbExcelSingle.Close(covOptional, COleVariant(sExcelFile), covOptional);
	m_wbExcels.Close();

	m_rangeExcel.ReleaseDispatch();
	m_wsExcelSingle.ReleaseDispatch();
	m_wsExcels.ReleaseDispatch();
	m_wbExcelSingle.ReleaseDispatch();
	m_wbExcels.ReleaseDispatch();
}

void CExport2Excel::Close()
{
	m_appExcel.put_UserControl(true);
	m_appExcel.Quit();
	m_appExcel.ReleaseDispatch();
}

// http://support.microsoft.com/kb/178783
// CreatePicutre(0, 0, 400, 400, "A:A,C:C,E:E,F:F", "����", "X��", "Y��");
void CExport2Excel::CreatePicutre(double dLeft, double dTop, double dWidth, double dHeight, // ͼ���λ�úʹ�С
								  const char* strDataSourceRange,
								  const char* strTitle,
								  const char* strX,
								  const char* strY)
{
	CChartObjects chartobjects;
	chartobjects.AttachDispatch(m_wsExcelSingle.ChartObjects(covOptional));

	// ����ͼ��λ�úʹ�С
	CChartObject chartobject = chartobjects.Add(dLeft, dTop, dWidth, dHeight);

	CChart chart;
	chart.AttachDispatch(chartobject.get_Chart());

	// ͼ���������Դ����Χ
	CRange range;
	// ����Դ -                         ѡ�ж������������ "A:A,C:C,E:E,F:F"
	range.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strDataSourceRange), vtMissing));

	// ��������Դ
	chart.SetSourceData(range, COleVariant((long)xlColumns));

	// ����ͼ������ - ����
	chart.put_ChartType(xlColumnClustered);

	// ��ʾͼ��(�Ҳ����Ϣ)
	chart.put_HasLegend(TRUE);
	CLegend legend;
	legend.AttachDispatch(chart.get_Legend());
	legend.put_Position(xlCorner);
	legend.DetachDispatch();


	// ����ͼ�����
	chart.put_HasTitle(TRUE);
	CChartTitle chartTitle;
	chartTitle.AttachDispatch(chart.get_ChartTitle());

	// ��������
	CFont0 font0;
	font0.AttachDispatch(chartTitle.get_Font());
	font0.put_Bold(_variant_t(TRUE));
	font0.put_Size(_variant_t(15));
	font0.DetachDispatch();

	chartTitle.put_Caption(strTitle);
	chartTitle.DetachDispatch();

	// ����x��
	CAxis axis;
	CAxisTitle axisTitle;
	axis.AttachDispatch(chart.Axes(COleVariant((long)xlCategory), xlPrimary));
	axis.put_HasTitle(TRUE);

	// �������� - x����������
	CTickLabels tickLabels;
	tickLabels.AttachDispatch(axis.get_TickLabels());
	font0.AttachDispatch(tickLabels.get_Font());
	font0.put_Size(_variant_t(4));
	font0.put_ColorIndex(_variant_t(3));
	font0.DetachDispatch();
	tickLabels.DetachDispatch();

	// x���ı�
	axisTitle.AttachDispatch(axis.get_AxisTitle());
	font0.AttachDispatch(axisTitle.get_Font());
	font0.put_Size(_variant_t(8));
	font0.DetachDispatch();
	axisTitle.put_Text(strX);
	axisTitle.DetachDispatch();
	axis.DetachDispatch();

	// ����y��
	axis.AttachDispatch(chart.Axes(_variant_t(xlValue), xlPrimary));
	axis.put_HasTitle(TRUE);

	// �������� - y����������
	tickLabels.AttachDispatch(axis.get_TickLabels());
	tickLabels.put_AutoScaleFont(_variant_t(TRUE));
	font0.AttachDispatch(tickLabels.get_Font());
	font0.put_Size(_variant_t(6));
	font0.put_ColorIndex(_variant_t(4));
	font0.DetachDispatch();
	tickLabels.DetachDispatch();

	// ����y������
	axisTitle.AttachDispatch(axis.get_AxisTitle());
	font0.AttachDispatch(axisTitle.get_Font());
	font0.put_Size(_variant_t(8));
	font0.DetachDispatch();
	axisTitle.put_Text(strY);
	axisTitle.DetachDispatch();
	axis.DetachDispatch();

	range.DetachDispatch();

	// ����1������ͼ����ɫ ������1��ʼ
	CSeries series;
	series.AttachDispatch(chart.SeriesCollection(_variant_t(1)));

	Cnterior interior;
	interior.AttachDispatch(series.get_Interior());
	interior.put_ColorIndex(_variant_t(3));
	interior.DetachDispatch();
	series.DetachDispatch();

	chart.DetachDispatch();
	chartobject.DetachDispatch();
	chartobjects.DetachDispatch();
}

/*
�ֺ�        ��ֵ      ����
�˺�        5         1.76
�ߺ�        5.5       1.94
С��        6.5       2.29
����        7.5       2.65
С��        9         3.18
���        10.5      3.70
С��        12        4.23
�ĺ�        14        4.94
С��        15        5.29
����        16        5.64
С��        18        6.35
����        22        7.76
Сһ        24        8.47
һ��        26        9.17
С��        36        12.70
����        42        14.82
*/
