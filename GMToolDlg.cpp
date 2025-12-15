
// GMToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "./GMTool.h"
#include "./GMToolDlg.h"

#include "../Lib_Engine/Core/NSRPath.h"
#include "../Lib_Engine/Core/NSRLog.h"
#include "../Lib_Engine/Core/NSRParam.h"
#include "../Lib_Engine/Core/NSROption.h"

#include "../Lib_Client/G-Logic/UserTypeDefine.h"

#include "../Lib_Engine/G-Logic/GLOGIC.h"
#include "../Lib_Engine/DxResponseMan.h"

#include "../Lib_Client/DxServerInstance.h"

#include "./Logic/GMToolConfig.h"
#include "./Logic/GMToolGlobal.h"
#include "./logic/GMToolPresetItem.h"
#include "./logic/GMToolPresetSkill.h"
#include "./Logic/GMToolLogs.h"
#include "./Logic/GMToolOdbcBase.h"

#include "./DlgConfig.h"
#include "./DlgPresetItem.h"
#include "./DlgPresetSkill.h"
#include "./SheetWithTab.h"

#include "../Lib_Helper/EtcFunction.h"

#include <boost/filesystem.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGMToolDlg dialog

CGMToolDlg::CGMToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGMToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGMToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGMToolDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_MAINPAGE_BUTTON_SETTING, OnBnClickedMainpageButtonSetting)
END_MESSAGE_MAP()


// CGMToolDlg message handlers

BOOL CGMToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(::AfxGetInstanceHandle(), szPath, MAX_PATH);
	
	RPATH::SetPath( szPath );
	RLOG::Init();

	RPARAM::Init ();

	CGMToolPresetItem::GetInstance().SetPath( RPATH::getAppPath() );
	CGMToolPresetItem::GetInstance().PresetLoad();

	CGMToolPresetSkill::GetInstance().SetPath( RPATH::getAppPath() );
	CGMToolPresetSkill::GetInstance().PresetLoad();

	DxResponseMan::GetInstance().OneTimeSceneInit ( RPATH::getAppPath(), this, ROPTION::strFontType, RPARAM::emLangSet, RPARAM::strGDIFont );
	GMTOOL::Create( RPATH::getAppPath() );

	GMTOOL_GLOBAL::gmtoolMapList.LoadMapsListFile( "mapslist.mst" );

	CString strWELCOME;
	strWELCOME.Format( "Welcome [%s]:(%d)%s", 
		COMMENT::USER_TYPE[ NSUSER_TYPE::UserTypeToUserTypeIndex((NSUSER_TYPE::EMUSER_TYPE)GMTOOL_CONFIG::m_wLoginType)].c_str(), 
		GMTOOL_CONFIG::m_dwLoginID, 
		GMTOOL_CONFIG::m_szLoginUser );
	SetWin_Text( this, IDC_EDIT_GM_INFO, strWELCOME.GetString() );

	SetWin_Combo_Init( this, IDC_MAINPAGE_COMBO_SETTING, GMTOOL_GLOBAL::strMainPageSettingsType, MAINPAGE_SETTINGS_TYPE_SIZE );


	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_GMTOOL_MAIN_STATIC );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );
	LOGFONT logfont = {0};

	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );

	m_pSheetTab = new CsheetWithTab ( SheetRect, logfont, this );
	m_pSheetTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pSheetTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_pSheetTab->InitPages();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGMToolDlg::PostNcDestroy()
{
	SAFE_DELETE ( m_pSheetTab );

	CGMToolOdbcBase::GetInstance()->DatabaseClose();
	CGMToolOdbcBase::GetInstance()->ReleaseInstance();

	DxResponseMan::GetInstance().FinalCleanup ();
	GMTOOL::CleanUp ();

	CDialog::PostNcDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGMToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGMToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGMToolDlg::OnBnClickedMainpageButtonSetting()
{
	NSUSER_TYPE::EMUSER_TYPE_INDEX emUserTypeIndex = NSUSER_TYPE::UserTypeToUserTypeIndex( (NSUSER_TYPE::EMUSER_TYPE)GMTOOL_CONFIG::m_wLoginType );
	std::string strUserType = COMMENT::USER_TYPE[emUserTypeIndex].c_str();

	if ( emUserTypeIndex != NSUSER_TYPE::USER_TYPE_INDEX_MASTER )
	{
		CDebugSet::MsgBoxAfx( "Only %s is allowed to open settings page!", strUserType.c_str() );
		return;
	}

	MAINPAGE_SETTINGS_TYPE emType = static_cast<MAINPAGE_SETTINGS_TYPE> ( GetWin_Combo_Sel( this, IDC_MAINPAGE_COMBO_SETTING ));
	switch ( emType )
	{
	case MAINPAGE_SETTINGS_TYPE_TOOL:
		{
			CDlgConfig dlg;
			if ( dlg.DoModal() == IDOK ){
				GMTOOL_CONFIG::SettingsSave();
				GMTOOL_LOGS::LogInfo( "Config Saved" );
			}
		}break;

	case MAINPAGE_SETTINGS_TYPE_ITEMPRESET:
		{
			CDlgPresetItem dlg;
			if ( dlg.DoModal() == IDOK ){
				CGMToolPresetItem::GetInstance().PresetSave();
				GMTOOL_LOGS::LogInfo( "Preset Item Saved" );
			}
		}break;

	case MAINPAGE_SETTINGS_TYPE_SKILLPRESET:
		{
			CDlgPresetSkill dlg;
			if ( dlg.DoModal() == IDOK ){
				CGMToolPresetSkill::GetInstance().PresetSave();
				GMTOOL_LOGS::LogInfo( "Preset Skill Saved" );
			}
		}break;
	};
}

void CGMToolDlg::OnClose()
{
	if( m_pSheetTab ){
		if ( !m_pSheetTab->IsDialogAllFree() ){
			CDebugSet::MsgBox( GetSafeHwnd(), "Close all dialog first!" );
			return;
		}
	}

	if( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Exit Tool?") != IDYES ){
		return;
	}
	
	CDialog::OnClose();
}