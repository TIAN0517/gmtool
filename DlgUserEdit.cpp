// DlgUserEdit.cpp : implementation file
//

#include "stdafx.h"
#include "./GMTool.h"
#include "./DlgUserEdit.h"


#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Helper/HLibTimeFunctions.h"
#include "../Lib_Helper/HLibDataConvert.h"
#include "./Logic/GMToolData.h"
#include "./Logic/GMToolGlobal.h"
#include "./Logic/GMToolOdbcBase.h"
#include "./DlgDatetime.h"
#include "./PageUser.h"

#include "./Logic/GMToolConfig.h"
#include "../Lib_Client/G-Logic/UserTypeDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDlgUserEdit dialog

IMPLEMENT_DYNAMIC(CDlgUserEdit, CDialog)

CDlgUserEdit::CDlgUserEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserEdit::IDD, pParent)
	, m_pParentWnd(NULL)
	, m_nDialogID(-1)
	, m_dwID(0)
	, m_strNAME("")
	, m_pData(NULL)
{

}

CDlgUserEdit::CDlgUserEdit(int nDialogID, DWORD dwID, std::string strNAME, CWnd* pParent /*= NULL*/)
	: CDialog(CDlgUserEdit::IDD, pParent)
	, m_pParentWnd(pParent)
	, m_nDialogID(nDialogID)
	, m_dwID(dwID)
	, m_strNAME(strNAME)
	, m_pData(NULL)
{

}

CDlgUserEdit::~CDlgUserEdit()
{
	SAFE_DELETE( m_pData );
}

void CDlgUserEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUserEdit, CDialog)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_MD5, OnBnClickedUsereditButtonMd5)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_MD52, OnBnClickedUsereditButtonMd52)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_USERBLOCK_SET, OnBnClickedUsereditButtonUserblockSet)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_USERBLOCK_RESET, OnBnClickedUsereditButtonUserblockReset)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_CHATBLOCK_SET, OnBnClickedUsereditButtonChatblockSet)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_CHATBLOCK_RESET, OnBnClickedUsereditButtonChatblockReset)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_PREMIUMDATE_SET, OnBnClickedUsereditButtonPremiumdateSet)
	ON_BN_CLICKED(IDC_USEREDIT_BUTTON_PREMIUMDATE_RESET, OnBnClickedUsereditButtonPremiumdateReset)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
	
END_MESSAGE_MAP()


// CDlgUserEdit message handlers
BOOL CDlgUserEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strWindowText;
	strWindowText.Format( "Edit User:(%d) %s", m_dwID, m_strNAME.c_str() );
	SetWindowText( strWindowText.GetString() );

	SetWin_Combo_Init( this, IDC_USEREDIT_COMBO_USERTYPE, COMMENT::USER_TYPE, NSUSER_TYPE::USER_TYPE_INDEX_SIZE );
	SetWin_Combo_Init( this, IDC_USEREDIT_COMBO_LOGINSTATE, GMTOOL_GLOBAL::strUserStatus, GMTOOL_USER_STATUS_SIZE );
	SetWin_Combo_Init( this, IDC_USEREDIT_COMBO_AVAILABLE, GMTOOL_GLOBAL::strBasic, GMTOOL_BASIC_SIZE );
	SetWin_Combo_Init( this, IDC_USEREDIT_COMBO_USERBLOCK, GMTOOL_GLOBAL::strBasic, GMTOOL_BASIC_SIZE );

	m_pData = new SGMTOOL_DATA_USER;
	int nReturn = CGMToolOdbcBase::GetInstance()->UserDataGet( m_dwID, m_pData );
	if ( nReturn != DB_OK ){
		SAFE_DELETE( m_pData );
		CDebugSet::MsgBox( GetSafeHwnd(), "Unable to Get UserData! UserNumber:%d", m_dwID );
	}

	DataDefault();
	DataShow();
	
	return TRUE;  
}

void CDlgUserEdit::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	if ( m_pParentWnd ){
		((CPageUser*)m_pParentWnd)->DialogDeleteID(m_nDialogID);
	}

	delete this;
}

void CDlgUserEdit::OnOK()
{
	if(UpdateData(true)){
		DestroyWindow();
	}
}

void CDlgUserEdit::OnCancel()
{
	DestroyWindow();
}

void CDlgUserEdit::DataDefault()
{
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_NUM, 0 );
	SetWin_Text( this, IDC_USEREDIT_EDIT_NAME, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PASS, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PASS2, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_EMAIL, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_FULLNAME, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_USERBLOCK, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_CHATBLOCK, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PREMIUMDATE, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_CREATEDATE, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_LOGINDATE, "" );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_SERVERNUMBER, 0 );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_SERVERGROUP, 0 );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_CHAREMAIN, 0 );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_USERPOINT, 0 );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_USERTYPE, 0 );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_LOGINSTATE, 0 );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_AVAILABLE, 0 );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_USERBLOCK, 0);

	/* user flag verified, Juver, 2020/02/24 */
	SetWin_Check( this, IDC_USEREDIT_CHECK_USER_FLAG_VERIFIED, 0 );

	//PCID
	SetWin_Text( this, IDC_USEREDIT_EDIT_PCID_HWID, "" );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PCID_MAC, "" );

	/* user flag restricted, Juver, 2020/04/20 */
	SetWin_Check( this, IDC_USEREDIT_CHECK_USER_FLAG_RESTRICTED, 0 );

	bool bEnable = GMTOOL_CONFIG::m_wLoginType > NSUSER_TYPE::USER_TYPE_GM4;

	if ( !bEnable )
	{
		SetPasswordMask(IDC_USEREDIT_EDIT_PASS);
		SetPasswordMask(IDC_USEREDIT_EDIT_PASS2);
		SetPasswordMask(IDC_USEREDIT_EDIT_EMAIL);
	}

	GetDlgItem(IDC_USEREDIT_EDIT_NUM)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_NAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_PASS)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_PASS2)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_EMAIL)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_FULLNAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_USERBLOCK)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_CHATBLOCK)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_PREMIUMDATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_CREATEDATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_LOGINDATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_SERVERNUMBER)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_SERVERGROUP)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_CHAREMAIN)->EnableWindow(bEnable);
	//GetDlgItem(IDC_USEREDIT_EDIT_USERPOINT)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_COMBO_USERTYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_COMBO_LOGINSTATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_COMBO_AVAILABLE)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_COMBO_USERBLOCK)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_CHECK_USER_FLAG_VERIFIED)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_PCID_HWID)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_EDIT_PCID_MAC)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_CHECK_USER_FLAG_RESTRICTED)->EnableWindow(bEnable);

	GetDlgItem(IDC_USEREDIT_BUTTON_MD5)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_BUTTON_MD52)->EnableWindow(bEnable);

	GetDlgItem(IDC_USEREDIT_BUTTON_USERBLOCK_SET)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_BUTTON_CHATBLOCK_SET)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_BUTTON_PREMIUMDATE_SET)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_BUTTON_USERBLOCK_RESET)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_BUTTON_CHATBLOCK_RESET)->EnableWindow(bEnable);
	GetDlgItem(IDC_USEREDIT_BUTTON_PREMIUMDATE_RESET)->EnableWindow(bEnable);
}

void CDlgUserEdit::DataShow()
{
	if ( !m_pData ){
		return;
	}

	SetWin_Num_int( this, IDC_USEREDIT_EDIT_NUM, m_pData->dwUserNum );
	SetWin_Text( this, IDC_USEREDIT_EDIT_NAME, m_pData->szUserID );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PASS, m_pData->szUserPass );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PASS2, m_pData->szUserPass2 );
	SetWin_Text( this, IDC_USEREDIT_EDIT_EMAIL, m_pData->szUserEmail );
	SetWin_Text( this, IDC_USEREDIT_EDIT_FULLNAME, m_pData->szUserFullName );
	SetWin_Text( this, IDC_USEREDIT_EDIT_USERBLOCK, _HLIB::cstring_timet12( m_pData->tUserBlockDate ).GetString() );
	SetWin_Text( this, IDC_USEREDIT_EDIT_CHATBLOCK, _HLIB::cstring_timet12( m_pData->tChatBlockDate ).GetString() );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PREMIUMDATE, _HLIB::cstring_timet12( m_pData->tPremiumDate ).GetString() );
	SetWin_Text( this, IDC_USEREDIT_EDIT_CREATEDATE, _HLIB::cstring_timet12( m_pData->tCreateDate ).GetString() );
	SetWin_Text( this, IDC_USEREDIT_EDIT_LOGINDATE, _HLIB::cstring_timet12( m_pData->tLastLoginDate ).GetString() );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_SERVERNUMBER, m_pData->wServerNumber );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_SERVERGROUP, m_pData->wServerGroup );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_CHAREMAIN, m_pData->wChaRemain );
	SetWin_Num_int( this, IDC_USEREDIT_EDIT_USERPOINT, m_pData->dwUserPoint );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_USERTYPE, NSUSER_TYPE::UserTypeToUserTypeIndex( (NSUSER_TYPE::EMUSER_TYPE) m_pData->wUserType ) );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_LOGINSTATE, GMTOOL_GLOBAL::strUserStatus[m_pData->bUserLoginState].c_str() );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_AVAILABLE, GMTOOL_GLOBAL::strBasic[m_pData->bUserAvailable].c_str() );
	SetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_USERBLOCK, GMTOOL_GLOBAL::strBasic[m_pData->bUserBlock].c_str());

	/* user flag verified, Juver, 2020/02/25 */
	SetWin_Check( this, IDC_USEREDIT_CHECK_USER_FLAG_VERIFIED, m_pData->bUserFlagVerified );

	//PCID
	SetWin_Text( this, IDC_USEREDIT_EDIT_PCID_HWID, m_pData->szUserPCID_HWID );
	SetWin_Text( this, IDC_USEREDIT_EDIT_PCID_MAC, m_pData->szUserPCID_MAC );

	/* user flag restricted, Juver, 2020/04/20 */
	SetWin_Check( this, IDC_USEREDIT_CHECK_USER_FLAG_RESTRICTED, m_pData->bUserFlagRestricted );
}

BOOL CDlgUserEdit::DataSave()
{
	if ( !m_pData ){
		return FALSE;
	}

	BOOL bONLINE = FALSE;
	CGMToolOdbcBase::GetInstance()->UserOnlineCheck( m_pData->dwUserNum, bONLINE );

	if ( bONLINE ){
		if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "User: [%d]%s is Online! continue?", m_pData->dwUserNum, m_pData->szUserID ) != IDYES ){
			return FALSE;
		}
	}

	std::string strPass = GetWin_Text( this, IDC_USEREDIT_EDIT_PASS );
	std::string strPass2 = GetWin_Text( this, IDC_USEREDIT_EDIT_PASS2 );
	std::string strEmail = GetWin_Text( this, IDC_USEREDIT_EDIT_EMAIL );
	std::string strFullName = GetWin_Text( this, IDC_USEREDIT_EDIT_FULLNAME );
	int nCharRemain = GetWin_Num_int( this, IDC_USEREDIT_EDIT_CHAREMAIN );
	int nUserPoints = GetWin_Num_int( this, IDC_USEREDIT_EDIT_USERPOINT );
	BOOL bLoginState = GetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_LOGINSTATE );
	BOOL bAvailable = GetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_AVAILABLE );
	BOOL bUserBlock = GetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_USERBLOCK );

	NSUSER_TYPE::EMUSER_TYPE_INDEX emUserTypeIndex = static_cast<NSUSER_TYPE::EMUSER_TYPE_INDEX> ( GetWin_Combo_Sel( this, IDC_USEREDIT_COMBO_USERTYPE ) );

	/* user flag verified, Juver, 2020/02/25 */
	bool bUserFlagVerified = cast_bool( GetWin_Check( this, IDC_USEREDIT_CHECK_USER_FLAG_VERIFIED ) );

	//PCID
	std::string strUserPCID_HWID = GetWin_Text( this, IDC_USEREDIT_EDIT_PCID_HWID );
	std::string strUserPCID_MAC = GetWin_Text( this, IDC_USEREDIT_EDIT_PCID_MAC );

	/* user flag restricted, Juver, 2020/04/20 */
	bool bUserFlagRestricted = cast_bool( GetWin_Check( this, IDC_USEREDIT_CHECK_USER_FLAG_RESTRICTED ) );

	if ( strPass.size() < MIN_USER_PASS || strPass.size() > MAX_USER_PASS ){
		CDebugSet::MsgBox( GetSafeHwnd(), "UserPass can only have %d to %d characters", MIN_USER_PASS, MAX_USER_PASS );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PASS)); 
		return FALSE;
	}

	if ( strPass2.size() < MIN_USER_PASS || strPass2.size() > MAX_USER_PASS ){
		CDebugSet::MsgBox( GetSafeHwnd(), "UserPass2 can only have %d to %d characters", MIN_USER_PASS, MAX_USER_PASS );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PASS2)); 
		return FALSE;
	}

	if ( strEmail.size() > USR_EMAIL_LENGTH ){
		CDebugSet::MsgBox( GetSafeHwnd(), "UserEmail can only have 0 to %d characters", USR_EMAIL_LENGTH );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_EMAIL)); 
		return FALSE;
	}

	if ( strFullName.size() > USR_FULLNAME_LENGTH ){
		CDebugSet::MsgBox( GetSafeHwnd(), "FullName can only have 0 to %d characters", USR_FULLNAME_LENGTH );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_FULLNAME)); 
		return FALSE;
	}

	//PCID
	if ( strUserPCID_HWID.size() > PCID_LENGTH ){
		CDebugSet::MsgBox( GetSafeHwnd(), "PCID can only have 0 to %d characters", PCID_LENGTH );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PCID_HWID)); 
		return FALSE;
	}

	if ( strUserPCID_MAC.size() > PCID_LENGTH ){
		CDebugSet::MsgBox( GetSafeHwnd(), "PCID can only have 0 to %d characters", PCID_LENGTH );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PCID_MAC)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strPass.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "UserPass contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PASS)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strPass2.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "UserPass2 contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PASS2)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString2( strEmail.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "UserEmail contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_EMAIL)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString3( strFullName.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "FullName contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_FULLNAME)); 
		return FALSE;
	}

	//PCID
	if ( GMTOOL_GLOBAL::IsBadString( strUserPCID_HWID.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "PCID HWID contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PCID_HWID)); 
		return FALSE;
	}

	if ( GMTOOL_GLOBAL::IsBadString( strUserPCID_MAC.c_str() ) ){
		CDebugSet::MsgBox( GetSafeHwnd(), "PCID MAC contains invalid characters!" );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_PCID_MAC)); 
		return FALSE;
	}

	if ( nCharRemain < 0 || nCharRemain >= MAX_ONESERVERCHAR_NUM ){
		CDebugSet::MsgBox( GetSafeHwnd(), "ChaRemain can only have 0 to %d value", MAX_ONESERVERCHAR_NUM );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_CHAREMAIN)); 
		return FALSE;
	}

	if ( nUserPoints < 0 ){
		CDebugSet::MsgBox( GetSafeHwnd(), "User Points invalid" );
		GotoDlgCtrl(GetDlgItem(IDC_USEREDIT_EDIT_USERPOINT)); 
		return FALSE;
	}

	StringCchCopy( m_pData->szUserPass, USR_PASS_LENGTH, strPass.c_str() );
	StringCchCopy( m_pData->szUserPass2, USR_PASS_LENGTH, strPass2.c_str() );
	StringCchCopy( m_pData->szUserEmail, USR_EMAIL_LENGTH, strEmail.c_str() );
	StringCchCopy( m_pData->szUserFullName, USR_FULLNAME_LENGTH, strFullName.c_str() );
	m_pData->wUserType = (WORD)NSUSER_TYPE::UserTypeIndexToUserType( emUserTypeIndex );
	m_pData->wChaRemain = (WORD)nCharRemain;
	m_pData->dwUserPoint = (WORD)nUserPoints;
	m_pData->bUserLoginState = bLoginState;
	m_pData->bUserAvailable = bAvailable;
	m_pData->bUserBlock = bUserBlock;

	/* user flag verified, Juver, 2020/02/25 */
	m_pData->bUserFlagVerified = bUserFlagVerified;

	//PCID
	StringCchCopy( m_pData->szUserPCID_HWID, PCID_LENGTH, strUserPCID_HWID.c_str() );
	StringCchCopy( m_pData->szUserPCID_MAC, PCID_LENGTH, strUserPCID_MAC.c_str() );

	/* user flag restricted, Juver, 2020/04/20 */
	m_pData->bUserFlagRestricted = bUserFlagRestricted;

	int nReturn = CGMToolOdbcBase::GetInstance()->UserDataSave( m_pData );
	if ( nReturn != DB_OK ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Unable to Save UserData! UserNumber:%d", m_pData->dwUserNum );
		return FALSE;
	}

	return TRUE;
}

void CDlgUserEdit::OnBnClickedUsereditButtonMd5()
{
	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Do you want to convert UserPass to MD5?" ) == IDYES )
	{
		std::string strTEXT = GMTOOL_GLOBAL::GMToolStringConvertToMD5( GetWin_Text( this, IDC_USEREDIT_EDIT_PASS ).GetString(), MAX_USER_PASS );
		SetWin_Text( this, IDC_USEREDIT_EDIT_PASS, strTEXT.c_str() );
	}
}

void CDlgUserEdit::OnBnClickedUsereditButtonMd52()
{
	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Do you want to convert UserPass2 to MD5?" ) == IDYES )
	{
		std::string strTEXT = GMTOOL_GLOBAL::GMToolStringConvertToMD5( GetWin_Text( this, IDC_USEREDIT_EDIT_PASS2 ).GetString(), MAX_USER_PASS );
		SetWin_Text( this, IDC_USEREDIT_EDIT_PASS2, strTEXT.c_str() );
	}
}

void CDlgUserEdit::OnBnClickedUsereditButtonUserblockSet()
{
	if ( !m_pData ){
		return;
	}

	__time64_t ttime = m_pData->tUserBlockDate;
	if ( ttime < CTime::GetCurrentTime().GetTime() ){
		ttime = CTime::GetCurrentTime().GetTime();
	}

	CDlgDatetime dlg( this );
	dlg.DateSetMin( CTime::GetCurrentTime().GetTime() );
	dlg.DateTimeSet( ttime );
	if ( dlg.DoModal() == IDOK ){
		m_pData->tUserBlockDate = dlg.DateTimeGet();
		SetWin_Text( this, IDC_USEREDIT_EDIT_USERBLOCK, _HLIB::cstring_timet12( m_pData->tUserBlockDate ).GetString() );
	}
}

void CDlgUserEdit::OnBnClickedUsereditButtonUserblockReset()
{
	if ( !m_pData ){
		return;
	}

	m_pData->tUserBlockDate = CTime::GetCurrentTime().GetTime();
	SetWin_Text( this, IDC_USEREDIT_EDIT_USERBLOCK, _HLIB::cstring_timet12( m_pData->tUserBlockDate ).GetString() );
}

void CDlgUserEdit::OnBnClickedUsereditButtonChatblockSet()
{
	if ( !m_pData ){
		return;
	}

	__time64_t ttime = m_pData->tChatBlockDate;
	if ( ttime < CTime::GetCurrentTime().GetTime() ){
		ttime = CTime::GetCurrentTime().GetTime();
	}

	CDlgDatetime dlg( this );
	dlg.DateSetMin( CTime::GetCurrentTime().GetTime() );
	dlg.DateTimeSet( ttime );
	if ( dlg.DoModal() == IDOK ){
		m_pData->tChatBlockDate = dlg.DateTimeGet();
		SetWin_Text( this, IDC_USEREDIT_EDIT_CHATBLOCK, _HLIB::cstring_timet12( m_pData->tChatBlockDate ).GetString() );
	}
}

void CDlgUserEdit::OnBnClickedUsereditButtonChatblockReset()
{
	if ( !m_pData ){
		return;
	}

	CTime cTime( 1970, 2, 1, 0, 0, 0 );
	m_pData->tChatBlockDate = cTime.GetTime();
	SetWin_Text( this, IDC_USEREDIT_EDIT_CHATBLOCK, _HLIB::cstring_timet12( m_pData->tChatBlockDate ).GetString() );
}

void CDlgUserEdit::OnBnClickedUsereditButtonPremiumdateSet()
{
	if ( !m_pData ){
		return;
	}

	__time64_t ttime = m_pData->tPremiumDate;
	if ( ttime < CTime::GetCurrentTime().GetTime() ){
		ttime = CTime::GetCurrentTime().GetTime();
	}

	CDlgDatetime dlg( this );
	dlg.DateSetMin( CTime::GetCurrentTime().GetTime() );
	dlg.DateTimeSet( ttime );
	if ( dlg.DoModal() == IDOK ){
		m_pData->tPremiumDate = dlg.DateTimeGet();
		SetWin_Text( this, IDC_USEREDIT_EDIT_PREMIUMDATE, _HLIB::cstring_timet12( m_pData->tPremiumDate ).GetString() );
	}	
}

void CDlgUserEdit::OnBnClickedUsereditButtonPremiumdateReset()
{
	if ( !m_pData ){
		return;
	}

	CTime cTime( 1970, 2, 1, 0, 0, 0 );
	m_pData->tPremiumDate = cTime.GetTime();
	SetWin_Text( this, IDC_USEREDIT_EDIT_PREMIUMDATE, _HLIB::cstring_timet12( m_pData->tPremiumDate ).GetString() );
}

void CDlgUserEdit::OnBnClickedOk()
{
	if ( DataSave()){
		OnOK();
	}
}

void CDlgUserEdit::OnBnClickedCancel()
{
	OnCancel();
}

void CDlgUserEdit::OnBnClickedOk2()
{
	if ( DataSave()){
		CDebugSet::MsgBox( GetSafeHwnd(), "Save Done!" );
	}
}

void CDlgUserEdit::SetPasswordMask(int nID)
{
	CWnd* pWnd = GetDlgItem(nID);
	if (pWnd && pWnd->GetSafeHwnd()) 
	{
		pWnd->SendMessage(EM_SETPASSWORDCHAR, (WPARAM)'*', 0);
		pWnd->Invalidate();
	}
}