// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testGUI.h"
#include "EditDlg.h"
#include "TestGUIDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDlg)
	m_initDimension1 = 0.0;
	m_initDimension2 = 0.0;
	m_initDimension3 = 0.0;
	m_initOrientationL = 0.0;
	m_initOrientationM = 0.0;
	m_initOrientationN = 0.0;
	m_initPositionX = 0.0;
	m_initPositionY = 0.0;
	m_initPositionZ = 0.0;
	//}}AFX_DATA_INIT
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Control(pDX, IDC_POSITION_Z, m_positionZ);
	DDX_Control(pDX, IDC_POSITION_Y, m_positionY);
	DDX_Control(pDX, IDC_POSITION_X, m_positionX);
	DDX_Control(pDX, IDC_ORIENTATION_N, m_orientationN);
	DDX_Control(pDX, IDC_ORIENTATION_M, m_orientationM);
	DDX_Control(pDX, IDC_ORIENTATION_L, m_orientationL);
	DDX_Control(pDX, IDC_SPIN9, m_spin9);
	DDX_Control(pDX, IDC_SPIN8, m_spin8);
	DDX_Control(pDX, IDC_SPIN7, m_spin7);
	DDX_Control(pDX, IDC_SPIN6, m_spin6);
	DDX_Control(pDX, IDC_SPIN5, m_spin5);
	DDX_Control(pDX, IDC_SPIN4, m_spin4);
	DDX_Control(pDX, IDC_SPIN3, m_spin3);
	DDX_Control(pDX, IDC_SPIN2, m_spin2);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_DIM3, m_dim3_name);
	DDX_Control(pDX, IDC_DIM2, m_dim2_name);
	DDX_Control(pDX, IDC_DIM1, m_dim1_name);
	DDX_Control(pDX, IDC_SHAPE, m_mhuShape);
	DDX_Control(pDX, IDC_DIMENSION_3, m_dimension3);
	DDX_Control(pDX, IDC_DIMENSION_2, m_dimension2);
	DDX_Control(pDX, IDC_DIMENSION_1, m_dimension1);
	DDX_Control(pDX, IDC_SEL_MHU, m_selectedMHU);
	DDX_Control(pDX, IDC_TAG_SELECT, m_tagSelection);
	DDX_Control(pDX, IDC_NUM_MHU, m_numMHU);
	DDX_Control(pDX, IDC_MHU_SELECT_COMBO, m_mhuComboList);
	DDX_Text(pDX, IDC_DIMENSION_1, m_initDimension1);
	DDX_Text(pDX, IDC_DIMENSION_2, m_initDimension2);
	DDX_Text(pDX, IDC_DIMENSION_3, m_initDimension3);
	DDX_Text(pDX, IDC_ORIENTATION_L, m_initOrientationL);
	DDX_Text(pDX, IDC_ORIENTATION_M, m_initOrientationM);
	DDX_Text(pDX, IDC_ORIENTATION_N, m_initOrientationN);
	DDX_Text(pDX, IDC_POSITION_X, m_initPositionX);
	DDX_Text(pDX, IDC_POSITION_Y, m_initPositionY);
	DDX_Text(pDX, IDC_POSITION_Z, m_initPositionZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_CBN_SELCHANGE(IDC_MHU_SELECT_COMBO, OnMhuSelected)
	ON_CBN_SELCHANGE(IDC_TAG_SELECT, OnchangeTag)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnSpin1change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnSpin2change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnSpin3change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnSpin4change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, OnSpin5change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, OnSpin6change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, OnSpin7change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN8, OnSpin8change)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN9, OnSpin9change)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

BOOL CEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	
	char title[260];
	sprintf(title, "Editor for Assembly %d", m_mhAssembly->getNumber());
	this->SetWindowText(title);

	char temp[4];
	this->m_numMHU.SetWindowText(itoa(m_mhAssembly->getNumMHUnits(),temp,10));
	

	for(int i = 0; i < m_mhAssembly->getNumMHUnits(); i++)
		m_mhuComboList.AddString(itoa(m_mhAssembly->getMHUnit(i)->getID(),temp,10));
	this->m_mhuComboList.SetCurSel(0);
	
	//xg
	for(int i = 0; i < 3; i++) // Can add additional tags when they are implemented
		m_tagSelection.AddString(itoa(i,temp,10));
	this->m_tagSelection.SetCurSel(0);
	this->OnMhuSelected();

	this->m_spinnerIncrement = 0.0001; // Magic Number !!!!!!!!

	UDACCEL AccellValue;
	AccellValue.nSec = 1000;
	AccellValue.nInc = 1;
	this->m_spin1.SetRange(-1000, 1000);
	this->m_spin2.SetRange(-1000, 1000);
	this->m_spin3.SetRange(-1000, 1000);
	this->m_spin4.SetRange(-1000, 1000);
	this->m_spin5.SetRange(-1000, 1000);
	this->m_spin6.SetRange(-1000, 1000);
	this->m_spin7.SetRange(-1000, 1000);
	this->m_spin8.SetRange(-1000, 1000);
	this->m_spin9.SetRange(-1000, 1000);
	this->m_spin1.SetAccel(1, &AccellValue); 
	this->m_spin2.SetAccel(1, &AccellValue); 
	this->m_spin3.SetAccel(1, &AccellValue); 
	this->m_spin4.SetAccel(1, &AccellValue);
	this->m_spin5.SetAccel(1, &AccellValue);
	this->m_spin6.SetAccel(1, &AccellValue);
	this->m_spin7.SetAccel(1, &AccellValue);
	this->m_spin8.SetAccel(1, &AccellValue);
	this->m_spin9.SetAccel(1, &AccellValue);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditDlg::OnMhuSelected() 
{
	// TODO: Add your control notification handler code here
	
	int index;
	CString tempText;
	char temp[10];
	Cylinder *cylPtr;
	Box *boxPtr;

    index= m_tagSelection.GetCurSel();
	m_tagSelection.GetLBText( index, tempText);
	int selectionTag = atoi(tempText);

	index= m_mhuComboList.GetCurSel();
	m_mhuComboList.GetLBText( index, tempText);
	this->m_selMhuNumber = atoi(tempText);
	
	m_mhAssembly->getMHUnit(m_selMhuNumber)->setSelectionTag(selectionTag);
	this->m_selectedMHU.SetWindowText(itoa(m_selMhuNumber,temp,10));

	Muscle *musclePtr = this->m_mhAssembly->getMHUnit(m_selMhuNumber);
	this->m_initPositionX = musclePtr->getPosition().getX();
	this->m_initPositionY = musclePtr->getPosition().getY();
	this->m_initPositionZ = musclePtr->getPosition().getZ();

	this->m_initOrientationL = musclePtr->getOrientation().getX();
	this->m_initOrientationM = musclePtr->getOrientation().getY();
	this->m_initOrientationN = musclePtr->getOrientation().getZ();

	sprintf(temp,"%f",m_initPositionX);
	this->m_positionX.SetWindowText(temp);
	sprintf(temp,"%f",m_initPositionY);
	this->m_positionY.SetWindowText(temp);
	sprintf(temp,"%f",m_initPositionZ);
	this->m_positionZ.SetWindowText(temp);

	sprintf(temp,"%f",m_initOrientationL);
	this->m_orientationL.SetWindowText(temp);
	sprintf(temp,"%f",m_initOrientationM);
	this->m_orientationM.SetWindowText(temp);
	sprintf(temp,"%f",m_initOrientationN);
	this->m_orientationN.SetWindowText(temp);
	
	switch(musclePtr->getShape())
	{
		case 1: 
			cylPtr = (Cylinder *)(this->m_mhAssembly->getMHUnit(m_selMhuNumber));
			this->m_mhuShape.SetWindowText("Cylinder");
			this->m_dim1_name.SetWindowText("Radius");
			this->m_dim2_name.SetWindowText("Height");
			this->m_dim3_name.SetWindowText("------");
			this->m_initDimension1 = cylPtr->getRadius();
			sprintf(temp,"%f",m_initDimension1);
			this->m_dimension1.SetWindowText(temp);
			this->m_initDimension2 = cylPtr->getHeight();
			sprintf(temp,"%f",m_initDimension2);
			this->m_dimension2.SetWindowText(temp);
			this->m_initDimension3 = -1;
			this->m_dimension3.SetWindowText("n/a");
			break;
		case 2:
			boxPtr = (Box *)(this->m_mhAssembly->getMHUnit(m_selMhuNumber));
			this->m_mhuShape.SetWindowText("Box");
			this->m_dim1_name.SetWindowText("Dimension1");
			this->m_dim2_name.SetWindowText("Dimension2");
			this->m_dim3_name.SetWindowText("Dimension3");
			this->m_initDimension1 = boxPtr->getDimension1();
			sprintf(temp,"%f",m_initDimension1);
			this->m_dimension1.SetWindowText(temp);
			this->m_initDimension2 = boxPtr->getDimension2();
			sprintf(temp,"%f",m_initDimension2);
			this->m_dimension2.SetWindowText(temp);
			this->m_initDimension3 = boxPtr->getDimension3();
			sprintf(temp,"%f",m_initDimension3);
			this->m_dimension3.SetWindowText(temp);
			break;
		default:
			this->m_mhuShape.SetWindowText("???");
			break;
	}
	



	char message[260];
	sprintf(message, "Selected MHU # %d, Tag is %d", m_selMhuNumber, selectionTag);
	CWnd *parent = this->GetParent();
	CTestGUIDlg *qq = (CTestGUIDlg *)parent;
	qq->m_messageBoxText.AddString(message);
	
}

void CEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	this->OnApply();
	this->OnCancel();
	//CDialog::OnOK();
}


void CEditDlg::OnchangeTag() 
{
	// TODO: Add your control notification handler code here
	this->OnMhuSelected();
	
}

void CEditDlg::OnSpin1change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initDimension1+(num*m_spinnerIncrement)));
	this->m_dimension1.SetWindowText(temp);

	*pResult = 0;
}

void CEditDlg::OnSpin2change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initDimension2+(num*m_spinnerIncrement)));
	this->m_dimension2.SetWindowText(temp);

	*pResult = 0;
}

void CEditDlg::OnSpin3change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	if(this->m_mhAssembly->getMHUnit(m_selMhuNumber)->getShape() == 1)
		return;

	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initDimension3+(num*m_spinnerIncrement)));
	this->m_dimension1.SetWindowText(temp);

	*pResult = 0;
}

void CEditDlg::OnSpin4change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initPositionX+(num*m_spinnerIncrement)));
	this->m_positionX.SetWindowText(temp);
	
	*pResult = 0;
}

void CEditDlg::OnSpin5change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initPositionY+(num*m_spinnerIncrement)));
	this->m_positionY.SetWindowText(temp);
	
	
	*pResult = 0;
}

void CEditDlg::OnSpin6change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initPositionZ+(num*m_spinnerIncrement)));
	this->m_positionZ.SetWindowText(temp);
	
	*pResult = 0;
}

void CEditDlg::OnSpin7change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initOrientationL+(num*m_spinnerIncrement)));
	this->m_orientationL.SetWindowText(temp);
	
	*pResult = 0;
}

void CEditDlg::OnSpin8change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initOrientationM+(num*m_spinnerIncrement)));
	this->m_orientationM.SetWindowText(temp);
	
	*pResult = 0;
}

void CEditDlg::OnSpin9change(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	char temp[10];
	int num = pNMUpDown->iPos;
	
	sprintf(temp,"%f",(this->m_initOrientationN+(num*m_spinnerIncrement)));
	this->m_orientationN.SetWindowText(temp);
	
	*pResult = 0;
}

void CEditDlg::OnApply() 
{
	// TODO: Add your control notification handler code here
	CString value,valX,valY,valZ;
	Muscle *musclePtr;
	Cylinder *cylPtr;
	Box *boxPtr;

	musclePtr = this->m_mhAssembly->getMHUnit(m_selMhuNumber);

	this->m_positionX.GetWindowText(valX);
	this->m_positionY.GetWindowText(valY);
	this->m_positionZ.GetWindowText(valZ);
	musclePtr->setPosition(Vector(atof(valX),atof(valY),atof(valZ)));

	this->m_orientationL.GetWindowText(valX);
	this->m_orientationM.GetWindowText(valY);
	this->m_orientationN.GetWindowText(valZ);
	musclePtr->setOrientation(Vector(atof(valX),atof(valY),atof(valZ)));

	switch(musclePtr->getShape())
	{
		case 1: 
			cylPtr = (Cylinder *)(this->m_mhAssembly->getMHUnit(m_selMhuNumber));
			this->m_dimension1.GetWindowText(value);
			cylPtr->setRadius(atof(value));
			this->m_dimension2.GetWindowText(value);
			cylPtr->setHeight(atof(value));			
			break;
		case 2:
			boxPtr = (Box *)(this->m_mhAssembly->getMHUnit(m_selMhuNumber));
			this->m_dimension1.GetWindowText(value);
			boxPtr->setDimension1(atof(value));
			this->m_dimension2.GetWindowText(value);
			//boxPtr->setDimension2(atof(value));
			this->m_dimension3.GetWindowText(value);
			boxPtr->setDimension3(atof(value));
			break;
		default:
			MessageBox("ERROR");
			break;
	}
	
	

	
}
