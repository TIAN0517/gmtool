// DlgAwardTitleEdit.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "DlgAwardTitleEdit.h"
#include "afxdialogex.h"

#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Helper/HLibDataConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgAwardTitleEdit dialog

IMPLEMENT_DYNAMIC(CDlgAwardTitleEdit, CDialogEx)

CDlgAwardTitleEdit::CDlgAwardTitleEdit(CWnd* pParent /*=NULL*/, SAWARD_TITLE_DATA_EX* pData /*= NULL*/)
	: CDialogEx(CDlgAwardTitleEdit::IDD, pParent)
	, m_pData(NULL)
{
	m_pData = pData;
}

CDlgAwardTitleEdit::~CDlgAwardTitleEdit()
{
}

void CDlgAwardTitleEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAwardTitleEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgAwardTitleEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgAwardTitleEdit::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgAwardTitleEdit message handlers
BOOL CDlgAwardTitleEdit::OnInitDialog()
{
	CDialog::OnInitDialog();


	std::string strTypes[EMAWARD_TITLE_TYPE_SIZE] = 
	{
		"0",
		"1",
		"2",
	};

	SetWin_Combo_Init( this, IDC_AWARD_TITLE_CMD_TYPE, strTypes, EMAWARD_TITLE_TYPE_SIZE );

	DataDefault();
	DataShow();

	return TRUE;
}

BOOL CDlgAwardTitleEdit::DataDefault()
{
	SetWin_Num_int( this, IDC_AWARD_TITLE_EDIT_ID, 0 );
	SetWin_Text( this, IDC_AWARD_TITLE_EDIT_TITLE, "" );
	SetWin_Combo_Sel( this, IDC_AWARD_TITLE_CMD_TYPE, 0 );
	
	return TRUE;
}

BOOL CDlgAwardTitleEdit::DataShow()
{
	if ( !m_pData )	return FALSE;

	SetWin_Num_int( this, IDC_AWARD_TITLE_EDIT_ID, m_pData->bAdd? -1 : m_pData->sTitle.dwID );
	SetWin_Text( this, IDC_AWARD_TITLE_EDIT_TITLE, m_pData->sTitle.szTitle );
	SetWin_Combo_Sel( this, IDC_AWARD_TITLE_CMD_TYPE, m_pData->sTitle.emType );

	return TRUE;
}

BOOL CDlgAwardTitleEdit::DataSave()
{
	if ( !m_pData )	return FALSE;

	std::string strText = GetWin_Text( this, IDC_AWARD_TITLE_EDIT_TITLE );
	StringCbCopy( m_pData->sTitle.szTitle, AWARD_TITLE_LENGTH+1, strText.c_str() );

	m_pData->sTitle.emType = (EMAWARD_TITLE_TYPE)GetWin_Combo_Sel( this, IDC_AWARD_TITLE_CMD_TYPE );

	return TRUE;
}

void CDlgAwardTitleEdit::OnBnClickedOk()
{
	if ( !DataSave() ) return;

	CDialogEx::OnOK();
}

void CDlgAwardTitleEdit::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
