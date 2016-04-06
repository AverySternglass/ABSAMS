// testGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testGUI.h"
#include "testGUIDlg.h"
#include "resource.h"
#include "EditDlg.h"
#include "EditSprDlg.h"
//#include "interface.h"
//#include "absamsV3.3\Solid\Solid.hpp"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGUIDlg dialog

CTestGUIDlg::CTestGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestGUIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestGUIDlg)
	DDX_Control(pDX, IDC_SHOW_COLLISIONS, m_showCollisions);
	DDX_Control(pDX, IDC_RUN_SIMULATION, m_runSimulation);
	DDX_Control(pDX, IDC_EDIT_BUTTON, m_editButton);
	DDX_Control(pDX, IDC_LIST1, m_messageBoxText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestGUIDlg, CDialog)
	//{{AFX_MSG_MAP(CTestGUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnOpen)
	ON_BN_CLICKED(IDC_EDIT_BUTTON, OnEditButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnSaveButton)
	ON_BN_CLICKED(IDC_ADD_COMMAND, OnAddCommand)
	ON_BN_CLICKED(IDC_RUN_SIMULATION, OnRunSimulation)
	ON_BN_CLICKED(IDC_SHOW_COLLISIONS, OnShowCollisions)
	ON_BN_CLICKED(IDC_EDIT_BUTTON2, OnEditButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGUIDlg message handlers

BOOL CTestGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	this->assemblyLoaded = false;
	this->commandLoaded = false;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestGUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestGUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestGUIDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here

//	MessageBox("Use this only to open general assemblies", NULL, MB_OK);
	
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "MH Assemblies\0*.mha;\0Suckers\0*.skr\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);
	
	if(!strlen(szFile)) // Check if "cancel" has been pressed
		return;

	char fileExtension[4];
	strncpy( fileExtension, szFile+strlen(szFile)-3, 4 );
	

	if(!strcmp(fileExtension,"mha"))
		appendage = new Assembly(1,szFile);
	else if(!strcmp(fileExtension,"skr"))
		appendage = new Sucker(1,szFile);

	this->assemblyLoaded = true;
	
	if(this->commandLoaded && this->assemblyLoaded)
		this->m_runSimulation.EnableWindow();
	
	sim = new Simulation(appendage);

	char message[260];

	sprintf(message, "Opened MHA File : %s", szFile);
	m_messageBoxText.AddString(message);
	this->m_editButton.EnableWindow();
	this->m_showCollisions.EnableWindow();
	//xg
	sim->initialize();
	glutIdleFunc(mainSimulationLoop);
	glutDisplayFunc(mainDisplay); 
	glutReshapeFunc(mainWindowFunction);
	glutSpecialFunc(mainKeyboardFunction1);
	glutKeyboardFunc(mainKeyboardFunction2);

	glutMouseFunc(processMouse);

	glutMainLoop();
	


}


void CTestGUIDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}



void CTestGUIDlg::OnEditButton() 
{
	// TODO: Add your control notification handler code here
		
	CEditDlg *editDlg;
	editDlg = new CEditDlg;
	editDlg->m_mhAssembly = appendage;
	
	editDlg->Create(IDD_EDIT_DIALOG);
	editDlg->ShowWindow(1);
	char message[260];
	sprintf(message, "Editing MHUs in Assembly # %d", appendage->getNumber());
	m_messageBoxText.AddString(message);
}

void CTestGUIDlg::OnSaveButton() 
{
	// TODO: Add your control notification handler code here

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "MH Assemblies\0*.mha;\0Suckers\0*.skr\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetSaveFileName(&ofn);
	
	appendage->writeMHAFile(szFile);
}

void CTestGUIDlg::OnAddCommand() 
{
	// TODO: Add your control notification handler code here

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Command Files\0*.mhc\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);
	
	if(!strlen(szFile)) // Check if "cancel" has been pressed
		return;
	command = new Command(szFile);

	this->commandLoaded = true;

	if(this->commandLoaded && this->assemblyLoaded)
		this->m_runSimulation.EnableWindow();

	char message[260];
	sprintf(message, "Oened Command File %s", szFile);
	
	m_messageBoxText.AddString(message);
}

void CTestGUIDlg::OnRunSimulation() 
{
	// TODO: Add your control notification handler code here

	
	sim = new Simulation(g_stepSize, g_collisionDecimation, g_displayDecimation, g_imageSaveDecimation,
				g_loggingDecimation, appendage, command);

	sim->setInitialize(true);
	sim->initialize();
	glutIdleFunc(mainSimulationLoop);
	glutDisplayFunc(mainDisplay); 
	glutReshapeFunc(mainWindowFunction);
	glutSpecialFunc(mainKeyboardFunction1);
	glutKeyboardFunc(mainKeyboardFunction2);

	glutMouseFunc(processMouse);

	glutMainLoop();
	
}

void CTestGUIDlg::OnShowCollisions() 
{
	// TODO: Add your control notification handler code here
	
	for(int i =0; i < appendage->getNumMHUnits(); i++)
	{
		appendage->getMHUnit(i)->setIgnoreCollision(true);
		appendage->getMHUnit(i)->setSelectionTag(0);
	}
	sim->setSimState(SIM_COLL_CHK);
	sim->updateSolid();
	sim->checkCollision();
	//xg
	for(int i =0; i < appendage->getNumMHUnits(); i++)
		appendage->getMHUnit(i)->setIgnoreCollision(false);

	sim->setSimState(SIM_EDIT);

}


void CTestGUIDlg::OnEditButton2() 
{
	// TODO: Add your control notification handler code here
	CEditSprDlg *editSprDlg;
	editSprDlg = new CEditSprDlg;
	editSprDlg->m_mhAssembly = appendage;
	
	editSprDlg->Create(IDD_EDIT_DIALOG1);
	editSprDlg->ShowWindow(1);
	char message[260];
	sprintf(message, "Editing Nodes and Springs in Assembly # %d", appendage->getNumber());
	m_messageBoxText.AddString(message);
}
