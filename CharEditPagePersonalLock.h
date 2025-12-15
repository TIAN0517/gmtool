#pragma once

class	CCharEditTab;
struct SCHARDATA2;

// CCharEditPageBasic dialog

class CCharEditPagePersonalLock : public CPropertyPage
{
	DECLARE_DYNAMIC(CCharEditPagePersonalLock)

public:
	CCharEditPagePersonalLock(LOGFONT logfont, SCHARDATA2* pData);
	virtual ~CCharEditPagePersonalLock();

// Dialog Data
	enum { IDD = IDD_CHAREDIT_PAGE_PERSONAL_LOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CCharEditTab*	m_pSheetTab;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	CFont*			m_pFont;
	SCHARDATA2*		m_pData;

public:
	void	SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void	SetSheetTab ( CCharEditTab* pSheetTab ) { m_pSheetTab = pSheetTab; }

public:
	void	DataDefault();
	void	DataShow();
	BOOL	DataSave();


public:
	virtual BOOL OnInitDialog();


};
