#include "stdafx.h"
#include "./GMTool.h"
#include "./CharEditPageCollection.h"
#include "./CharEditTab.h"
#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Client/G-Logic/GLCharData.h"
#include "../Lib_Client/G-Logic/GLItemCollection.h"
#include "../Lib_Helper/HLibDataConvert.h"
#include "./DlgActivityList.h"
#include "./DlgActivityEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCharEditPageActivity dialog

IMPLEMENT_DYNAMIC(CCharEditPageCollection, CPropertyPage)

	CCharEditPageCollection::CCharEditPageCollection(LOGFONT logfont, SCHARDATA2* pData)
	: CPropertyPage(CCharEditPageCollection::IDD)
	, m_pFont ( NULL )
	, m_pData( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	m_pData = pData;
}

CCharEditPageCollection::~CCharEditPageCollection()
{
	SAFE_DELETE ( m_pFont );
}

void CCharEditPageCollection::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHAREDIT_COLLECTION_PROG_LIST, m_ListProg);
	DDX_Control(pDX, IDC_CHAREDIT_COLLECTION_DONE_LIST, m_ListDone);
}


BEGIN_MESSAGE_MAP(CCharEditPageCollection, CPropertyPage)

	ON_BN_CLICKED(IDC_CHAREDIT_ACTIVITY_BUTTON_PROG_EDIT, OnBnClickedChareditCollectionButtonProgEdit)
	ON_BN_CLICKED(IDC_CHAREDIT_ACTIVITY_BUTTON_PROG_COMPLETE, OnBnClickedChareditCollectionButtonProgComplete)
	ON_BN_CLICKED(IDC_CHAREDIT_ACTIVITY_BUTTON_PROG_DELETE, OnBnClickedChareditCollectionButtonProgDelete)
	ON_BN_CLICKED(IDC_CHAREDIT_ACTIVITY_BUTTON_PROG_CLEAR, OnBnClickedChareditCollectionButtonProgClear)
	ON_BN_CLICKED(IDC_CHAREDIT_ACTIVITY_BUTTON_DONE_DELETE, OnBnClickedChareditCollectionButtonDoneDelete)
	ON_BN_CLICKED(IDC_CHAREDIT_ACTIVITY_BUTTON_DONE_CLEAR, OnBnClickedChareditCollectionButtonDoneClear)
END_MESSAGE_MAP()


// CCharEditPageActivity message handlers
BOOL CCharEditPageCollection::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
    m_pSheetTab->ChangeDialogFont(this, m_pFont, CDF_TOPLEFT);
    m_bDlgInit = TRUE;

    RECT rectCtrl;
    m_ListProg.SetExtendedStyle(m_ListProg.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
    m_ListProg.GetClientRect(&rectCtrl);
    m_ListProg.InsertColumn(0, "ID", LVCFMT_LEFT, (10 * (rectCtrl.right - rectCtrl.left)) / 100);
    m_ListProg.InsertColumn(1, "Title", LVCFMT_LEFT, (30 * (rectCtrl.right - rectCtrl.left)) / 100);

    m_ListDone.SetExtendedStyle(m_ListDone.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
    m_ListDone.GetClientRect(&rectCtrl);
    m_ListDone.InsertColumn(0, "ID", LVCFMT_LEFT, (10 * (rectCtrl.right - rectCtrl.left)) / 100);
    m_ListDone.InsertColumn(1, "Title", LVCFMT_LEFT, (40 * (rectCtrl.right - rectCtrl.left)) / 100);

    UpdateProgList();
    UpdateDoneList();

	return TRUE;  
}

void CCharEditPageCollection::UpdateProgList()
{
    m_ListProg.DeleteAllItems();

    if (!m_pData) 
	{
        return;
    }

    m_ListProg.SetRedraw(FALSE);

    SITEMCOLLECTION_CHAR_DATA_MAP& mapItemCollection = m_pData->m_mapItemCollectionProg;
    SITEMCOLLECTION_CHAR_DATA_MAP_ITER iter = mapItemCollection.begin();

    if (mapItemCollection.empty()) {
    }

    for (int i = 0; iter != mapItemCollection.end(); ++iter, ++i)
    {
        const SITEMCOLLECTION_CHAR_DATA& sItemCollection = (*iter).second;
        std::string strTitle = "Unknown Item Collection";

        SITEMCOLLECTION_FILE_DATA* pCollection_data = GLItemCollection::GetInstance().GetItemCollection(sItemCollection.dwItemCollectionID);
        if (pCollection_data)
        {
            strTitle = pCollection_data->strItemCollectionTitle.c_str();
        }
        m_ListProg.InsertItem(i, _HLIB::cstring_dword(sItemCollection.dwItemCollectionID).GetString());
        m_ListProg.SetItemText(i, 1, strTitle.c_str());
        m_ListProg.SetItemData(i, sItemCollection.dwItemCollectionID);
    }

    m_ListProg.SetRedraw(TRUE);
}

void CCharEditPageCollection::UpdateDoneList()
{
	m_ListDone.DeleteAllItems();

	if ( !m_pData ){
		return;
	}

	m_ListDone.SetRedraw( FALSE );

	SITEMCOLLECTION_CHAR_DATA_MAP& mapItemCollection = m_pData->m_mapItemCollectionDone;
	SITEMCOLLECTION_CHAR_DATA_MAP_ITER iter = mapItemCollection.begin();

	for ( int i=0 ; iter != mapItemCollection.end(); ++iter, ++i )
	{
		const SITEMCOLLECTION_CHAR_DATA& sItemCollection = (*iter).second;
		std::string strTitle = "Unknown Item Collection";
		std::string strBadge = "";

		SITEMCOLLECTION_FILE_DATA* pItemCollectionData = GLItemCollection::GetInstance().GetItemCollection( sItemCollection.dwItemCollectionID );
		if ( pItemCollectionData )
		{
			strTitle = pItemCollectionData->strItemCollectionTitle.c_str();
		}

		m_ListDone.InsertItem( i, _HLIB::cstring_dword( sItemCollection.dwItemCollectionID ).GetString() );
		m_ListDone.SetItemText( i, 1, strTitle.c_str() );
		m_ListDone.SetItemData( i, sItemCollection.dwItemCollectionID );
	}

	m_ListDone.SetRedraw( TRUE );
}

void CCharEditPageCollection::OnBnClickedChareditCollectionButtonProgEdit()
{
	if ( !m_pData )	return;

	int nSelect = m_ListProg.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED );
	if( nSelect == -1 ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Nothing selected!" );
		return;
	}

	DWORD dwID = (DWORD) m_ListProg.GetItemData ( nSelect );

	SITEMCOLLECTION_CHAR_DATA_MAP& mapCollection = m_pData->m_mapItemCollectionProg;
	SITEMCOLLECTION_CHAR_DATA_MAP_ITER iter = mapCollection.find(dwID);
	if ( iter != mapCollection.end() )
	{
		SITEMCOLLECTION_CHAR_DATA &sData = (*iter).second;
		/*CDlgActivityEdit dlg( this, &sData );
		if ( dlg.DoModal() == IDOK )
		{
		UpdateProgList();

		for( int nItem=0; nItem<m_ListProg.GetItemCount(); nItem++){
		DWORD dwID = m_ListProg.GetItemData( nItem );
		if( dwID == sData.dwItemCollectionID ){
		m_ListProg.EnsureVisible( nItem, TRUE );
		m_ListProg.SetItemState( nItem, LVIS_SELECTED, LVIS_SELECTED );
		GotoDlgCtrl(GetDlgItem(m_ListProg.GetDlgCtrlID())); 
		}
		}
		}*/
	}
}

void CCharEditPageCollection::OnBnClickedChareditCollectionButtonProgComplete()
{
	if ( !m_pData )	return;

	int nItemCount = m_ListProg.GetItemCount();

	// Iterate through all items and check if they are selected
	for (int i = 0; i < nItemCount; ++i)
	{
		if (m_ListProg.GetItemState(i, LVIS_SELECTED) & LVIS_SELECTED)
		{
			DWORD dwID = (DWORD)m_ListProg.GetItemData(i);

			SITEMCOLLECTION_CHAR_DATA_MAP& mapCollection = m_pData->m_mapItemCollectionProg;
			SITEMCOLLECTION_CHAR_DATA_MAP_ITER iter = mapCollection.find(dwID);
			if (iter != mapCollection.end())
			{
				SITEMCOLLECTION_CHAR_DATA sitemcollection_data = (*iter).second;

				for (int j = 0; j < ITEMCOLLECTION_MAX_ID; ++j)
				{
					sitemcollection_data.dwItemCollectionProgressNow[j] = sitemcollection_data.dwItemCollectionProgressMax[j];
				}

				m_pData->m_mapItemCollectionDone.insert(std::make_pair(sitemcollection_data.dwItemCollectionID, sitemcollection_data));
				mapCollection.erase(iter);
			}
		}
	}

	UpdateProgList();
	UpdateDoneList();
}

void CCharEditPageCollection::OnBnClickedChareditCollectionButtonProgDelete()
{
	if ( !m_pData )	return;

	int nSelect = m_ListProg.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED );
	if( nSelect == -1 ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Nothing selected!" );
		return;
	}

	DWORD dwID = (DWORD) m_ListProg.GetItemData ( nSelect );

	SITEMCOLLECTION_CHAR_DATA_MAP& mapCollection = m_pData->m_mapItemCollectionProg;
	SITEMCOLLECTION_CHAR_DATA_MAP_ITER iter = mapCollection.find(dwID);
	if ( iter != mapCollection.end() ){
		mapCollection.erase( iter );
	}

	UpdateProgList();
}

void CCharEditPageCollection::OnBnClickedChareditCollectionButtonProgClear()
{
	if ( !m_pData )return;

	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Delete All Prog Collection?" ) == IDYES ){
		m_pData->m_mapItemCollectionProg.clear();
		UpdateProgList();
	}
}

void CCharEditPageCollection::OnBnClickedChareditCollectionButtonDoneDelete()
{
	if ( !m_pData )	return;

	int nSelect = m_ListDone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED );
	if( nSelect == -1 ){
		CDebugSet::MsgBox( GetSafeHwnd(), "Nothing selected!" );
		return;
	}

	DWORD dwID = (DWORD) m_ListDone.GetItemData ( nSelect );

	SITEMCOLLECTION_CHAR_DATA_MAP& mapCollection = m_pData->m_mapItemCollectionDone;
	SITEMCOLLECTION_CHAR_DATA_MAP_ITER iter = mapCollection.find(dwID);
	if ( iter != mapCollection.end() ){
		mapCollection.erase( iter );
	}

	UpdateDoneList();
}

void CCharEditPageCollection::OnBnClickedChareditCollectionButtonDoneClear()
{
	if ( !m_pData )return;

	if ( CDebugSet::MsgBoxYesNo( GetSafeHwnd(), "Delete All Done Collection?" ) == IDYES ){
		m_pData->m_mapItemCollectionDone.clear();
		UpdateDoneList();
	}
}
