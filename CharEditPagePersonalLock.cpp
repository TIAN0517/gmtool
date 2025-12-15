// CharEditPageBasic.cpp : implementation file
//

#include "stdafx.h"
#include "./GMTool.h"
#include "./CharEditPagePersonalLock.h"

#include "./CharEditTab.h"
#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Client/G-Logic/GLCharData.h"
#include "../Lib_Client/G-Logic/GLogicData.h"

#include "./GMToolDlg.h"
#include "../Lib_Client/G-Logic/GLMapList.h"

#include "./Logic/GMToolGlobal.h"
#include "./Logic/GMToolOdbcBase.h"

#include "../Lib_Helper/HLibColorValue.h"

#include "./DlgMap.h"
#include "./SelColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCharEditPageBasic dialog

IMPLEMENT_DYNAMIC(CCharEditPagePersonalLock, CPropertyPage)

CCharEditPagePersonalLock::CCharEditPagePersonalLock(LOGFONT logfont, SCHARDATA2* pData)
	: CPropertyPage(CCharEditPagePersonalLock::IDD)
	, m_pFont ( NULL )
	, m_pData( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	m_pData = pData;
}

CCharEditPagePersonalLock::~CCharEditPagePersonalLock()
{
	SAFE_DELETE ( m_pFont );
}

void CCharEditPagePersonalLock::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCharEditPagePersonalLock, CPropertyPage)
END_MESSAGE_MAP()


// CCharEditPageBasic message handlers
BOOL CCharEditPagePersonalLock::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_pSheetTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	m_bDlgInit = TRUE;


	

	DataDefault();
	DataShow();

	return TRUE;  
}

void CCharEditPagePersonalLock::DataDefault()
{
	SetWin_Check( this, IDC_CHECK_CHAR_PLOCK_PUTON_LOCK, FALSE );
	SetWin_Check( this, IDC_CHECK_CHAR_PLOCK_INVEN_LOCK, FALSE );
	SetWin_Check( this, IDC_CHECK_CHAR_PLOCK_LOCKER_LOCK, FALSE );

	SetWin_Text( this, IDC_EDIT_CHAR_PLOCK_PUTON_PIN, "" );
	SetWin_Text( this, IDC_EDIT_CHAR_PLOCK_INVEN_PIN, "" );
	SetWin_Text( this, IDC_EDIT_CHAR_PLOCK_LOCKER_PIN, "" );
}

void CCharEditPagePersonalLock::DataShow()
{
	if ( !m_pData ){
		return;
	}

	SetWin_Check( this, IDC_CHECK_CHAR_PLOCK_PUTON_LOCK, m_pData->m_sPersonalLock[EMPERSONAL_LOCK_EQUIP].bLock );
	SetWin_Check( this, IDC_CHECK_CHAR_PLOCK_INVEN_LOCK, m_pData->m_sPersonalLock[EMPERSONAL_LOCK_INVEN].bLock );
	SetWin_Check( this, IDC_CHECK_CHAR_PLOCK_LOCKER_LOCK, m_pData->m_sPersonalLock[EMPERSONAL_LOCK_LOCKER].bLock );

	SetWin_Text( this, IDC_EDIT_CHAR_PLOCK_PUTON_PIN, m_pData->m_sPersonalLock[EMPERSONAL_LOCK_EQUIP].szPin );
	SetWin_Text( this, IDC_EDIT_CHAR_PLOCK_INVEN_PIN, m_pData->m_sPersonalLock[EMPERSONAL_LOCK_INVEN].szPin );
	SetWin_Text( this, IDC_EDIT_CHAR_PLOCK_LOCKER_PIN, m_pData->m_sPersonalLock[EMPERSONAL_LOCK_LOCKER].szPin );
}

BOOL CCharEditPagePersonalLock::DataSave()
{
	if ( !m_pData ){
		return FALSE;
	}

	BOOL bLockPutOn = GetWin_Check( this, IDC_CHECK_CHAR_PLOCK_PUTON_LOCK );
	BOOL bLockInven =  GetWin_Check( this, IDC_CHECK_CHAR_PLOCK_INVEN_LOCK );
	BOOL bLockLocker = GetWin_Check( this, IDC_CHECK_CHAR_PLOCK_LOCKER_LOCK );

	std::string strPinPutOn = GetWin_Text( this, IDC_EDIT_CHAR_PLOCK_PUTON_PIN );
	std::string strPinInven = GetWin_Text( this, IDC_EDIT_CHAR_PLOCK_INVEN_PIN );
	std::string strPinLocker = GetWin_Text( this, IDC_EDIT_CHAR_PLOCK_LOCKER_PIN );

	if ( strPinPutOn.size() > PERSONAL_LOCK_PIN_SIZE )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "PutOn Pin max %u digit", PERSONAL_LOCK_PIN_SIZE );
		return FALSE;
	}

	if ( strPinPutOn.find_first_not_of( "0123456789" ) != std::string::npos )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "PutOn Pin should be numbers only" );
		return FALSE;
	}

	if ( strPinInven.size() > PERSONAL_LOCK_PIN_SIZE )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Inven Pin max %u digit", PERSONAL_LOCK_PIN_SIZE );
		return FALSE;
	}

	if ( strPinInven.find_first_not_of( "0123456789" ) != std::string::npos )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Inven Pin should be numbers only" );
		return FALSE;
	}

	if ( strPinLocker.size() > PERSONAL_LOCK_PIN_SIZE )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Locker Pin max %u digit", PERSONAL_LOCK_PIN_SIZE );
		return FALSE;
	}

	if ( strPinLocker.find_first_not_of( "0123456789" ) != std::string::npos )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Locker Pin should be numbers only" );
		return FALSE;
	}

	m_pData->m_sPersonalLock[EMPERSONAL_LOCK_EQUIP].bLock = cast_bool( bLockPutOn );
	m_pData->m_sPersonalLock[EMPERSONAL_LOCK_INVEN].bLock = cast_bool( bLockInven );
	m_pData->m_sPersonalLock[EMPERSONAL_LOCK_LOCKER].bLock = cast_bool( bLockLocker );

	StringCchCopy( m_pData->m_sPersonalLock[EMPERSONAL_LOCK_EQUIP].szPin, PERSONAL_LOCK_PIN_SIZE+1, strPinPutOn.c_str() );
	StringCchCopy( m_pData->m_sPersonalLock[EMPERSONAL_LOCK_INVEN].szPin, PERSONAL_LOCK_PIN_SIZE+1, strPinInven.c_str() );
	StringCchCopy( m_pData->m_sPersonalLock[EMPERSONAL_LOCK_LOCKER].szPin, PERSONAL_LOCK_PIN_SIZE+1, strPinLocker.c_str() );

	return TRUE;
}

