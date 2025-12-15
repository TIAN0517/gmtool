
#include "stdafx.h"
#include "./GMToolGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace GMTOOL_GLOBAL
{
	std::string	strBasic[GMTOOL_BASIC_SIZE] =
	{
		_T("No"),
		_T("Yes"),
	};

	std::string	strMainPageSettingsType[MAINPAGE_SETTINGS_TYPE_SIZE] =
	{
		_T("Tool Settings"),
		_T("Item Presets"),
		_T("Skill Presets"),
	};

	std::string	strUserPageSearchType[USERPAGE_SEARCH_TYPE_SIZE] =
	{
		_T("Search UserName"),
		_T("Search UserNumber"),
		_T("Search UserEmail"),
		_T("Search UserFullName"),
		_T("Search GM-Admin"),
		_T("Search Online"),
		_T("Search PCID HWID"),
		_T("Search PCID MAC"),
		_T("Search Restricted"),		/* user flag restricted, Juver, 2020/04/20 */
	};

	std::string	strUserStatus[GMTOOL_USER_STATUS_SIZE] =
	{
		_T("Offline"),
		_T("Online"),
	};

	std::string	strUserLoginType[GMTOOL_USER_LOGINTYPE_SIZE] =
	{
		_T("Logout"),
		_T("Login"),
	};

	std::string	strCharPageSearchType[CHARPAGE_SEARCH_TYPE_SIZE] =
	{
		_T("Search ChaName"),
		_T("Search ChaNumber"),
		_T("Search UserNumber"),
		_T("Search Online"),
	};



	std::string	strMapDataSearchType[EMMAPDATA_SEARCH_SIZE] =
	{
		_T("Search Name"),
		_T("Search MID"),
		_T("Search SID"),
	};

	std::string	strItemDataSearchType[EMITEMDATA_SEARCH_SIZE] =
	{
		_T("Search Name"),
		_T("Search MID"),
		_T("Search SID"),
		_T("Search Type"),
	};

	std::string	strCrowDataSearchType[EMCROWDATA_SEARCH_SIZE] =
	{
		_T("Search Name"),
		_T("Search MID"),
		_T("Search SID"),
	};

	std::string	strSkillDataSearchType[EMSKILLDATA_SEARCH_SIZE] =
	{
		_T("Search Name"),
		_T("Search MID"),
		_T("Search SID"),
		_T("Search Class"),
		_T("Search Pet"),
	};

	std::string	strQuestDataSearchType[EMQUESTDATA_SEARCH_SIZE] =
	{
		_T("Search Title"),
		_T("Search FileName"),
		_T("Search ID"),
	};

	std::string	strShopItemSearch[EMSHOPITEM_SEARCH_SIZE] =
	{
		_T("Search ItemName"),
		_T("Search ProductNum"),
		_T("Search Category"),
		_T("Search MID"),
		_T("Search SID"),
	};

	std::string	strSearchLimit[EMSEARCH_LIMIT_SIZE] =
	{
		_T("No Limit"),
		_T("TOP 10"),
		_T("TOP 50"),
		_T("TOP 100"),
		_T("TOP 500"),
		_T("TOP 999"),
	};

	std::string	strPetPageSearchType[EMPETPAGE_SEARCH_SIZE] =
	{
		_T("Search PetName"),
		_T("Search PetNum"),
		_T("Search PetChaNum(Owner)"),
		_T("Search Card MID"),
		_T("Search Card SID"),
		_T("Search Pet Type"),
	};

	std::string	strVehiclePageSearchType[EMVEHICLEPAGE_SEARCH_SIZE] =
	{
		_T("Search VehicleName"),
		_T("Search VehicleNum"),
		_T("Search VehicleChaNum(Owner)"),
		_T("Search Card MID"),
		_T("Search Card SID"),
		_T("Search Vehicle Type"),
	};

	std::string	strShopItemSearch2[EMSHOPITEM2_SEARCH_SIZE] =
	{
		_T("Search ItemName"),
		_T("Search ProductNum"),
		_T("Search Category"),
		_T("Search MID"),
		_T("Search SID"),
		_T("Search Stock"),
		_T("Search Price"),
		_T("Search Discount"),
		_T("Search Currency"),
	};

	/*equipment lock, Juver, 2018/01/15 */
	std::string	strEquipmentLockPageSearchType[EMEQUIPMENT_LOCK_PAGE_SEARCH_TYPE_SIZE] =
	{
		_T("Search ChaNum"),
		_T("Search EPin"),
	};

	std::string	strItemShopCurrencyType[SHOPPAGE_ITEMCURRENCY_TYPE] =
	{
		_T("E-Points"),
		_T("P-Points"),
	};

	std::string	strItemShopCategoryType[SHOPPAGE_ITEMCATEGORY_SIZE] =
	{
		_T("All"),
		_T("Male Costume"),
		_T("Female Costume"),
		_T("All Costume"),
		_T("Weapon Costume"),
		_T("Accessory Costume"),
		_T("Wing Costume"),
		_T("Box"),
		_T("Enhancement"),
		_T("Power Up"),
		_T("Pet"),
		_T("Vehicle"),
		_T("Card"),
	};
};

