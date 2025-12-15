#include "stdafx.h"
#include "./GMToolOdbcBase.h"
#include "./GMToolOdbcConn.h"
#include "./GMToolLogs.h"

#include "../../Lib_Client/G-Logic/GLCharDefine.h"
#include "../../Lib_Client/G-Logic/GLCharData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CGMToolOdbcBase::CombatRecordCheck( SCHARDATA2* pCharData2 )
{
	if ( !pCharData2 ) return DB_ERROR;
	if ( pCharData2->GetUserID() == 0 )	return DB_ERROR;

	TCHAR szCheck[128] = {0};
	_snprintf( szCheck, 128, "{call sp_CombatRecordCheck(%u,?)}", pCharData2->m_dwCharID );

	TCHAR szInsert[128] = {0};
	_snprintf( szInsert, 128, "{call sp_CombatRecordMake(%d,%u,%u,%u,?)}", 0, 
		pCharData2->m_dwCharID, 
		pCharData2->m_dwPKScorePREV, 
		pCharData2->m_dwPKDeathPREV );

	CGMToolOdbcConn* pDatabase = m_pGameDB;
	if ( !pDatabase )	return DB_ERROR;

	int nReturn = pDatabase->ExecuteSpInt(szCheck);
	if ( nReturn <= 0 ){
		pDatabase->ExecuteSpInt(szInsert);
	}

	return DB_OK;
}

int CGMToolOdbcBase::CombatRecordRead( SCHARDATA2* pCharData2 )
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
	_snprintf( szTemp, 512, 
		"SELECT "
		"PVPKills, PVPDeaths, PVPResu, "
		"TyrannyKills, TyrannyDeaths, TyrannyResu, "
		"ClubWarKills, ClubWarDeaths, ClubWarResu, "
		"CaptureTheFlagKills, CaptureTheFlagDeaths, CaptureTheFlagResu, "
		"SchoolWarsKills, SchoolWarsDeaths, SchoolWarsResu, "
		"ClubDeathMatchKills, ClubDeathMatchDeaths, ClubDeathMatchResu, "
		"PKMapKills, PKMapDeaths, PKMapResu, "
		"PVEKills, PVEDeaths, PVEMoneyGain "
		"FROM ChaCombatRecord WHERE ChaNum=%u ", pCharData2->m_dwCharID );

	GMTOOL_LOGS::LogSql( "%s", szTemp );

	sReturn = ::SQLExecDirect(pConn->hStmt, (SQLCHAR*)szTemp, SQL_NTS );

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO)) 
	{
		GMTOOL_LOGS::LogSqlError( "%s", GetErrorString(pConn->hStmt) );
		pDatabase->FreeConnection(pConn);

		return DB_ERROR;
	}

	SQLINTEGER  nPVPKills, cbPVPKills = SQL_NTS;
	SQLINTEGER  nPVPDeaths, cbPVPDeaths = SQL_NTS;
	SQLINTEGER  nPVPResu, cbPVPResu = SQL_NTS;

	SQLINTEGER  nTyrannyKills, cbTyrannyKills = SQL_NTS;
	SQLINTEGER  nTyrannyDeaths, cbTyrannyDeaths = SQL_NTS;
	SQLINTEGER  nTyrannyResu, cbTyrannyResu = SQL_NTS;

	SQLINTEGER  nClubWarKills, cbClubWarKills = SQL_NTS;
	SQLINTEGER  nClubWarDeaths, cbClubWarDeaths = SQL_NTS;
	SQLINTEGER  nClubWarResu, cbClubWarResu = SQL_NTS;

	SQLINTEGER  nCaptureTheFlagKills, cbCaptureTheFlagKills = SQL_NTS;
	SQLINTEGER  nCaptureTheFlagDeaths, cbCaptureTheFlagDeaths = SQL_NTS;
	SQLINTEGER  nCaptureTheFlagResu, cbCaptureTheFlagResu = SQL_NTS;

	SQLINTEGER  nSchoolWarsKills, cbSchoolWarsKills = SQL_NTS;
	SQLINTEGER  nSchoolWarsDeaths, cbSchoolWarsDeaths = SQL_NTS;
	SQLINTEGER  nSchoolWarsResu, cbSchoolWarsResu = SQL_NTS;

	SQLINTEGER  nClubDeathMatchKills, cbClubDeathMatchKills = SQL_NTS;
	SQLINTEGER  nClubDeathMatchDeaths, cbClubDeathMatchDeaths = SQL_NTS;
	SQLINTEGER  nClubDeathMatchResu, cbClubDeathMatchResu = SQL_NTS;

	SQLINTEGER  nPKMapKills, cbPKMapKills = SQL_NTS;
	SQLINTEGER  nPKMapDeaths, cbPKMapDeaths = SQL_NTS;
	SQLINTEGER  nPKMapResu, cbPKMapResu = SQL_NTS;

	SQLINTEGER  nPVEKills, cbPVEKills = SQL_NTS;
	SQLINTEGER  nPVEDeaths, cbPVEDeaths = SQL_NTS;

	LONGLONG   llPVEMoneyGain = 0;
	SQLINTEGER cbPVEMoneyGain=SQL_NTS; 

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
			::SQLGetData(pConn->hStmt,1, SQL_C_LONG, &nPVPKills, 0, &cbPVPKills );	
			::SQLGetData(pConn->hStmt,2, SQL_C_LONG, &nPVPDeaths, 0, &cbPVPDeaths );	
			::SQLGetData(pConn->hStmt,3, SQL_C_LONG, &nPVPResu, 0, &cbPVPResu );	

			::SQLGetData(pConn->hStmt,4, SQL_C_LONG, &nTyrannyKills, 0, &cbTyrannyKills );	
			::SQLGetData(pConn->hStmt,5, SQL_C_LONG, &nTyrannyDeaths, 0, &cbTyrannyDeaths );	
			::SQLGetData(pConn->hStmt,6, SQL_C_LONG, &nTyrannyResu, 0, &cbTyrannyResu );	

			::SQLGetData(pConn->hStmt,7, SQL_C_LONG, &nClubWarKills, 0, &cbClubWarKills );	
			::SQLGetData(pConn->hStmt,8, SQL_C_LONG, &nClubWarDeaths, 0, &cbClubWarDeaths );	
			::SQLGetData(pConn->hStmt,9, SQL_C_LONG, &nClubWarResu, 0, &cbClubWarResu );	

			::SQLGetData(pConn->hStmt,10, SQL_C_LONG, &nCaptureTheFlagKills, 0, &cbCaptureTheFlagKills );	
			::SQLGetData(pConn->hStmt,11, SQL_C_LONG, &nCaptureTheFlagDeaths, 0, &cbCaptureTheFlagDeaths );	
			::SQLGetData(pConn->hStmt,12, SQL_C_LONG, &nCaptureTheFlagResu, 0, &cbCaptureTheFlagResu );	

			::SQLGetData(pConn->hStmt,13, SQL_C_LONG, &nSchoolWarsKills, 0, &cbSchoolWarsKills );	
			::SQLGetData(pConn->hStmt,14, SQL_C_LONG, &nSchoolWarsDeaths, 0, &cbSchoolWarsDeaths );	
			::SQLGetData(pConn->hStmt,15, SQL_C_LONG, &nSchoolWarsResu, 0, &cbSchoolWarsResu );	

			::SQLGetData(pConn->hStmt,16, SQL_C_LONG, &nClubDeathMatchKills, 0, &cbClubDeathMatchKills );	
			::SQLGetData(pConn->hStmt,17, SQL_C_LONG, &nClubDeathMatchDeaths, 0, &cbClubDeathMatchDeaths );	
			::SQLGetData(pConn->hStmt,18, SQL_C_LONG, &nClubDeathMatchResu, 0, &cbClubDeathMatchResu );	

			::SQLGetData(pConn->hStmt,19, SQL_C_LONG, &nPKMapKills, 0, &cbPKMapKills );	
			::SQLGetData(pConn->hStmt,20, SQL_C_LONG, &nPKMapDeaths, 0, &cbPKMapDeaths );	
			::SQLGetData(pConn->hStmt,21, SQL_C_LONG, &nPKMapResu, 0, &cbPKMapResu );	

			::SQLGetData(pConn->hStmt,22, SQL_C_LONG, &nPVEKills, 0, &cbPVEKills );	
			::SQLGetData(pConn->hStmt,23, SQL_C_LONG, &nPVEDeaths, 0, &cbPVEDeaths );	
			::SQLGetData(pConn->hStmt,24, SQL_C_SBIGINT, &llPVEMoneyGain, 0, &cbPVEMoneyGain);

			pCharData2->m_sCombatRecord.dwPVPKills = static_cast<DWORD>(nPVPKills);
			pCharData2->m_sCombatRecord.dwPVPDeaths = static_cast<DWORD>(nPVPDeaths);
			pCharData2->m_sCombatRecord.dwPVPResu = static_cast<DWORD>(nPVPResu);

			pCharData2->m_sCombatRecord.dwTyrannyKills = static_cast<DWORD>(nTyrannyKills);
			pCharData2->m_sCombatRecord.dwTyrannyDeaths = static_cast<DWORD>(nTyrannyDeaths);
			pCharData2->m_sCombatRecord.dwTyrannyResu = static_cast<DWORD>(nTyrannyResu);

			pCharData2->m_sCombatRecord.dwClubWarKills = static_cast<DWORD>(nClubWarKills);
			pCharData2->m_sCombatRecord.dwClubWarDeaths = static_cast<DWORD>(nClubWarDeaths);
			pCharData2->m_sCombatRecord.dwClubWarResu = static_cast<DWORD>(nClubWarResu);

			pCharData2->m_sCombatRecord.dwCaptureTheFlagKills = static_cast<DWORD>(nCaptureTheFlagKills);
			pCharData2->m_sCombatRecord.dwCaptureTheFlagDeaths = static_cast<DWORD>(nCaptureTheFlagDeaths);
			pCharData2->m_sCombatRecord.dwCaptureTheFlagResu = static_cast<DWORD>(nCaptureTheFlagResu);

			pCharData2->m_sCombatRecord.dwSchoolWarsKills = static_cast<DWORD>(nSchoolWarsKills);
			pCharData2->m_sCombatRecord.dwSchoolWarsDeaths = static_cast<DWORD>(nSchoolWarsDeaths);
			pCharData2->m_sCombatRecord.dwSchoolWarsResu = static_cast<DWORD>(nSchoolWarsResu);

			pCharData2->m_sCombatRecord.dwClubDeathMatchKills = static_cast<DWORD>(nClubDeathMatchKills);
			pCharData2->m_sCombatRecord.dwClubDeathMatchDeaths = static_cast<DWORD>(nClubDeathMatchDeaths);
			pCharData2->m_sCombatRecord.dwClubDeathMatchResu = static_cast<DWORD>(nClubDeathMatchResu);

			pCharData2->m_sCombatRecord.dwPKMapKills = static_cast<DWORD>(nPKMapKills);
			pCharData2->m_sCombatRecord.dwPKMapDeaths = static_cast<DWORD>(nPKMapDeaths);
			pCharData2->m_sCombatRecord.dwPKMapResu = static_cast<DWORD>(nPKMapResu);

			pCharData2->m_sCombatRecord.dwPVEKills = static_cast<DWORD>(nPVEKills);
			pCharData2->m_sCombatRecord.dwPVEDeaths = static_cast<DWORD>(nPVEDeaths);
			pCharData2->m_sCombatRecord.llPVEMoneyGain = static_cast<LONGLONG>(llPVEMoneyGain);
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

int CGMToolOdbcBase::CombatRecordWrite( SCHARDATA2* pCharData2 )
{
	if ( !pCharData2 )	return DB_ERROR;

	TCHAR szTemp[512] = {0};
	_snprintf( szTemp, 512, 
		"Update ChaCombatRecord Set "
		"PVPKills=%u, PVPDeaths=%u, PVPResu=%u, "
		"TyrannyKills=%u, TyrannyDeaths=%u, TyrannyResu=%u, "
		"ClubWarKills=%u, ClubWarDeaths=%u, ClubWarResu=%u, "
		"CaptureTheFlagKills=%u, CaptureTheFlagDeaths=%u, CaptureTheFlagResu=%u, "
		"SchoolWarsKills=%u, SchoolWarsDeaths=%u, SchoolWarsResu=%u, "
		"ClubDeathMatchKills=%u, ClubDeathMatchDeaths=%u, ClubDeathMatchResu=%u, "
		"PKMapKills=%u, PKMapDeaths=%u, PKMapResu=%u, "
		"PVEKills=%u, PVEDeaths=%u, PVEMoneyGain=%I64d "   
		"WHERE ChaNum=%u ", 
		pCharData2->m_sCombatRecord.dwPVPKills, pCharData2->m_sCombatRecord.dwPVPDeaths, pCharData2->m_sCombatRecord.dwPVPResu,
		pCharData2->m_sCombatRecord.dwTyrannyKills, pCharData2->m_sCombatRecord.dwTyrannyDeaths, pCharData2->m_sCombatRecord.dwTyrannyResu,
		pCharData2->m_sCombatRecord.dwClubWarKills, pCharData2->m_sCombatRecord.dwClubWarDeaths, pCharData2->m_sCombatRecord.dwClubWarResu,
		pCharData2->m_sCombatRecord.dwCaptureTheFlagKills, pCharData2->m_sCombatRecord.dwCaptureTheFlagDeaths, pCharData2->m_sCombatRecord.dwCaptureTheFlagResu,
		pCharData2->m_sCombatRecord.dwSchoolWarsKills, pCharData2->m_sCombatRecord.dwSchoolWarsDeaths, pCharData2->m_sCombatRecord.dwSchoolWarsResu,
		pCharData2->m_sCombatRecord.dwClubDeathMatchKills, pCharData2->m_sCombatRecord.dwClubDeathMatchDeaths, pCharData2->m_sCombatRecord.dwClubDeathMatchResu,
		pCharData2->m_sCombatRecord.dwPKMapKills, pCharData2->m_sCombatRecord.dwPKMapDeaths, pCharData2->m_sCombatRecord.dwPKMapResu,
		pCharData2->m_sCombatRecord.dwPVEKills, pCharData2->m_sCombatRecord.dwPVEDeaths, pCharData2->m_sCombatRecord.llPVEMoneyGain,
		pCharData2->m_dwCharID );

	int nReturn = m_pGameDB->ExecuteSQL(szTemp);

	return nReturn;
}