#include "stdafx.h"
#include "./GMToolOdbcBase.h"
#include "./GMToolOdbcConn.h"
#include "./GMToolLogs.h"

#include "../../Lib_Client/G-Logic/GLCharDefine.h"
#include "../../Lib_Client/G-Logic/GLCharData.h"
#include "./GMToolLogs.h"
#include "./GMToolGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CGMToolOdbcBase::PKComboCheck( SCHARDATA2* pCharData2 )
{
	if ( !pCharData2 ) return DB_ERROR;
	if ( pCharData2->GetUserID() == 0 )	return DB_ERROR;

	TCHAR szCheck[128] = {0};
	_snprintf( szCheck, 128, "{call PKComboCheck(%u,?)}", pCharData2->m_dwCharID );

	TCHAR szInsert[128] = {0};
	_snprintf( szInsert, 128, "{call PKComboMake(%d,%u,?)}", 0,  pCharData2->m_dwCharID );

	CGMToolOdbcConn* pDatabase = m_pGameDB;
	if ( !pDatabase )	return DB_ERROR;

	int nReturn = pDatabase->ExecuteSpInt(szCheck);
	if ( nReturn <= 0 ){
		pDatabase->ExecuteSpInt(szInsert);
	}

	return DB_OK;
}

int CGMToolOdbcBase::PKComboRead( SCHARDATA2* pCharData2 )
{    
	if ( !pCharData2 )	return DB_ERROR;
	if ( pCharData2->GetUserID() == 0 )	return DB_ERROR;

	CGMToolOdbcConn* pDatabase = m_pGameDB;
	if ( !pDatabase )	return DB_ERROR;

	ODBC_STMT* pConn = pDatabase->GetConnection();
	if (!pConn)			return DB_ERROR;

	SQLRETURN sReturn = 0;
	int nUserNum = 0;

	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, "SELECT PKCombo00, PKCombo01, PKCombo02, PKCombo03, PKCombo04, PKCombo05, PKCombo06, PKCombo07 FROM ChaPKCombo WHERE ChaNum=%u ", pCharData2->m_dwCharID );

	GMTOOL_LOGS::LogSql( "%s", szTemp );

	sReturn = ::SQLExecDirect(pConn->hStmt, (SQLCHAR*)szTemp, SQL_NTS );

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO)) 
	{
		GMTOOL_LOGS::LogSqlError( "%s", GetErrorString(pConn->hStmt) );
		pDatabase->FreeConnection(pConn);

		return DB_ERROR;
	}

	SQLINTEGER  nPKCombo00, cbPKCombo00 = SQL_NTS;
	SQLINTEGER  nPKCombo01, cbPKCombo01 = SQL_NTS;
	SQLINTEGER  nPKCombo02, cbPKCombo02 = SQL_NTS;
	SQLINTEGER  nPKCombo03, cbPKCombo03 = SQL_NTS;
	SQLINTEGER  nPKCombo04, cbPKCombo04 = SQL_NTS;
	SQLINTEGER  nPKCombo05, cbPKCombo05 = SQL_NTS;
	SQLINTEGER  nPKCombo06, cbPKCombo06 = SQL_NTS;
	SQLINTEGER  nPKCombo07, cbPKCombo07 = SQL_NTS;

	while(true)
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
			::SQLGetData(pConn->hStmt,1, SQL_C_LONG, &nPKCombo00, 0, &cbPKCombo00 );	
			::SQLGetData(pConn->hStmt,2, SQL_C_LONG, &nPKCombo01, 0, &cbPKCombo01 );	
			::SQLGetData(pConn->hStmt,3, SQL_C_LONG, &nPKCombo02, 0, &cbPKCombo02 );	
			::SQLGetData(pConn->hStmt,4, SQL_C_LONG, &nPKCombo03, 0, &cbPKCombo03 );	
			::SQLGetData(pConn->hStmt,5, SQL_C_LONG, &nPKCombo04, 0, &cbPKCombo04 );	
			::SQLGetData(pConn->hStmt,6, SQL_C_LONG, &nPKCombo05, 0, &cbPKCombo05 );	
			::SQLGetData(pConn->hStmt,7, SQL_C_LONG, &nPKCombo06, 0, &cbPKCombo06 );	
			::SQLGetData(pConn->hStmt,8, SQL_C_LONG, &nPKCombo07, 0, &cbPKCombo07 );	

			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_00] = (DWORD)nPKCombo00;
			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_01] = (DWORD)nPKCombo01;
			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_02] = (DWORD)nPKCombo02;
			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_03] = (DWORD)nPKCombo03;
			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_04] = (DWORD)nPKCombo04;
			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_05] = (DWORD)nPKCombo05;
			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_06] = (DWORD)nPKCombo06;
			pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_07] = (DWORD)nPKCombo07;
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

int CGMToolOdbcBase::PKComboWrite( SCHARDATA2* pCharData2 )
{
	if ( !pCharData2 )	return DB_ERROR;

	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, "Update ChaPKCombo Set PKCombo00=%u, PKCombo01=%u, PKCombo02=%u, PKCombo03=%u, PKCombo04=%u, PKCombo05=%u, PKCombo06=%u, PKCombo07=%u  WHERE ChaNum=%u ", 
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_00],
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_01],
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_02],
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_03],
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_04],
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_05],
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_06],
		pCharData2->m_sPKComboCount.dwCount[EMPKCOMBO_COUNT_07],
		pCharData2->m_dwCharID );

	CGMToolOdbcConn* pDatabase = m_pGameDB;
	if ( !pDatabase )	return DB_ERROR;

	return pDatabase->ExecuteSQL(szTemp);
}