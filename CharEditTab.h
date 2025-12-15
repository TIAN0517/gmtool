#ifndef _GMTOOL_CHAREDITTAB_H_
#define _GMTOOL_CHAREDITTAB_H_

struct SGMToolCharData;
/////////////////////////////////////////////////////////////////////////////
// CCharEditTab

#include "./GMToolTab.h"

#include "./CharEditPageBasic.h"
#include "./CharEditPagePutOn.h"
#include "./CharEditPageInven.h"
#include "./CharEditPageSkills.h"
#include "./CharEditPageSlotAction.h"
#include "./CharEditPageSlotSkill.h"
#include "./CharEditPageQuest.h"
#include "./CharEditPageCoolTime.h"
#include "./CharEditPageLocker.h"
#include "./CharEditPageItemFood.h"
#include "./CharEditPageActivity.h"			/*activity system, Juver, 2017/10/23 */
#include "./CharEditPagePersonalLock.h"
#include "./CharEditPagePKCombo.h"			/* pk combo, Juver, 2021/02/11 */
#include "./CharEditPageAwardTitle.h"		/* award title, Juver, 2021/02/13 */
#include "./CharEditPageCombatRecord.h"
#include "./CharEditPageCollection.h"

class CCharEditTab : public CPropertySheet
{
	DECLARE_DYNAMIC(CCharEditTab)

public:
	CWnd*		m_pWndParent;
	SGMToolCharData* m_pData;

public:
	CCharEditPageBasic		m_PageBasic;
	CCharEditPagePutOn		m_PagePutOn;
	CCharEditPageInven		m_PageInven;
	CCharEditPageSkills		m_PageSkills;
	CCharEditPageSlotAction m_PageSlotAction;
	CCharEditPageSlotSkill	m_PageSlotSkill;
	CCharEditPageQuest		m_PageQuest;
	CCharEditPageCoolTime	m_PageCoolTime;
	CCharEditPageLocker		m_PageLocker;
	CCharEditPageItemFood	m_PageItemFood;
	CCharEditPageActivity	m_PageActivity;					/*activity system, Juver, 2017/10/23 */
	CCharEditPagePersonalLock	m_PagePersonalLock;
	CCharEditPagePKCombo		m_PagePKCombo;				/* pk combo, Juver, 2021/02/11 */
	CCharEditPageAwardTitle		m_PageAwardTitle;			/* award title, Juver, 2021/02/13 */
	CCharEditPageCombatRecord	m_PageCombatRecord;
	CCharEditPageCollection		m_pPageItemCollection;

public:	

// Construction
public:
	CCharEditTab(CWnd* pParentWnd = NULL);
	CCharEditTab( SGMToolCharData* pData, CRect& rect, LOGFONT logfont, CWnd* pParentWnd = NULL );
	virtual ~CCharEditTab();

// Attributes
public:
	CRect		m_Rect;
	BOOL		m_bNoTabs;
	int			m_iDistanceFromTop;
	CFont*		m_pFont;

// Get/Set
public:
   void NoTabs() { m_bNoTabs = TRUE; }
   void SetDistanceFromTop( int iDistance ) { m_iDistanceFromTop = iDistance; }
   void ChangeDialogFont(CWnd* pWnd, CFont* pFont, int nFlag);

public:
	virtual BOOL OnInitDialog();

	void	InitPages();

	BOOL	SaveInfo();

// Generated message map functions
protected:
	afx_msg HBRUSH CtlColor(CDC* pDc, UINT uCtlColor);	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#endif	// _GMTOOL_CHAREDITTAB_H_