// DlgShopItemEdit.cpp : implementation file
//

#include "stdafx.h"
#include "./GMTool.h"
#include "./DlgShopItemEdit.h"

#include "./Logic/GMToolData.h"
#include "../Lib_Helper/EtcFunction.h"
#include "../Lib_Client/G-Logic/GLItemMan.h"
#include "./DlgItem.h"
#include "./Logic/GMToolGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDlgShopItemEdit dialog

IMPLEMENT_DYNAMIC(CDlgShopItemEdit, CDialog)

CDlgShopItemEdit::CDlgShopItemEdit(CWnd* pParent /*=NULL*/, SGMTOOL_SHOP_ITEM* pDATA /*= NULL*/)
	: CDialog(CDlgShopItemEdit::IDD, pParent)
	, m_pData( NULL )
{
	m_pData = pDATA;
}

CDlgShopItemEdit::~CDlgShopItemEdit()
{
}

void CDlgShopItemEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShopItemEdit, CDialog)
	ON_BN_CLICKED(IDC_SHOPITEM_BUTTON_EDIT_ITEM, OnBnClickedShopitemButtonEditItem)
	ON_BN_CLICKED(IDC_SHOPITEM_BUTTON_USE_DEFAULT, OnBnClickedShopitemButtonUseDefault)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_SHOPITEM_EDIT_ITEM_MID, OnEnChangeShopitemEditItemMid)
	ON_EN_CHANGE(IDC_SHOPITEM_EDIT_ITEM_SID, OnEnChangeShopitemEditItemSid)
END_MESSAGE_MAP()


// CDlgShopItemEdit message handlers
BOOL CDlgShopItemEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*
	std::string	strShopCurrencySize[SHOPPAGE_ITEMCURRENCY_TYPE];
	for( int i=0; i<SHOPPAGE_ITEMCURRENCY_TYPE; ++i )
	{
		CString strText;
		strText.Format( "(%d)%s", i, GMTOOL_GLOBAL::strItemShopCurrencyType[i].c_str());
		strShopCurrencySize[i] = strText.GetString();
	}

	SetWin_Combo_Init( this, IDC_SHOP_ITEMEDIT_COMBO_CURRENCYTYPE, strShopCurrencySize, SHOPPAGE_ITEMCURRENCY_TYPE );

	std::string strShopCategorySize[SHOPPAGE_ITEMCATEGORY_SIZE];
	for( int i=0; i<SHOPPAGE_ITEMCATEGORY_SIZE; ++i )
	{
		CString strText;
		strText.Format("(%d)%s", i, GMTOOL_GLOBAL::strItemShopCategoryType[i].c_str());
		strShopCategorySize[i] = strText.GetString();
	}

	SetWin_Combo_Init( this, IDC_SHOP_ITEMEDIT_COMBO_CATEGORYTYPE, strShopCategorySize, SHOPPAGE_ITEMCATEGORY_SIZE );
	*/

	SetWin_Combo_Init( this, IDC_SHOP_ITEMEDIT_COMBO_CURRENCYTYPE, GMTOOL_GLOBAL::strItemShopCurrencyType, SHOPPAGE_ITEMCURRENCY_TYPE );
	SetWin_Combo_Init( this, IDC_SHOP_ITEMEDIT_COMBO_CATEGORYTYPE, GMTOOL_GLOBAL::strItemShopCategoryType, SHOPPAGE_ITEMCATEGORY_SIZE );

	DataShow();

	return TRUE;
}

void CDlgShopItemEdit::DataShow()
{
	if ( !m_pData )	return;

	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_PRODUCTNUM, m_pData->dwProductNum );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_MID, m_pData->wItemMain );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_SID, m_pData->wItemSub );
	SetWin_Text( this, IDC_SHOPITEM_EDIT_ITEM_NAME, m_pData->szItemName );

	SetWin_Combo_Sel( this, IDC_SHOP_ITEMEDIT_COMBO_CURRENCYTYPE, GMTOOL_GLOBAL::strItemShopCurrencyType[m_pData->wItemCurrency].c_str() );
	SetWin_Combo_Sel( this, IDC_SHOP_ITEMEDIT_COMBO_CATEGORYTYPE, GMTOOL_GLOBAL::strItemShopCategoryType[m_pData->wItemSection].c_str() );

	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_STOCK, m_pData->dwItemStock );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_MONEY, m_pData->wItemPrice );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_DISCOUNT, m_pData->wItemDiscount );
	
	/*
	SetWin_Text( this, IDC_SHOPITEM_EDIT_ITEM_DURATION, m_pData->szDuration );
	SetWin_Text( this, IDC_SHOPITEM_EDIT_ITEM_IMAGE, m_pData->szItemImage );
	SetWin_Text( this, IDC_SHOPITEM_EDIT_ITEM_COMMENT, m_pData->szItemComment );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_LIST, m_pData->wItemList );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_CATEGORY, m_pData->dwCategory );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_STOCK, m_pData->dwItemStock );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_MONEY, m_pData->dwItemMoney );
	*/
}

BOOL CDlgShopItemEdit::DataSave()
{
	if ( !m_pData )	return FALSE;

	WORD wMID = GetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_MID );
	WORD wSID = GetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_SID );
	SITEM* pItem = GLItemMan::GetInstance().GetItem( wMID, wSID );
	if ( !pItem )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "Invalid Item( %d~%d )", wMID, wSID );
		return FALSE;
	}

	std::string strItemName = GetWin_Text( this, IDC_SHOPITEM_EDIT_ITEM_NAME );
	if ( strItemName.size() <= 0 )
	{
		CDebugSet::MsgBox( GetSafeHwnd(), "ItemName Cannot be empty!" );
		return FALSE;
	}

	m_pData->wItemMain = wMID;
	m_pData->wItemSub = wSID;
	m_pData->dwItemStock = GetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_STOCK );
	m_pData->wItemPrice = GetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_MONEY );

	EMSHOP_ITEM_CURRENCY_TYPE emCurrencyType = static_cast<EMSHOP_ITEM_CURRENCY_TYPE> ( GetWin_Combo_Sel( this, IDC_SHOP_ITEMEDIT_COMBO_CURRENCYTYPE ) );
	m_pData->wItemCurrency = (DWORD) GetCurrencyType ( emCurrencyType );

	EMSHOP_ITEM_CATEGORY_TYPE emCategoryType = static_cast<EMSHOP_ITEM_CATEGORY_TYPE> ( GetWin_Combo_Sel( this, IDC_SHOP_ITEMEDIT_COMBO_CATEGORYTYPE ) );
	m_pData->wItemSection = (DWORD) GetCategoryType ( emCategoryType );

	m_pData->wItemDiscount = GetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_DISCOUNT );

	return TRUE;
}

void CDlgShopItemEdit::OnBnClickedShopitemButtonEditItem()
{
	CDlgItem dlg( this );
	if ( dlg.DoModal() != IDOK ){
		return;
	}

	SNATIVEID sidITEM = dlg.m_SELECTED;
	SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sidITEM );
	if ( !pITEM ) {
		CDebugSet::MsgBox( GetSafeHwnd(), "Invalid Item! ( %d %d )", 
			sidITEM.wMainID,
			sidITEM.wSubID );
		return;
	}

	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_MID, sidITEM.wMainID );
	SetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_SID, sidITEM.wSubID );
}

void CDlgShopItemEdit::OnBnClickedShopitemButtonUseDefault()
{
	WORD wMID = GetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_MID );
	WORD wSID = GetWin_Num_int( this, IDC_SHOPITEM_EDIT_ITEM_SID );
	SITEM* pItem = GLItemMan::GetInstance().GetItem( wMID, wSID );
	if ( pItem )
	{
		SetWin_Text( this, IDC_SHOPITEM_EDIT_ITEM_NAME, pItem->GetName() );
	}	
}

void CDlgShopItemEdit::OnBnClickedOk()
{
	if ( DataSave() ){
		CDialog::OnOK();
	}
}

void CDlgShopItemEdit::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CDlgShopItemEdit::OnEnChangeShopitemEditItemMid()
{
	GMTOOL_GLOBAL::DataCheckItem( this, 
		IDC_SHOPITEM_EDIT_ITEM_MID,
		IDC_SHOPITEM_EDIT_ITEM_SID,
		IDC_SHOPITEM_EDIT_ITEMNAME );
}

void CDlgShopItemEdit::OnEnChangeShopitemEditItemSid()
{
	GMTOOL_GLOBAL::DataCheckItem( this, 
		IDC_SHOPITEM_EDIT_ITEM_MID,
		IDC_SHOPITEM_EDIT_ITEM_SID,
		IDC_SHOPITEM_EDIT_ITEMNAME );
}
