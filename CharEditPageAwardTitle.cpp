// CharEditPageAwardTitle.cpp : implementation file
//

#include "stdafx.h"
#include "GMTool.h"
#include "CharEditPageAwardTitle.h"
#include "afxdialogex.h"

#include "./CharEditTab.h"

#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Helper/HLibDataConvert.h"
#include "../Lib_Client/G-Logic/GLCharData.h"
#include "./Logic/GMToolCharData.h"

#include "./DlgAwardTitleEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCharEditPageAwardTitle dialog

IMPLEMENT_DYNAMIC(CCharEditPageAwardTitle, CPropertyPage)

CCharEditPageAwardTitle::CCharEditPageAwardTitle(LOGFONT logfont, SGMToolCharData* pData)
	: CPropertyPage(CCharEditPageAwardTitle::IDD)
	, m_pFont ( NULL )
	, m_pData( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	m_pData = pData;
}

CCharEditPageAwardTitle::~CCharEditPageAwardTitle()
{
	SAFE_DELETE ( m_pFont );
}

void CCharEditPageAwardTitle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAREDIT_AWARD_TITLE_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CCharEditPageAwardTitle, CPropertyPage)
	ON_BN_CLICKED(IDC_CHAREDIT_AWARD_TITLE_BUTTON_ADD, &CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonAdd)
	ON_BN_CLICKED(IDC_CHAREDIT_AWARD_TITLE_BUTTON_EDIT, &CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonEdit)
	ON_BN_CLICKED(IDC_CHAREDIT_AWARD_TITLE_BUTTON_DISABLE, &CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonDisable)
	ON_BN_CLICKED(IDC_CHAREDIT_AWARD_TITLE_BUTTON_ENABLE, &CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonEnable)
	ON_BN_CLICKED(IDC_CHAREDIT_AWARD_TITLE_BUTTON_DISABLE_ALL, &CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonDisableAll)
END_MESSAGE_MAP()


// CCharEditPageAwardTitle message handlers
BOOL CCharEditPageAwardTitle::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_pSheetTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	m_bDlgInit = TRUE;


	RECT rectCtrl;
	m_List.SetExtendedStyle ( m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_List.GetClientRect ( &rectCtrl );
	m_List.InsertColumn( 0, "", LVCFMT_LEFT, ( 1* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 1, "ID", LVCFMT_LEFT, ( 10* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 2, "Title", LVCFMT_LEFT, ( 50* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 3, "Type", LVCFMT_LEFT, ( 10* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 4, "Enabled", LVCFMT_LEFT, ( 10* ( rectCtrl.right - rectCtrl.left ) ) / 100 );
	m_List.InsertColumn( 5, "Date", LVCFMT_LEFT, ( 20* ( rectCtrl.right - rectCtrl.left ) ) / 100 );

	SetWin_Text( this, IDC_CHAREDIT_AWARD_TITLE_EDIT_TOTAL, "" );

	ShowData();

	return TRUE;  
}


void CCharEditPageAwardTitle::ShowData()
{
	m_List.DeleteAllItems();

	if ( !m_pData )	return;

	m_List.SetRedraw( FALSE );


	MAP_AWARD_TITLE_DATA_EX_ITER it_b = m_pData->mapAwardTitle.begin();
	MAP_AWARD_TITLE_DATA_EX_ITER it_e = m_pData->mapAwardTitle.end();

	for( int i=0; it_b != it_e; ++it_b, ++i )
	{
		const SAWARD_TITLE_DATA_EX& sData = (*it_b).second;

		m_List.InsertItem( i, "" );
		m_List.SetItemText( i, 1, _HLIB::cstringformat( "%02d", sData.bAdd? -1 :  sData.sTitle.dwID ).GetString() );
		m_List.SetItemText( i, 2, _HLIB::cstringformat( "%s", sData.sTitle.szTitle ).GetString() );
		m_List.SetItemText( i, 3, _HLIB::cstringformat( "%d", sData.sTitle.emType ).GetString() );
		m_List.SetItemText( i, 4, _HLIB::cstringformat( "%d", sData.bEnabled ).GetString() );
		m_List.SetItemText( i, 5, _HLIB::cstring_timet24( sData.tDate ).GetString() );
		m_List.SetItemData ( i, sData.sTitle.dwID );
	}

	m_List.SetRedraw( TRUE );

	CString strTotal;
	strTotal.Format( "Total Titles:%u", m_pData->mapAwardTitle.size() );
	SetWin_Text( this, IDC_CHAREDIT_AWARD_TITLE_EDIT_TOTAL, strTotal.GetString() );
}

void CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonAdd()
{
	if ( !m_pData )			return;

	//find temporary id
	//for add mode, final id will be different once saved to database
	DWORD dwID = m_pData->pCharData2->m_dwCharID; //charid as base id
	BOOL bFind = FALSE;
	while( !bFind )
	{
		MAP_AWARD_TITLE_DATA_EX_ITER it = m_pData->mapAwardTitle.find( dwID );
		if ( it == m_pData->mapAwardTitle.end() )
		{
			bFind = TRUE;
			break;
		}

		dwID ++;
	}

	SAWARD_TITLE_DATA_EX sData;
	sData.sTitle.dwID = dwID;
	sData.bAdd = TRUE;
	sData.bEnabled = TRUE;

	CDlgAwardTitleEdit dlg( this, &sData );
	if ( dlg.DoModal() == IDOK )
	{
		m_pData->mapAwardTitle.insert( std::make_pair( sData.sTitle.dwID, sData ) );
		ShowData();
	}
}

void CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonEdit()
{
	if ( !m_pData )			return;

	int nSelect = m_List.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 )		return;

	DWORD dwID = (DWORD) m_List.GetItemData ( nSelect );

	MAP_AWARD_TITLE_DATA_EX_ITER it = m_pData->mapAwardTitle.find(dwID);
	if ( it == m_pData->mapAwardTitle.end() )	return;

	SAWARD_TITLE_DATA_EX& sData = (*it).second;
	
	CDlgAwardTitleEdit dlg( this, &sData );
	if ( dlg.DoModal() == IDOK )
	{
		ShowData();

		for( int nItem=0; nItem<m_List.GetItemCount(); nItem++)
		{
			if( dwID == m_List.GetItemData( nItem ) )
			{
				m_List.EnsureVisible( nItem, TRUE );
				m_List.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED );
				GotoDlgCtrl(GetDlgItem(m_List.GetDlgCtrlID())); 
			}
		}
	}
}

void CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonDisable()
{
	if ( !m_pData )			return;

	int nSelect = m_List.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 )		return;

	DWORD dwID = (DWORD) m_List.GetItemData ( nSelect );

	MAP_AWARD_TITLE_DATA_EX_ITER it = m_pData->mapAwardTitle.find(dwID);
	if ( it == m_pData->mapAwardTitle.end() )	return;

	SAWARD_TITLE_DATA_EX& sData = (*it).second;
	sData.bEnabled = FALSE;

	ShowData();

	for( int nItem=0; nItem<m_List.GetItemCount(); nItem++)
	{
		if( dwID == m_List.GetItemData( nItem ) )
		{
			m_List.EnsureVisible( nItem, TRUE );
			m_List.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED );
			GotoDlgCtrl(GetDlgItem(m_List.GetDlgCtrlID())); 
		}
	}
}

void CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonEnable()
{
	if ( !m_pData )			return;

	int nSelect = m_List.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 )		return;

	DWORD dwID = (DWORD) m_List.GetItemData ( nSelect );

	MAP_AWARD_TITLE_DATA_EX_ITER it = m_pData->mapAwardTitle.find(dwID);
	if ( it == m_pData->mapAwardTitle.end() )	return;

	SAWARD_TITLE_DATA_EX& sData = (*it).second;
	sData.bEnabled = TRUE;

	ShowData();

	for( int nItem=0; nItem<m_List.GetItemCount(); nItem++)
	{
		if( dwID == m_List.GetItemData( nItem ) )
		{
			m_List.EnsureVisible( nItem, TRUE );
			m_List.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED );
			GotoDlgCtrl(GetDlgItem(m_List.GetDlgCtrlID())); 
		}
	}
}

void CCharEditPageAwardTitle::OnBnClickedChareditAwardTitleButtonDisableAll()
{
	if ( !m_pData )			return;

	MAP_AWARD_TITLE_DATA_EX_ITER it_b = m_pData->mapAwardTitle.begin();
	MAP_AWARD_TITLE_DATA_EX_ITER it_e = m_pData->mapAwardTitle.end();

	for( int i=0; it_b != it_e; ++it_b, ++i )
	{
		SAWARD_TITLE_DATA_EX& sData = (*it_b).second;
		sData.bEnabled = FALSE;
	}

	ShowData();
}
