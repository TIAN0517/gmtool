// CharEditPagePKCombo.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "CharEditPagePKCombo.h"
#include "afxdialogex.h"

#include "./CharEditTab.h"

#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Client/G-Logic/GLCharData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCharEditPagePKCombo dialog

IMPLEMENT_DYNAMIC(CCharEditPagePKCombo, CPropertyPage)

CCharEditPagePKCombo::CCharEditPagePKCombo(LOGFONT logfont, SCHARDATA2* pData)
	: CPropertyPage(CCharEditPagePKCombo::IDD)
	, m_pFont ( NULL )
	, m_pData( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	m_pData = pData;
}

CCharEditPagePKCombo::~CCharEditPagePKCombo()
{
	SAFE_DELETE ( m_pFont );
}

void CCharEditPagePKCombo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCharEditPagePKCombo, CPropertyPage)
END_MESSAGE_MAP()


// CCharEditPagePKCombo message handlers
BOOL CCharEditPagePKCombo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_pSheetTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	m_bDlgInit = TRUE;




	DataDefault();
	DataShow();

	return TRUE;  
}

void CCharEditPagePKCombo::DataDefault()
{
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_00, 0 );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_01, 0 );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_02, 0 );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_03, 0 );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_04, 0 );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_05, 0 );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_06, 0 );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_07, 0 );
}

void CCharEditPagePKCombo::DataShow()
{
	if ( !m_pData )	return;

	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_00, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_00] );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_01, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_01] );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_02, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_02] );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_03, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_03] );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_04, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_04] );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_05, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_05] );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_06, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_06] );
	SetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_07, m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_07] );
}

BOOL CCharEditPagePKCombo::DataSave()
{
	if ( !m_pData )	return FALSE;

	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_00] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_00 );
	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_01] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_01 );
	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_02] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_02 );
	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_03] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_03 );
	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_04] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_04 );
	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_05] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_05 );
	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_06] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_06 );
	m_pData->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_07] = GetWin_Num_int( this, IDC_EDIT_CHAR_PK_COMBO_07 );

	return TRUE;
}
