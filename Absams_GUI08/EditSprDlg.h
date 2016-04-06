#if !defined(AFX_EDITSPRDLG_H__A338EABD_0B3B_4B97_B3C1_9BF713F975CF__INCLUDED_)
#define AFX_EDITSPRDLG_H__A338EABD_0B3B_4B97_B3C1_9BF713F975CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditSprDlg.h : header file
//

#include "interface.h"

/////////////////////////////////////////////////////////////////////////////
// CEditSprDlg dialog

class CEditSprDlg : public CDialog
{
// Construction
public:
	double m_spinnerIncrement;
	int m_selNodeNumber;
	int m_selSpringNumber;
	Assembly *m_mhAssembly;
	CEditSprDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditSprDlg)
	enum { IDD = IDD_EDIT_DIALOG1 };
	CEdit	m_assocMHU;
	CEdit	m_positionW;
	CEdit	m_positionV;
	CEdit	m_positionU;
	CSpinButtonCtrl	m_spin18;
	CSpinButtonCtrl	m_spin17;
	CSpinButtonCtrl	m_spin16;
	CSpinButtonCtrl	m_spin15;
	CSpinButtonCtrl	m_spin14;
	CSpinButtonCtrl	m_spin13;
	CSpinButtonCtrl	m_spin12;
	CEdit	m_numNodes;
	CEdit	m_selectedNode;
	CComboBox	m_nodeComboList;
	double	m_initPositionU;
	double	m_initPositionV;
	double	m_initPositionW;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditSprDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditSprDlg)
	afx_msg void OnApply();
	afx_msg void OnSpin12chnage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin13change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin14change(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnNodeSelected();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITSPRDLG_H__A338EABD_0B3B_4B97_B3C1_9BF713F975CF__INCLUDED_)
