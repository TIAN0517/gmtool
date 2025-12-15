#pragma once

class	CCharEditTab;
struct SGMToolCharData;

// CCharEditPageAwardTitle dialog

class CCharEditPageAwardTitle : public CPropertyPage
{
	DECLARE_DYNAMIC(CCharEditPageAwardTitle)

public:
	CCharEditPageAwardTitle(LOGFONT logfont, SGMToolCharData* pData);
	virtual ~CCharEditPageAwardTitle();

// Dialog Data
	enum { IDD = IDD_CHAREDIT_PAGE_AWARD_TITLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CCharEditTab*	m_pSheetTab;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	CFont*			m_pFont;
	SGMToolCharData*		m_pData;

public:
	void	SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void	SetSheetTab ( CCharEditTab* pSheetTab ) { m_pSheetTab = pSheetTab; }

private:
	CListCtrl	m_List;

public:
	void	ShowData();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChareditAwardTitleButtonAdd();
	afx_msg void OnBnClickedChareditAwardTitleButtonEdit();
	afx_msg void OnBnClickedChareditAwardTitleButtonDisable();
	afx_msg void OnBnClickedChareditAwardTitleButtonEnable();
	afx_msg void OnBnClickedChareditAwardTitleButtonDisableAll();
};
