// DlgUserNew.cpp : implementation file
//

#include "stdafx.h"
#include "./GMTool.h"
#include "./DlgUserNew.h"


#include "../Lib_Helper/EtcFunction.h"
#include "./Logic/GMToolGlobal.h"
#include "./Logic/GMToolData.h"
#include "./Logic/GMToolOdbcBase.h"

#include "../Lib_Client/G-Logic/UserTypeDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDlgUserNew dialog

IMPLEMENT_DYNAMIC(CDlgUserNew, CDialog)

CDlgUserNew::CDlgUserNew(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserNew::IDD, pParent)
{

}

CDlgUserNew::~CDlgUserNew()
{
}

void CDlgUserNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUserNew, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_USERNEW_BUTTON_MD5_1, OnBnClickedUsernewButtonMd51)
	ON_BN_CLICKED(IDC_USERNEW_BUTTON_MD5_2, OnBnClickedUsernewButtonMd52)
	ON_BN_CLICKED(IDC_USERNEW_BUTTON_USERCHECK, OnBnClickedUsernewButtonUsercheck)
END_MESSAGE_MAP()


// CDlgUserNew message handlers
BOOL CDlgUserNew::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetWin_Combo_Init( this, IDC_USERNEW_COMBO_USERTYPE, COMMENT::USER_TYPE, NSUSER_TYPE::USER_TYPE_INDEX_SIZE );

	SetWin_Num_int( this, IDC_USERNEW_EDIT_CHAREMAIN, 2 );
	SetWin_Num_int( this, IDC_USERNEW_EDIT_USERPOINT, 0 );

	return TRUE;  
}

void CDlgUserNew::OnBnClickedOk()
{
	std::string strName = GetWin_Text( this, IDC_USERNEW_EDIT_USERNAME );
	std::string strPass = GetWin_Text( this, IDC_USERNEW_EDIT_USERPASS );
	std::string strPass2 = GetWin_Text( this, IDC_USERNEW_EDIT_USERPASS2 );
	std::string strEmail = GetWin_Text( this, IDC_USERNEW_EDIT_USEREMAIL );
	std::string strFullName = GetWin_Text( this, IDC_USERNEW_EDIT_USER_FULLNAME );
	int nCharRemain = GetWin_Num_int( this, IDC_USERNEW_EDIT_CHAREMAIN );
	int nUserPoints = GetWin_Num_int( this, IDC_USERNEW_EDIT_USERPOINT );
	NSUSER_TYPE::EMUSER_TYPE_INDEX emUserTypeIndex = static_cast<NSUSER_TYPE::EMUSER_TYPE_INDEX> ( GetWin_Combo_Sel( this, IDC_USERNEW_COMBO_USERTYPE ) );

	/* user flag verified, Juver, 2020/02/25 */
	bool bUserFlagVerified = cast_bool( GetWin_Check( this, IDC_USERNEW_CHECK_USER_FLAG_VERIFIED ) );

	/* user flag restricted, Juver, 2020/04/20 */
	bool bUserFlagRestricted = cast_bool( GetWin_Check( this, IDC_USERNEW_CHECK_USER_FLAG_RESTRICTED ) );

	if ( strName.size() < MIN_USER_ID || strName.size() > MAX_USER_ID ){
		CDebugSet::MsgBoxAfx( "UserName can only have %d to %d characters", MIN_USER_ID, MAX_USER_ID );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERNAME)); 
		return;
	}

	if ( strPass.size() < MIN_USER_PASS || strPass.size() > MAX_USER_PASS ){
		CDebugSet::MsgBoxAfx( "UserPass can only have %d to %d characters", MIN_USER_PASS, MAX_USER_PASS );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERPASS)); 
		return;
	}

	if ( strPass2.size() < MIN_USER_PASS || strPass2.size() > MAX_USER_PASS ){
		CDebugSet::MsgBoxAfx( "UserPass2 can only have %d to %d characters", MIN_USER_PASS, MAX_USER_PASS );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERPASS2)); 
		return;
	}

	if ( strEmail.size() > USR_EMAIL_LENGTH ){
		CDebugSet::MsgBoxAfx( "UserEmail can only have 0 to %d characters", USR_EMAIL_LENGTH );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USEREMAIL)); 
		return;
	}

	if ( strFullName.size() > USR_FULLNAME_LENGTH ){
		CDebugSet::MsgBoxAfx( "UserFullNamecan only have 0 to %d characters", USR_FULLNAME_LENGTH );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USER_FULLNAME)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strName.c_str() ) ){
		CDebugSet::MsgBoxAfx( "UserName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERNAME)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strPass.c_str() ) ){
		CDebugSet::MsgBoxAfx( "UserPass contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERPASS)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strPass2.c_str() ) ){
		CDebugSet::MsgBoxAfx( "UserPass2 contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERPASS2)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strEmail.c_str() ) ){
		CDebugSet::MsgBoxAfx( "UserEmail contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USEREMAIL)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString3( strEmail.c_str() ) ){
		CDebugSet::MsgBoxAfx( "FullName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USER_FULLNAME)); 
		return;
	}

	if ( nCharRemain <= 0 || nCharRemain >= MAX_ONESERVERCHAR_NUM ){
		CDebugSet::MsgBoxAfx( "ChaRemain can only have 1 to %d value", MAX_ONESERVERCHAR_NUM );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_CHAREMAIN)); 
		return;
	}

	if ( nUserPoints < 0 ){
		CDebugSet::MsgBoxAfx( "User Points invalid" );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERPOINT)); 
		return;
	}


	BOOL bExist = UseIDCheck( strName.c_str() );
	if ( bExist ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Name:'%s' Already used! Try Another Name!", strName.c_str() );
		return;
	}

	SGMTOOL_USER_NEW sDATA;
	StringCchCopy( sDATA.szUserID, USR_ID_LENGTH, strName.c_str() );
	StringCchCopy( sDATA.szUserPass, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( sDATA.szUserPass2, USR_PASS_LENGTH, strPass2.c_str() );
	StringCchCopy( sDATA.szUserEmail, USR_EMAIL_LENGTH, strEmail.c_str() );
	StringCchCopy( sDATA.szUserFullName, USR_FULLNAME_LENGTH, strFullName.c_str() );
	sDATA.wUserType = (WORD)NSUSER_TYPE::UserTypeIndexToUserType( emUserTypeIndex );
	sDATA.wChaRemain = (WORD)nCharRemain;
	sDATA.dwUserPoint = (WORD)nUserPoints;

	/* user flag verified, Juver, 2020/02/25 */
	sDATA.bUserFlagVerified = bUserFlagVerified;

	/* user flag restricted, Juver, 2020/04/20 */
	sDATA.bUserFlagRestricted = bUserFlagRestricted;

	int nReturn = CGMToolOdbcBase::GetInstance()->UserNew( &sDATA );
	if ( nReturn == DB_ERROR ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Create User Failed! Check Logs!" );
		return;
	}

	CDebugSet::MsgBox( GetSafeHwnd(), "User Created!" );

	CDialog::OnOK();
}


void CDlgUserNew::OnBnClickedUsernewButtonMd51()
{
	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Do you want to convert UserPass to MD5?" ) == IDYES )
	{
		std::string strTEXT = GMTOOL_GLOBAL::GMToolStringConvertToMD5( GetWin_Text( this, IDC_USERNEW_EDIT_USERPASS ).GetString(), MAX_USER_PASS );
		SetWin_Text( this, IDC_USERNEW_EDIT_USERPASS, strTEXT.c_str() );
	}
}

void CDlgUserNew::OnBnClickedUsernewButtonMd52()
{
	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Do you want to convert UserPass2 to MD5?" ) == IDYES )
	{
		std::string strTEXT = GMTOOL_GLOBAL::GMToolStringConvertToMD5( GetWin_Text( this, IDC_USERNEW_EDIT_USERPASS2 ).GetString(), MAX_USER_PASS );
		SetWin_Text( this, IDC_USERNEW_EDIT_USERPASS2, strTEXT.c_str() );
	}
}

void CDlgUserNew::OnBnClickedUsernewButtonUsercheck()
{
	std::string strName = GetWin_Text( this, IDC_USERNEW_EDIT_USERNAME );

	if ( strName.size() < MIN_USER_ID || strName.size() > MAX_USER_ID ){
		CDebugSet::MsgBoxAfx( "UserName can only have %d to %d characters", MIN_USER_ID, MAX_USER_ID );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERNAME)); 
		return;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strName.c_str() ) ){
		CDebugSet::MsgBoxAfx( "UserName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USERNEW_EDIT_USERNAME)); 
		return;
	}

	BOOL bExist = UseIDCheck( strName.c_str() );
	if ( bExist ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Name:%s Already used! Try Another Name!", strName.c_str() );
	}else{
		CDebugSet::MsgBox( GetSafeHwnd(), "Name:%s is Valid!", strName.c_str() );
	}
}

BOOL CDlgUserNew::UseIDCheck( std::string strName )
{
	BOOL bExist = FALSE;
	int nUserNum = 0;

	int nReturn = CGMToolOdbcBase::GetInstance()->UserIDCheck( strName.c_str(), bExist, nUserNum );
	if ( nReturn == DB_ERROR ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Unable to check database for existing name! Report this bug!" );
	}

	return bExist;
}