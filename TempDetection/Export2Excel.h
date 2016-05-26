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

// ˮƽ���뷽ʽ
#define xlLeft -4131
#define xlCenter -4108
#define xlRight -4152

// �߿�
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
#define xlThin 2		// ϸ��
#define xlMedium -4138	// ����
#define xlThick 4		//�ִ���

#define xlInsideVertical 11
#define xlInsideHorizontal 12

// ͼ��
#define xlColumns 2
#define xlValue 2
#define xlPrimary 1
#define xlCategory 1

// ͼ������
#define xlColumnClustered 51

// ͼ���������Ͻ�
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
	//����Excel�ļ�
	bool CreateExcel(CString sExcelFile);
	//��Excel�ļ�
	bool OpenExcel(CString sExcelFile);
	//������
	void CreateSheet(CString sSheetName);

	// �����Ƿ���ʾ ���Ƿ񱣴���ļ����޸ġ��ĶԻ���
	void SetShowAlert(BOOL bShow);

	//����ָ���е��п�
	void SetColWidth(long iColumn, float iWidth);
	void SetRowHeight(long iRow, float iHeight);
	void SetAutoFilter(long iRow);
	//�����Զ���Ӧ�п�
	void SetAudoColumn();
	//���õ�ǰ���
	void SetSheet(long iSheetIndex);
	//���ж���
	void SetFirstLineFreezePanes();
	//������ɫ
	void SetFirstLineColor(COLORREF color = RGB(100, 100, 100));
	void SetLineColor(COLORREF color, long iRow, LPSTR pszFontName = NULL, int iFontSize = 12, bool bBold = true);
	void SetColor(COLORREF color, long iRow, long iColumn);

	//дTitle
	void WriteTitle(LPSTR pszText);
	//д��ı�ͷ
	void WriteHeader(long iColumn, LPSTR pszText);
	//��ָ�����к�����ʾ�ı�
	void WriteData(long iRow, long iColumn, LPSTR pszText);
	//�ϲ�Title��
	void MergeTitleCells(long iRow, long iStartColumn, long iEndColumn);
	//�ϲ���Ԫ��
	void MergeCells(long iRow, long iStartColumn, long iEndColumn);
	void MergeCells(long iStartRow, long iEndRow, long iStartColumn, long iEndColumn);
	// ��ȡ�ϲ���Ԫ����Ϣ
	void GetMergeAreaInfo(long iRow, long iColumn, long& MergeRowCount, long& MergeColumnCount, long& MergeStartRow, long& MergeStartColumn);

	CString GetText(long iRow, long iColumn);

	// ��ʽ��д����
	CString GetCalcText(long iRow, long iColumn);
	void WriteCalcText(long iRow, long iColumn, LPSTR pszText);

	void InsertRow(long iRow);
	long GetRowCount();

	int GetSheetIndex();
	void SetWrapText(long iRow, long iColumn);

	// ���ñ߿�
	void SetBorders(long iStartRow, long iStartColumn, long iEndRow, long iEndColumn, // ָ���ĵ�Ԫ��
							   bool bLeft, bool bTop, bool bRight, bool bBottom,				// ָ�����ĸ���
							   bool bInsideVertical, bool bInsideHorizontal,					// �ڲ��߿�
							   long Left_LineType, long Top_LineType, long Right_LineType, long Bottom_LineType, // �ĸ��ߵ�������
							   long InsideVertical_LineType, long InsideHorizontal_LineType);

	// ���õ�Ԫ���ı�����ʽ
	void SetNumberFormatLocal(long iRow, long iColumn, LPSTR pszText);
	// ���ö��뷽ʽ
	void SetHorizontalAlignment(long iRow, long iColumn, long HAType);
	// ��������
	void SetFont(long iRow, LPSTR pszFontName, int iFontSize, bool bBold);
	void SetFont(long iRow, long iColumn, LPSTR pszFontName, int iFontSize, bool bBold);

	//����Excel�ļ�
	void Save();
	void SaveAs(CString strExcelFile);

	//�ر�Excel����
	void Close();

	// ����ͼ��
	void CreatePicutre(double dLeft, double dTop, double dWidth, double dHeight, // ͼ���λ�úʹ�С
								  const char* strDataSourceRange,
								  const char* strTitle,
								  const char* strX,
								  const char* strY);
};
