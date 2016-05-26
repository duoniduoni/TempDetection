#include "StdAfx.h"
#include <afxdisp.h>
#include "Export2Excel.h"
//using namespace O12;
/*
 Email:happyboy200032@163.com
 Blog: http://happyboy200032.blog.163.com

 1.
	程序中所有有关序号和索引的一律为数字1开始
 2.
	在使用本类的时候，需要初始化COM库
	if(CoInitialize(NULL) != NULL)
	{
		AfxMessageBox("初始化COM失败!");
	}
 3.
	//在程序退出的时候需要清除COM库
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
	创建Excel文件
	sExcelFile:	Excel文件名
*/
bool CExport2Excel::CreateExcel(CString sExcelFile)
{
	bCreate = true;
	//使用Excel类型库接口的方式实现
	this->sExcelFile = sExcelFile;
	covOptional = COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if(!m_appExcel.CreateDispatch("Excel.Application",NULL))
	{
		//创建Excel服务失败
		return false;
	}

	m_wbExcels.AttachDispatch(m_appExcel.get_Workbooks(),true);
	m_wbExcelSingle.AttachDispatch(m_wbExcels.Add(covOptional));

	//得到Worksheets 
	m_wsExcels.AttachDispatch(m_wbExcelSingle.get_Worksheets(),true);

	//删除表 只剩下一个表
	for (short i = 1; i<= (short)m_wsExcels.get_Count(); i++)
	{
		m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((short)i)));
		m_wsExcelSingle.Delete();
	}

	iSheetIndex = 1;
	bSheet = true;
	return true;
}

//打开Excel文件
bool CExport2Excel::OpenExcel(CString sExcelFile)
{
	bCreate = false;
	//使用Excel类型库接口的方式实现
	this->sExcelFile = sExcelFile;
	covOptional = COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if(!m_appExcel.CreateDispatch("Excel.Application",NULL))
	{
		//创建Excel服务失败
		return false;
	}

	m_wbExcels.AttachDispatch(m_appExcel.get_Workbooks(),true);
	m_wbExcelSingle.AttachDispatch(m_wbExcels.Open(sExcelFile.GetBuffer(), vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing));

	//得到Worksheets 
	m_wsExcels.AttachDispatch(m_wbExcelSingle.get_Worksheets(),true);
/*
	long iSheet = m_wsExcels.get_Count();
	long i;
	for (i = 1; i <= iSheet; i++)
	{
		m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((long)(i))));
		if (m_wsExcelSingle.get_Name().CompareNoCase("文件") == 0)
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
	创建表
	sSheetName:	表名
*/
void CExport2Excel::CreateSheet(CString sSheetName)
{
	if (bSheet)
	{
		//第一个表
		m_wsExcelSingle.AttachDispatch(m_wsExcels.get_Item(COleVariant((short)(1))));
	}else{
		//不是第一个表
		m_wsExcelSingle.AttachDispatch(m_wsExcels.Add(vtMissing, vtMissing, COleVariant((short)(1)), vtMissing));
	}

	bSheet = false;

	iSheetIndex = 1;
	//设置表名
	m_wsExcelSingle.put_Name(sSheetName);
	m_rangeExcel.AttachDispatch(m_wsExcelSingle.get_UsedRange(), TRUE);
}

void CExport2Excel::SetShowAlert(BOOL bShow)
{
	m_appExcel.put_DisplayAlerts(bShow);
}

/*
	设置当前工作表
	iSheetIndex: 为创建表的顺序（倒序，即最后创建的表序号为1）
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
	写表头
	iColumn:指定列
	pszText:文本
*/
void CExport2Excel::WriteHeader(long iColumn, LPSTR pszText)
{
	WriteData(1, iColumn, pszText);
}

/*
	iRow:		行号
	iColumn:	列号
	pszText:	要写入的文本
*/
void CExport2Excel::WriteData(long iRow, long iColumn, LPSTR pszText)
{
	// 向Excel中写数据
	m_rangeExcel.put_Item(_variant_t(iRow + 1), _variant_t(iColumn), COleVariant(pszText));
	//SetAudoColumn();
}

//读取文本
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

//读取公式
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

//读取合并单元格信息
void CExport2Excel::GetMergeAreaInfo(long iRow, long iColumn, long& MergeRowCount, long& MergeColumnCount, long& MergeStartRow, long& MergeStartColumn)
{
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)(iColumn))).pdispVal, true);

	CRange unionRange;
	unionRange.AttachDispatch(tRange.get_MergeArea());

	//合并单元格的行数
	CRange mergeAreaRange_HangCount;
	mergeAreaRange_HangCount.AttachDispatch(unionRange.get_Rows());
	MergeRowCount = mergeAreaRange_HangCount.get_Count();
	mergeAreaRange_HangCount.ReleaseDispatch();

	//合并单元格的列数
	CRange mergeAreaRange_LieCount;
	mergeAreaRange_LieCount.AttachDispatch(unionRange.get_Columns());
	MergeColumnCount = mergeAreaRange_LieCount.get_Count();
	mergeAreaRange_LieCount.ReleaseDispatch();

	//起始行，从1开始
	MergeStartRow = unionRange.get_Row();
	//起始列，从1开始
	MergeStartColumn = unionRange.get_Column();

	unionRange.ReleaseDispatch();
	tRange.ReleaseDispatch();
}

// 写公式
void CExport2Excel::WriteCalcText(long iRow, long iColumn, LPSTR pszText)
{
	// 向Excel中写数据
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow + 1), _variant_t((long)(iColumn))).pdispVal, true);

	tRange.put_Formula(COleVariant(pszText));
	tRange.ReleaseDispatch();
}

// 设置单元格格式 @ = 文本格式
void CExport2Excel::SetNumberFormatLocal(long iRow, long iColumn, LPSTR pszText)
{
	// 向Excel中写数据
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow + 1), _variant_t((long)(iColumn))).pdispVal, true);

	tRange.put_NumberFormatLocal(COleVariant(pszText));
	tRange.ReleaseDispatch();
}

// 设置单元格水平右对齐
void CExport2Excel::SetHorizontalAlignment(long iRow, long iColumn, long HAType)
{
	// 向Excel中写数据
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow + 1), _variant_t((long)(iColumn))).pdispVal, true);

	tRange.put_HorizontalAlignment(_variant_t(HAType));
	tRange.ReleaseDispatch();
}

/*
	设置列宽
	iColumn:	指定列
	iWidth:		宽度
*/
void CExport2Excel::SetColWidth(long iColumn, float iWidth)
{
	CRange tRange;
	//得到第一行
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t(iColumn)).pdispVal, true);
	//设置列宽
	tRange.put_ColumnWidth(_variant_t(iWidth));
	tRange.ReleaseDispatch();
}

/*
	设置列宽
	iRow:	指定行
	iHeight:		高度
*/
void CExport2Excel::SetRowHeight(long iRow, float iHeight)
{
	CRange tRange;
	//得到第一列
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)1)).pdispVal, true);
	//设置列高
	tRange.put_RowHeight(_variant_t(iHeight));
	tRange.ReleaseDispatch();
}

//error
void CExport2Excel::SetAutoFilter(long iRow)
{
	CRange tRange;
	//得到第一列
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)1)).pdispVal, true);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//设置列高
	tRange.AutoFilter(COleVariant((long)1), COleVariant((long)2), 1, COleVariant((long)4), vtMissing);
	tRange.ReleaseDispatch();
}

//设置自动换行
void CExport2Excel::SetWrapText(long iRow, long iColumn)
{
	CRange tRange;
	//得到第一列
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)iRow), _variant_t((long)iColumn)).pdispVal, true);
	COleVariant varTrue((short)TRUE,VT_BOOL);
	tRange.put_WrapText(varTrue);
	tRange.ReleaseDispatch();
}

//自动调整列宽
void CExport2Excel::SetAudoColumn()
{
	//选择所有列
	CRange range;
	range.AttachDispatch(m_wsExcelSingle.get_Cells());
	range.Select();

	//列设置为自动调整列宽
	CRange range1;
	range1.AttachDispatch(range.get_Columns());
	range1.AutoFit();

	range1.ReleaseDispatch();
	range.ReleaseDispatch();

	//取消选中所有列（即选中任意一个单元格即可）
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//合并单元格 均从1开始
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

	//取消选中所有列（即选中任意一个单元格即可）
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//合并单元格 均从1开始
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

	//取消选中所有列（即选中任意一个单元格即可）
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//合并单元格 均从1开始
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

	//取消选中所有列（即选中任意一个单元格即可）
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
}

//设置边框
//SetBorders(4, 1, iRow, 8, true, true, true, true, true, true, xlMedium, xlMedium, xlMedium, xlMedium, xlThin, xlThin)
void CExport2Excel::SetBorders(long iStartRow, long iStartColumn, long iEndRow, long iEndColumn, // 指定的单元格
							   bool bLeft, bool bTop, bool bRight, bool bBottom,				// 指定的四个边
							   bool bInsideVertical, bool bInsideHorizontal,					// 内部边框
							   long Left_LineType, long Top_LineType, long Right_LineType, long Bottom_LineType, // 四个边的线类型
							   long InsideVertical_LineType, long InsideHorizontal_LineType)	// 内部边框的线类型
{
	iStartColumn += 'A' - 1;
	iEndColumn += 'A' - 1;

	CString strT;
	strT.Format("%C%d:%C%d", iStartColumn, iStartRow, iEndColumn, iEndRow);

	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strT.GetBuffer()), vtMissing), true);
	tRange.Select();

	//为四周和内部加上边框
	m_bordersExcel.AttachDispatch(tRange.get_Borders());

	// 置空
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

	//取消选中所有列（即选中任意一个单元格即可）
	tRange.AttachDispatch(m_rangeExcel.get_Item(_variant_t((long)1), _variant_t((long)(1))).pdispVal, true);
	tRange.Select();
	tRange.ReleaseDispatch();
	//http://www.cppblog.com/greatws/archive/2008/09/21/62423.html
}

//首行冻结
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

//首行颜色
void CExport2Excel::SetFirstLineColor(COLORREF color)
{
	CRange tRange;
	tRange.AttachDispatch(m_rangeExcel.get_Range(_variant_t("2:2"), vtMissing), true);
	tRange.Select();

	//设置居中
	tRange.put_HorizontalAlignment(_variant_t((short)-4108));
	//设置粗体
	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	tFont.put_Bold(_variant_t(true));
	tFont.put_Name(_variant_t("宋体"));
	tFont.put_Size(_variant_t(10));
	tFont.ReleaseDispatch();

	//设置颜色
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

	//设置居中
	tRange.put_HorizontalAlignment(_variant_t((short)-4108));
	//设置粗体
	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	if (bBold)
		tFont.put_Bold(_variant_t(true));

	if (pszFontName != NULL)
		tFont.put_Name(_variant_t(pszFontName));

	tFont.put_Size(_variant_t(iFontSize));
	tFont.ReleaseDispatch();

	//设置颜色
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
	//设置居中
	tRange.put_HorizontalAlignment(_variant_t((short)-4108));
	//设置粗体
	CFont0 tFont;
	tFont.AttachDispatch(tRange.get_Font());
	if (bBold)
		tFont.put_Bold(_variant_t(true));

	if (pszFontName != NULL)
		tFont.put_Name(_variant_t(pszFontName));

	tFont.put_Size(_variant_t(iFontSize));
	tFont.ReleaseDispatch();
*/
	//设置颜色
	Cnterior tNterior;
	tNterior.AttachDispatch(tRange.get_Interior());

	tNterior.put_Color(_variant_t(color));
	tNterior.ReleaseDispatch();
	tRange.ReleaseDispatch();
}

/*
	增加行，当前行向下移动
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
		//app.SetDisplayAlerts(false); // 不弹出对话框询问是否保存
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
// CreatePicutre(0, 0, 400, 400, "A:A,C:C,E:E,F:F", "标题", "X轴", "Y轴");
void CExport2Excel::CreatePicutre(double dLeft, double dTop, double dWidth, double dHeight, // 图标的位置和大小
								  const char* strDataSourceRange,
								  const char* strTitle,
								  const char* strX,
								  const char* strY)
{
	CChartObjects chartobjects;
	chartobjects.AttachDispatch(m_wsExcelSingle.ChartObjects(covOptional));

	// 创建图表位置和大小
	CChartObject chartobject = chartobjects.Add(dLeft, dTop, dWidth, dHeight);

	CChart chart;
	chart.AttachDispatch(chartobject.get_Chart());

	// 图表的数据来源、范围
	CRange range;
	// 数据源 -                         选中多个不连续的列 "A:A,C:C,E:E,F:F"
	range.AttachDispatch(m_rangeExcel.get_Range(_variant_t(strDataSourceRange), vtMissing));

	// 设置数据源
	chart.SetSourceData(range, COleVariant((long)xlColumns));

	// 设置图表类型 - 柱形
	chart.put_ChartType(xlColumnClustered);

	// 显示图例(右侧的信息)
	chart.put_HasLegend(TRUE);
	CLegend legend;
	legend.AttachDispatch(chart.get_Legend());
	legend.put_Position(xlCorner);
	legend.DetachDispatch();


	// 设置图表标题
	chart.put_HasTitle(TRUE);
	CChartTitle chartTitle;
	chartTitle.AttachDispatch(chart.get_ChartTitle());

	// 设置字体
	CFont0 font0;
	font0.AttachDispatch(chartTitle.get_Font());
	font0.put_Bold(_variant_t(TRUE));
	font0.put_Size(_variant_t(15));
	font0.DetachDispatch();

	chartTitle.put_Caption(strTitle);
	chartTitle.DetachDispatch();

	// 设置x轴
	CAxis axis;
	CAxisTitle axisTitle;
	axis.AttachDispatch(chart.Axes(COleVariant((long)xlCategory), xlPrimary));
	axis.put_HasTitle(TRUE);

	// 设置字体 - x轴坐标文字
	CTickLabels tickLabels;
	tickLabels.AttachDispatch(axis.get_TickLabels());
	font0.AttachDispatch(tickLabels.get_Font());
	font0.put_Size(_variant_t(4));
	font0.put_ColorIndex(_variant_t(3));
	font0.DetachDispatch();
	tickLabels.DetachDispatch();

	// x轴文本
	axisTitle.AttachDispatch(axis.get_AxisTitle());
	font0.AttachDispatch(axisTitle.get_Font());
	font0.put_Size(_variant_t(8));
	font0.DetachDispatch();
	axisTitle.put_Text(strX);
	axisTitle.DetachDispatch();
	axis.DetachDispatch();

	// 设置y轴
	axis.AttachDispatch(chart.Axes(_variant_t(xlValue), xlPrimary));
	axis.put_HasTitle(TRUE);

	// 设置字体 - y轴坐标文字
	tickLabels.AttachDispatch(axis.get_TickLabels());
	tickLabels.put_AutoScaleFont(_variant_t(TRUE));
	font0.AttachDispatch(tickLabels.get_Font());
	font0.put_Size(_variant_t(6));
	font0.put_ColorIndex(_variant_t(4));
	font0.DetachDispatch();
	tickLabels.DetachDispatch();

	// 设置y轴名称
	axisTitle.AttachDispatch(axis.get_AxisTitle());
	font0.AttachDispatch(axisTitle.get_Font());
	font0.put_Size(_variant_t(8));
	font0.DetachDispatch();
	axisTitle.put_Text(strY);
	axisTitle.DetachDispatch();
	axis.DetachDispatch();

	range.DetachDispatch();

	// 设置1号柱形图的颜色 索引由1开始
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
字号        磅值      毫米
八号        5         1.76
七号        5.5       1.94
小六        6.5       2.29
六号        7.5       2.65
小五        9         3.18
五号        10.5      3.70
小四        12        4.23
四号        14        4.94
小三        15        5.29
三号        16        5.64
小二        18        6.35
二号        22        7.76
小一        24        8.47
一号        26        9.17
小初        36        12.70
初号        42        14.82
*/
