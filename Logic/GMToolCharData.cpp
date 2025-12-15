#include "stdafx.h"
#include "./GMToolCharData.h"


#include "../../Lib_Client/G-Logic/GLCharData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


SAWARD_TITLE_DATA_EX::SAWARD_TITLE_DATA_EX()
	: sTitle(SAWARD_TITLE_DATA())
	, bEnabled(FALSE)
	, tDate(0)
	, bAdd(FALSE)
{
};

SAWARD_TITLE_DATA_EX::~SAWARD_TITLE_DATA_EX()
{

}

SAWARD_TITLE_DATA_EX& SAWARD_TITLE_DATA_EX::operator= ( const SAWARD_TITLE_DATA_EX &cData )
{
	if( this == &cData )	return *this;

	sTitle		= cData.sTitle;
	bEnabled	= cData.bEnabled;
	tDate		= cData.tDate;
	bAdd		= cData.bAdd;

	return *this;
}



SGMToolCharData::SGMToolCharData()
	: pCharData2(NULL)
{
	pCharData2 = new SCHARDATA2;
	mapAwardTitle.clear();
}

SGMToolCharData::~SGMToolCharData()
{
	mapAwardTitle.clear();
	SAFE_DELETE( pCharData2 ); 
}