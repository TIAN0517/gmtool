#pragma once


#include "./Logic/GMToolCharData.h"

// CDlgAwardTitleEdit dialog

class CDlgAwardTitleEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAwardTitleEdit)

public:
	CDlgAwardTitleEdit(CWnd* pParent = NULL, SAWARD_TITLE_DATA_EX* pData = NULL);   // standard constructor
	virtual ~CDlgAwardTitleEdit();

// Dialog Data
	enum { IDD = IDD_DLG_AWARD_TITLE_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	SAWARD_TITLE_DATA_EX* m_pData;

private:
	BOOL DataDefault();
	BOOL DataShow();
	BOOL DataSave();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
