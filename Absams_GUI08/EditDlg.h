#if !defined(AFX_EDITDLG_H__915853BB_1EC6_4265_AF68_77C258318AA2__INCLUDED_)
#define AFX_EDITDLG_H__915853BB_1EC6_4265_AF68_77C258318AA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//

#include "interface.h"

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	double m_spinnerIncrement;
	int m_selMhuNumber;
	Assembly *m_mhAssembly;
	CEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_EDIT_DIALOG };
	CEdit	m_positionZ;
	CEdit	m_positionY;
	CEdit	m_positionX;
	CEdit	m_orientationN;
	CEdit	m_orientationM;
	CEdit	m_orientationL;
	CSpinButtonCtrl	m_spin9;
	CSpinButtonCtrl	m_spin8;
	CSpinButtonCtrl	m_spin7;
	CSpinButtonCtrl	m_spin6;
	CSpinButtonCtrl	m_spin5;
	CSpinButtonCtrl	m_spin4;
	CSpinButtonCtrl	m_spin3;
	CSpinButtonCtrl	m_spin2;
	CSpinButtonCtrl	m_spin1;
	CEdit	m_dim3_name;
	CEdit	m_dim2_name;
	CEdit	m_dim1_name;
	CEdit	m_mhuShape;
	CEdit	m_dimension3;
	CEdit	m_dimension2;
	CEdit	m_dimension1;
	CEdit	m_selectedMHU;
	CComboBox	m_tagSelection;
	CEdit	m_numMHU;
	CComboBox	m_mhuComboList;
	double	m_initDimension1;
	double	m_initDimension2;
	double	m_initDimension3;
	double	m_initOrientationL;
	double	m_initOrientationM;
	double	m_initOrientationN;
	double	m_initPositionX;
	double	m_initPositionY;
	double	m_initPositionZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMhuSelected();
	afx_msg void OnchangeTag();
	afx_msg void OnSpin1change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin2change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin3change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin4change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin5change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin6change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin7change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin8change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpin9change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__915853BB_1EC6_4265_AF68_77C258318AA2__INCLUDED_)
