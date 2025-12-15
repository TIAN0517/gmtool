// CharEditPageCombatRecord.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "CharEditPageCombatRecord.h"
#include "afxdialogex.h"

#include "./CharEditTab.h"

#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Client/G-Logic/GLCharData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCharEditPageCombatRecord dialog

IMPLEMENT_DYNAMIC(CCharEditPageCombatRecord, CPropertyPage)

CCharEditPageCombatRecord::CCharEditPageCombatRecord(LOGFONT logfont, SCHARDATA2* pData)
	: CPropertyPage(CCharEditPageCombatRecord::IDD)
	, m_pFont ( NULL )
	, m_pData( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	m_pData = pData;
}

CCharEditPageCombatRecord::~CCharEditPageCombatRecord()
{
	SAFE_DELETE ( m_pFont );
}

void CCharEditPageCombatRecord::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCharEditPageCombatRecord, CPropertyPage)
END_MESSAGE_MAP()


// CCharEditPageCombatRecord message handlers
BOOL CCharEditPageCombatRecord::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_pSheetTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	m_bDlgInit = TRUE;




	DataDefault();
	DataShow();

	return TRUE;  
}

void CCharEditPageCombatRecord::DataDefault()
{
}

void CCharEditPageCombatRecord::DataShow()
{
	if ( !m_pData )	return;

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVP_KILLS, m_pData->m_sCombatRecord.dwPVPKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVP_DEATHS, m_pData->m_sCombatRecord.dwPVPDeaths );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVP_RESU, m_pData->m_sCombatRecord.dwPVPResu );

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_TYRANNY_KILLS, m_pData->m_sCombatRecord.dwTyrannyKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_TYRANNY_DEATHS, m_pData->m_sCombatRecord.dwTyrannyDeaths );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_TYRANNY_RESU, m_pData->m_sCombatRecord.dwTyrannyResu );

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_WAR_KILLS, m_pData->m_sCombatRecord.dwClubWarKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_WAR_DEATHS, m_pData->m_sCombatRecord.dwClubWarDeaths );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_WAR_RESU, m_pData->m_sCombatRecord.dwClubWarResu );

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CAPTURE_THE_FLAG_KILLS, m_pData->m_sCombatRecord.dwCaptureTheFlagKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CAPTURE_THE_FLAG_DEATHS, m_pData->m_sCombatRecord.dwCaptureTheFlagDeaths );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CAPTURE_THE_FLAG_RESU, m_pData->m_sCombatRecord.dwCaptureTheFlagResu );

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_SCHOOL_WAR_KILLS, m_pData->m_sCombatRecord.dwSchoolWarsKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_SCHOOL_WAR_DEATHS, m_pData->m_sCombatRecord.dwSchoolWarsDeaths );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_SCHOOL_WAR_RESU, m_pData->m_sCombatRecord.dwSchoolWarsResu );

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_DEATH_MATCH_KILLS, m_pData->m_sCombatRecord.dwClubDeathMatchKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_DEATH_MATCH_DEATHS, m_pData->m_sCombatRecord.dwClubDeathMatchDeaths );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_DEATH_MATCH_RESU, m_pData->m_sCombatRecord.dwClubDeathMatchResu );

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PK_MAP_KILLS, m_pData->m_sCombatRecord.dwPKMapKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PK_MAP_DEATHS, m_pData->m_sCombatRecord.dwPKMapDeaths );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PK_MAP_RESU, m_pData->m_sCombatRecord.dwPKMapResu );

	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVE_KILLS, m_pData->m_sCombatRecord.dwPVEKills );
	SetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVE_DEATHS, m_pData->m_sCombatRecord.dwPVEDeaths );
	SetWin_Num_LONGLONG( this, IDC_EDIT_COMBAT_RECORD_PVE_GOLD_GAIN, m_pData->m_sCombatRecord.llPVEMoneyGain );


}

BOOL CCharEditPageCombatRecord::DataSave()
{
	if ( !m_pData )	return FALSE;

	m_pData->m_sCombatRecord.dwPVPKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVP_KILLS );
	m_pData->m_sCombatRecord.dwPVPDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVP_DEATHS );
	m_pData->m_sCombatRecord.dwPVPResu = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVP_RESU );

	m_pData->m_sCombatRecord.dwTyrannyKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_TYRANNY_KILLS );
	m_pData->m_sCombatRecord.dwTyrannyDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_TYRANNY_DEATHS );
	m_pData->m_sCombatRecord.dwTyrannyResu = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_TYRANNY_RESU );

	m_pData->m_sCombatRecord.dwClubWarKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_WAR_KILLS );
	m_pData->m_sCombatRecord.dwClubWarDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_WAR_DEATHS );
	m_pData->m_sCombatRecord.dwClubWarResu = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_WAR_RESU );

	m_pData->m_sCombatRecord.dwCaptureTheFlagKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CAPTURE_THE_FLAG_KILLS );
	m_pData->m_sCombatRecord.dwCaptureTheFlagDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CAPTURE_THE_FLAG_DEATHS );
	m_pData->m_sCombatRecord.dwCaptureTheFlagResu = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CAPTURE_THE_FLAG_RESU );

	m_pData->m_sCombatRecord.dwSchoolWarsKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_SCHOOL_WAR_KILLS );
	m_pData->m_sCombatRecord.dwSchoolWarsDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_SCHOOL_WAR_DEATHS );
	m_pData->m_sCombatRecord.dwSchoolWarsResu = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_SCHOOL_WAR_RESU );

	m_pData->m_sCombatRecord.dwClubDeathMatchKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_DEATH_MATCH_KILLS );
	m_pData->m_sCombatRecord.dwClubDeathMatchDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_DEATH_MATCH_DEATHS );
	m_pData->m_sCombatRecord.dwClubDeathMatchResu = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_CLUB_DEATH_MATCH_RESU );

	m_pData->m_sCombatRecord.dwPKMapKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PK_MAP_KILLS );
	m_pData->m_sCombatRecord.dwPKMapDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PK_MAP_DEATHS );
	m_pData->m_sCombatRecord.dwPKMapResu = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PK_MAP_RESU );

	m_pData->m_sCombatRecord.dwPVEKills = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVE_KILLS );
	m_pData->m_sCombatRecord.dwPVEDeaths = GetWin_Num_int( this, IDC_EDIT_COMBAT_RECORD_PVE_DEATHS );
	m_pData->m_sCombatRecord.llPVEMoneyGain = GetWin_Num_LONGLONG( this, IDC_EDIT_COMBAT_RECORD_PVE_GOLD_GAIN );


	return TRUE;
}