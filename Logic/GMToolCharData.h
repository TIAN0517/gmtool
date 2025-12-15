/*!
 * \file GMToolCharData.h
 *
 * \author Juver
 * \date 2021/02/13
 *
 * 
 */

#ifndef GMTOOLCHARDATA_H_INCLUDED__
#define GMTOOLCHARDATA_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../Lib_Client/G-Logic/GLAwardTitle.h"

struct SCHARDATA2;

/* award title, Juver, 2021/02/13 */
struct SAWARD_TITLE_DATA_EX
{
	SAWARD_TITLE_DATA	sTitle;
	BOOL				bEnabled;
	__time64_t			tDate;
	BOOL				bAdd;

	SAWARD_TITLE_DATA_EX();
	~SAWARD_TITLE_DATA_EX();	

	SAWARD_TITLE_DATA_EX& operator= ( const SAWARD_TITLE_DATA_EX &cData );
};

typedef std::map<DWORD, SAWARD_TITLE_DATA_EX>		MAP_AWARD_TITLE_DATA_EX;
typedef MAP_AWARD_TITLE_DATA_EX::iterator			MAP_AWARD_TITLE_DATA_EX_ITER;


struct SGMToolCharData
{
	SCHARDATA2* pCharData2;

	/* award title, Juver, 2021/02/13 */
	MAP_AWARD_TITLE_DATA_EX	mapAwardTitle;

	SGMToolCharData();
	~SGMToolCharData();
};



#endif // GMTOOLCHARDATA_H_INCLUDED__
