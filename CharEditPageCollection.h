#pragma once

class	CCharEditTab;
struct	SCHARDATA2;


class CCharEditPageCollection : public CPropertyPage
{
	DECLARE_DYNAMIC(CCharEditPageCollection)

public:
	CCharEditPageCollection(LOGFONT logfont, SCHARDATA2* pData);
	virtual ~CCharEditPageCollection();

	// Dialog Data
	enum { IDD = IDD_CHAREDIT_PAGE_COLLECTION };

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

private:
	CListCtrl	m_ListProg;
	CListCtrl	m_ListDone;

public:
	void UpdateProgList();
	void UpdateDoneList();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedChareditCollectionButtonProgEdit();
	afx_msg void OnBnClickedChareditCollectionButtonProgComplete();
	afx_msg void OnBnClickedChareditCollectionButtonProgDelete();
	afx_msg void OnBnClickedChareditCollectionButtonProgClear();
	afx_msg void OnBnClickedChareditCollectionButtonDoneDelete();
	afx_msg void OnBnClickedChareditCollectionButtonDoneClear();
};
