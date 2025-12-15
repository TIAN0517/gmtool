#include "stdafx.h"
#include "./GMToolOdbcBase.h"
#include "./GMToolOdbcConn.h"
#include "./GMToolLogs.h"

#include "../../Lib_Client/G-Logic/GLCharDefine.h"
#include "../../Lib_Client/G-Logic/GLCharData.h"
#include "../../Lib_Helper/HLibDataConvert.h"
#include "../../Lib_Helper/HLibTimeFunctions.h"

#include "./GMToolLogs.h"
#include "./GMToolGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/* award title, Juver, 2021/02/12 */
int	CGMToolOdbcBase::ChaAwardTitleGet( DWORD dwChaNum, MAP_AWARD_TITLE_DATA_EX& mapTitle )
{
	//validity check
	if ( dwChaNum == 0	)	return DB_ERROR;

	//reset to defaults
	mapTitle.clear();

	//get data from db
	CGMToolOdbcConn* pDatabase = m_pGameDB;
	if ( !pDatabase )	return DB_ERROR;

	ODBC_STMT* pConn = pDatabase->GetConnection();
	if (!pConn)			return DB_ERROR;

	SQLRETURN sReturn = 0;

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "SELECT idx, Title, Type, Enabled, Date From ChaAwardTitle WHERE ChaNum=%d ", dwChaNum );

	GMTOOL_LOGS::LogSql( "%s", szTemp );

	sReturn = ::SQLExecDirect(pConn->hStmt, (SQLCHAR*)szTemp, SQL_NTS);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO)) 
	{	
		GMTOOL_LOGS::LogSqlError( "%s", GetErrorString(pConn->hStmt) );
		pDatabase->FreeConnection(pConn);

		return DB_ERROR;
	}

	SQLINTEGER nTitleID = 0, cbTitleID = SQL_NTS;
	SQLCHAR    szTitle[AWARD_TITLE_LENGTH+1] = {0}; SQLINTEGER cbTitle = SQL_NTS;
	SQLINTEGER nTitleType = 0, cbTitleType = SQL_NTS;
	SQLINTEGER nTitleEnabled = 0, cbTitleEnabled = SQL_NTS;
	TIMESTAMP_STRUCT sTitleDate; SQLINTEGER cbTitleDate = SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(pConn->hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			GMTOOL_LOGS::LogSqlError( "%s", GetErrorString(pConn->hStmt) );
			pDatabase->FreeConnection(pConn);

			return DB_ERROR;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(pConn->hStmt,  1, SQL_C_LONG,	&nTitleID,				0, &cbTitleID);
			::SQLGetData(pConn->hStmt,  2, SQL_C_CHAR,  szTitle, AWARD_TITLE_LENGTH, &cbTitle);
			::SQLGetData(pConn->hStmt,  3, SQL_C_LONG,	&nTitleType,			0, &cbTitleType);
			::SQLGetData(pConn->hStmt,  4, SQL_C_LONG,	&nTitleEnabled,			0, &cbTitleEnabled);
			::SQLGetData(pConn->hStmt,  5, SQL_C_TYPE_TIMESTAMP, &sTitleDate,   0, &cbTitleDate);

			SAWARD_TITLE_DATA_EX sTitleEx;
			sTitleEx.sTitle.dwID = (DWORD)nTitleID;

			if (cbTitle != 0 && cbTitle != -1)
				::StringCchCopy(sTitleEx.sTitle.szTitle, AWARD_TITLE_LENGTH+1, (const TCHAR*) szTitle);

			sTitleEx.sTitle.emType = (EMAWARD_TITLE_TYPE)nTitleType;

			sTitleEx.bEnabled = (BOOL)nTitleEnabled;

			if ( !_HLIB::timestamp_correction( sTitleDate ) ){
				GMTOOL_LOGS::LogError( "Variable sTitleDate value corrected" );
			}

			CTime cTemp(sTitleDate.year, sTitleDate.month, sTitleDate.day, 
				sTitleDate.hour, sTitleDate.minute, sTitleDate.second);
			sTitleEx.tDate = cTemp.GetTime();

			mapTitle.insert ( std::make_pair( sTitleEx.sTitle.dwID, sTitleEx ) );
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}	  

	pDatabase->FreeConnection(pConn);

	return DB_OK;
}

/* award title, Juver, 2021/02/14 */
int	CGMToolOdbcBase::ChaAwardTitleSave( DWORD dwChaNum, MAP_AWARD_TITLE_DATA_EX& mapTitle )
{
	//validity check
	if ( dwChaNum == 0	)	return DB_ERROR;

	CGMToolOdbcConn* pDatabase = m_pGameDB;
	if ( !pDatabase )		return DB_ERROR;

	MAP_AWARD_TITLE_DATA_EX_ITER it_b = mapTitle.begin();
	MAP_AWARD_TITLE_DATA_EX_ITER it_e = mapTitle.end();

	for ( ; it_b!= it_e; ++it_b )
	{
		SAWARD_TITLE_DATA_EX&	sData = (*it_b).second;

		if ( sData.bAdd )
		{
			TCHAR szTemp[1024] = {0};
			_snprintf( szTemp, 1024, 
				"INSERT INTO ChaAwardTitle ( ChaNum, Title, Type, Enabled ) Values ( %u, '%s', %u, %u )"
				, dwChaNum
				, sData.sTitle.szTitle
				, sData.sTitle.emType
				, sData.bEnabled );

			int nReturn = pDatabase->ExecuteSQL(szTemp);
			if ( nReturn != DB_OK )
			{
				return nReturn;
			}
		}
		else
		{
			TCHAR szTemp[1024] = {0};
			_snprintf( szTemp, 1024, "Update ChaAwardTitle Set Title='%s', Type=%u, Enabled=%u WHERE ChaNum=%d AND idx=%d ", 
				sData.sTitle.szTitle, sData.sTitle.emType, sData.bEnabled, dwChaNum, sData.sTitle.dwID );

			int nReturn = pDatabase->ExecuteSQL(szTemp);
			if ( nReturn != DB_OK )
			{
				return nReturn;
			}
		}
	}

	return DB_OK;
}