/*
	Email:happyboy200032@163.com
	Blog: http://happyboy200032.blog.163.com
*/

#pragma once
#include "Excel\CApplication.h"
#include "Excel\CRange.h"
#include "Excel\CWorkbook.h"
#include "Excel\CWorkbooks.h"
#include "Excel\CWorksheet.h"
#include "Excel\CWorksheets.h"
#include "Excel\CWindow0.h"
#include "Excel\Cnterior.h"
#include "Excel\CFont0.h"

#include "Excel\CBorder.h"
#include "Excel\CBorders.h"

#include "Excel\CChart.h"
#include "Excel\CChartObject.h"
#include "Excel\CChartObjects.h"
#include "Excel\CChartTitle.h"
#include "Excel\CAxisTitle.h"
#include "Excel\CAxis.h"
#include "Excel\CTickLabels.h"
#include "Excel\CSeries.h"
#include "Excel\CLegend.h"

// 水平对齐方式
#define xlLeft -4131
#define xlCenter -4108
#define xlRight -4152

// 边框
#define xlDiagonalDown 5
#define xlDiagonalUp 6

#define xlEdgeLeft 7
#define xlEdgeTop 8
#define xlEdgeBottom 9
#define xlEdgeRight 10

#define xlNone -4142
#define xlContinuous 1
#define xlAutomatic -4105

// LineType
#define xlThin 2		// 细线
#define xlMedium -4138	// 粗线
#define xlThick 4		//粗粗线

#define xlInsideVertical 11
#define xlInsideHorizontal 12

// 图表
#define xlColumns 2
#define xlValue 2
#define xlPrimary 1
#define xlCategory 1

// 图表类型
#define xlColumnClustered 51

// 图例放在右上角
#define xlCorner 2

class CExport2Excel
{
public:
	CExport2Excel(void);
	~CExport2Excel(void);

private:
	CWorksheet m_wsExcelSingle;
	CWorksheets m_wsExcels;
	CWorkbook m_wbExcelSingle;
	CWorkbooks m_wbExcels;
	CApplication m_appExcel;
	CRange m_rangeExcel;

	CBorder m_borderExcel;
	CBorders m_bordersExcel;

	COleVariant covOptional;
	CString sExcelFile;

	int iSheetIndex;

private:
	bool bSheet;
	bool bCreate;

public:
	//创建Excel文件
	bool CreateExcel(CString sExcelFile);
	//打开Excel文件
	bool OpenExcel(CString sExcelFile);
	//创建表
	void CreateSheet(CString sSheetName);

	// 设置是否显示 “是否保存对文件的修改”的对话框
	void SetShowAlert(BOOL bShow);

	//设置指定列的列宽
	void SetColWidth(long iColumn, float iWidth);
	void SetRowHeight(long iRow, float iHeight);
	void SetAutoFilter(long iRow);
	//设置自动适应列宽
	void SetAudoColumn();
	//设置当前活动表
	void SetSheet(long iSheetIndex);
	//首行冻结
	void SetFirstLineFreezePanes();
	//首行颜色
	void SetFirstLineColor(COLORREF color = RGB(100, 100, 100));
	void SetLineColor(COLORREF color, long iRow, LPSTR pszFontName = NULL, int iFontSize = 12, bool bBold = true);
	void SetColor(COLORREF color, long iRow, long iColumn);

	//写Title
	void WriteTitle(LPSTR pszText);
	//写表的表头
	void WriteHeader(long iColumn, LPSTR pszText);
	//在指定的行和列显示文本
	void WriteData(long iRow, long iColumn, LPSTR pszText);
	//合并Title列
	void MergeTitleCells(long iRow, long iStartColumn, long iEndColumn);
	//合并单元格
	void MergeCells(long iRow, long iStartColumn, long iEndColumn);
	void MergeCells(long iStartRow, long iEndRow, long iStartColumn, long iEndColumn);
	// 获取合并单元格信息
	void GetMergeAreaInfo(long iRow, long iColumn, long& MergeRowCount, long& MergeColumnCount, long& MergeStartRow, long& MergeStartColumn);

	CString GetText(long iRow, long iColumn);

	// 公式读写操作
	CString GetCalcText(long iRow, long iColumn);
	void WriteCalcText(long iRow, long iColumn, LPSTR pszText);

	void InsertRow(long iRow);
	long GetRowCount();

	int GetSheetIndex();
	void SetWrapText(long iRow, long iColumn);

	// 设置边框
	void SetBorders(long iStartRow, long iStartColumn, long iEndRow, long iEndColumn, // 指定的单元格
							   bool bLeft, bool bTop, bool bRight, bool bBottom,				// 指定的四个边
							   bool bInsideVertical, bool bInsideHorizontal,					// 内部边框
							   long Left_LineType, long Top_LineType, long Right_LineType, long Bottom_LineType, // 四个边的线类型
							   long InsideVertical_LineType, long InsideHorizontal_LineType);

	// 设置单元格“文本”格式
	void SetNumberFormatLocal(long iRow, long iColumn, LPSTR pszText);
	// 设置对齐方式
	void SetHorizontalAlignment(long iRow, long iColumn, long HAType);
	// 设置字体
	void SetFont(long iRow, LPSTR pszFontName, int iFontSize, bool bBold);
	void SetFont(long iRow, long iColumn, LPSTR pszFontName, int iFontSize, bool bBold);

	//保存Excel文件
	void Save();
	void SaveAs(CString strExcelFile);

	//关闭Excel操作
	void Close();

	// 创建图表
	void CreatePicutre(double dLeft, double dTop, double dWidth, double dHeight, // 图标的位置和大小
								  const char* strDataSourceRange,
								  const char* strTitle,
								  const char* strX,
								  const char* strY);
};
