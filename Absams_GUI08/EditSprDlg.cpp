// EditSprDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testGUI.h"
#include "EditSprDlg.h"
#include "TestGUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditSprDlg dialog


CEditSprDlg::CEditSprDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditSprDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditSprDlg)
	m_initPositionU = 0.0;
	m_initPositionV = 0.0;
	m_initPositionW = 0.0;
	//}}AFX_DATA_INIT
}


void CEditSprDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditSprDlg)
	DDX_Control(pDX, IDC_ASSOC_MHU, m_assocMHU);
	DDX_Control(pDX, IDC_POSITION_W, m_positionW);
	DDX_Control(pDX, IDC_POSITION_V, m_positionV);
	DDX_Control(pDX, IDC_POSITION_U, m_positionU);
	DDX_Control(pDX, IDC_SPIN18, m_spin18);
	DDX_Control(pDX, IDC_SPIN17, m_spin17);
	DDX_Control(pDX, IDC_SPIN16, m_spin16);
	DDX_Control(pDX, IDC_SPIN15, m_spin15);
	DDX_Control(pDX, IDC_SPIN14, m_spin14);
	DDX_Control(pDX, IDC_SPIN13, m_spin13);
	DDX_Control(pDX, IDC_SPIN12, m_spin12);
	DDX_Control(pDX, IDC_NUM_NODES, m_numNodes);
	DDX_Control(pDX, IDC_SEL_NODE, m_selectedNode);
	DDX_Control(pDX, IDC_NODE_SELECT_COMBO, m_nodeComboList);
	DDX_Text(pDX, IDC_POSITION_U, m_initPositionU);
	DDX_Text(pDX, IDC_POSITION_V, m_initPositionV);
	DDX_Text(pDX, IDC_POSITION_W, m_initPositionW);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditSprDlg, CDialog)
	//{{AFX_MSG_MAP(CEditSprDlg)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN12, OnSpin12chnage)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN13, OnSpin13change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN14, OnSpin14change)
	ON_CBN_SELCHANGE(IDC_NODE_SELECT_COMBO, OnNodeSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditSprDlg message handlers

void CEditSprDlg::OnApply() 
{
	// TODO: Add your control notification handler code here
	CString value,valU,valV,valW,assocMHU;
	Node *nodePtr;

	nodePtr = this->m_mhAssembly->getSurface(0)->getNode(m_selNodeNumber);
	
	this->m_positionU.GetWindowText(valU);
	this->m_positionV.GetWindowText(valV);
	this->m_positionW.GetWindowText(valW);
	nodePtr->setRelativePosition(Vector(atof(valU),atof(valV),atof(valW)));
	
}

void CEditSprDlg::OnSpin12chnage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initPositionU+(num*m_spinnerIncrement)));
	this->m_positionU.SetWindowText(temp);

	*pResult = 0;
}

void CEditSprDlg::OnSpin13change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initPositionV+(num*m_spinnerIncrement)));
	this->m_positionV.SetWindowText(temp);

	*pResult = 0;
}

void CEditSprDlg::OnSpin14change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initPositionW+(num*m_spinnerIncrement)));
	this->m_positionW.SetWindowText(temp);

	*pResult = 0;
}

void CEditSprDlg::OnOK() 
{
	// TODO: Add extra validation here
	this->OnApply();
	this->OnCancel();
	//CDialog::OnOK();
}

void CEditSprDlg::OnNodeSelected() 
{
	// TODO: Add your control notification handler code here

	int index;
	CString tempText;
	char temp[10];

    index= m_nodeComboList.GetCurSel();
	m_nodeComboList.GetLBText( index, tempText);
	this->m_selNodeNumber = atoi(tempText);
	
	for(int i = 0; i < m_mhAssembly->getSurface(0)->getNumNodes(); i++)
		m_mhAssembly->getSurface(0)->getNode(i)->setSelectionTag(0);

	m_mhAssembly->getSurface(0)->getNode(m_selNodeNumber)->setSelectionTag(1);
	this->m_selectedNode.SetWindowText(itoa(m_selNodeNumber,temp,10));

	Node *nodePtr = this->m_mhAssembly->getSurface(0)->getNode(m_selNodeNumber);

	this->m_assocMHU.SetWindowText(itoa(nodePtr->getMHUnitID()->getID(),temp,10));

	this->m_initPositionU = nodePtr->getRelativePosition().getX();
	this->m_initPositionV = nodePtr->getRelativePosition().getY();
	this->m_initPositionW = nodePtr->getRelativePosition().getZ();

	
	sprintf(temp,"%f",m_initPositionU);
	this->m_positionU.SetWindowText(temp);
	sprintf(temp,"%f",m_initPositionV);
	this->m_positionV.SetWindowText(temp);
	sprintf(temp,"%f",m_initPositionW);
	this->m_positionW.SetWindowText(temp);

	char message[260];
	sprintf(message, "Selected Node # %d", m_selNodeNumber);
	CWnd *parent = this->GetParent();
	CTestGUIDlg *qq = (CTestGUIDlg *)parent;
	qq->m_messageBoxText.AddString(message);
	
}

void CEditSprDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CEditSprDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	char title[260];
	sprintf(title, "Node/Spring Editor for Assembly %d", m_mhAssembly->getNumber());
	this->SetWindowText(title);

	char temp[4];
	this->m_numNodes.SetWindowText(itoa(m_mhAssembly->getSurface(0)->getNumNodes(),temp,10));
	

	for(int i = 0; i < m_mhAssembly->getSurface(0)->getNumNodes(); i++)
		m_nodeComboList.AddString(itoa(m_mhAssembly->getSurface(0)->getNode(i)->getNumber(),temp,10));
	this->m_nodeComboList.SetCurSel(0);
	
	this->OnNodeSelected();

	this->m_spinnerIncrement = 0.0001; // Magic Number !!!!!!!!

	UDACCEL AccellValue;
	AccellValue.nSec = 1000;
	AccellValue.nInc = 1;
	
	this->m_spin12.SetRange(-1000, 1000);
	this->m_spin13.SetRange(-1000, 1000);
	this->m_spin14.SetRange(-1000, 1000);
	this->m_spin15.SetRange(-1000, 1000);
	this->m_spin16.SetRange(-1000, 1000);
	this->m_spin17.SetRange(-1000, 1000);
	this->m_spin18.SetRange(-1000, 1000);
	
	this->m_spin12.SetAccel(1, &AccellValue); 
	this->m_spin13.SetAccel(1, &AccellValue); 
	this->m_spin14.SetAccel(1, &AccellValue);
	this->m_spin15.SetAccel(1, &AccellValue);
	this->m_spin16.SetAccel(1, &AccellValue);
	this->m_spin17.SetAccel(1, &AccellValue);
	this->m_spin18.SetAccel(1, &AccellValue);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
