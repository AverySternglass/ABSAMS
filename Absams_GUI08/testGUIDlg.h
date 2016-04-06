// testGUIDlg.h : header file
//

#if !defined(AFX_TESTGUIDLG_H__877F17CA_CC09_4EC2_90D5_6DCBB18E3907__INCLUDED_)
#define AFX_TESTGUIDLG_H__877F17CA_CC09_4EC2_90D5_6DCBB18E3907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestGUIDlg dialog

class CTestGUIDlg : public CDialog
{
// Construction
public:
	bool commandLoaded;
	bool assemblyLoaded;
	CTestGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestGUIDlg)
	enum { IDD = IDD_TESTGUI_DIALOG };
	CButton	m_showCollisions;
	CButton	m_runSimulation;
	CButton	m_editButton;
	CListBox	m_messageBoxText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	virtual void OnCancel();
	afx_msg void OnEditButton();
	afx_msg void OnSaveButton();
	afx_msg void OnAddCommand();
	afx_msg void OnRunSimulation();
	afx_msg void OnShowCollisions();
	afx_msg void OnEditButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGUIDLG_H__877F17CA_CC09_4EC2_90D5_6DCBB18E3907__INCLUDED_)
