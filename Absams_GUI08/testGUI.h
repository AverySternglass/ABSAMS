// testGUI.h : main header file for the TESTGUI application
//

#if !defined(AFX_TESTGUI_H__3E4BEAA7_4713_4B75_A854_EF56994D77EE__INCLUDED_)
#define AFX_TESTGUI_H__3E4BEAA7_4713_4B75_A854_EF56994D77EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestGUIApp:
// See testGUI.cpp for the implementation of this class
//

class CTestGUIApp : public CWinApp
{
public:
	CTestGUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestGUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGUI_H__3E4BEAA7_4713_4B75_A854_EF56994D77EE__INCLUDED_)
