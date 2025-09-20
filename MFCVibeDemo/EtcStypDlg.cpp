// EtcStypDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCVibeDemo.h"
#include "EtcStypDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEtcStypDlg dialog

IMPLEMENT_DYNAMIC(CEtcStypDlg, CDialogEx)

CEtcStypDlg::CEtcStypDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ETC_STYP, pParent)
	, m_nStructType(0)
	, m_nMassType(0)
	, m_nStructureMass(0)
	, m_bConsiderOffset(FALSE)
	, m_bConvertSelfWeight(FALSE)
	, m_bAlignBeam(FALSE)
	, m_bAlignSlab(FALSE)
	, m_bConsiderRotMPF(FALSE)
{
}

void CEtcStypDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ETC_PC_ST_3D, m_nStructType);
	DDX_Radio(pDX, IDC_ETC_PC_MASS_TYPE2, m_nMassType);
	DDX_Radio(pDX, IDC_ETC_PC_STRUCT_MASS, m_nStructureMass);
	DDX_Check(pDX, IDC_ETC_PC_CONSIDER_OFFSET_CHK, m_bConsiderOffset);
	DDX_Check(pDX, IDC_ETC_PC_CONVERT_SELFWEIGHT_CHK, m_bConvertSelfWeight);
	DDX_Check(pDX, IDC_ETC_PC_ALIGN_BEAM_CHK, m_bAlignBeam);
	DDX_Check(pDX, IDC_ETC_PC_ALIGN_SLAB_CHK, m_bAlignSlab);
	DDX_Check(pDX, IDC_ETC_CONSIDER_ROT_RIGID_MPF_CHK, m_bConsiderRotMPF);
}

BEGIN_MESSAGE_MAP(CEtcStypDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ETC_PC_MASS_TYPE2, &CEtcStypDlg::OnEtcPcMassType)
	ON_BN_CLICKED(IDC_ETC_PC_MASS_TYPE3, &CEtcStypDlg::OnEtcPcMassType)
	ON_BN_CLICKED(IDC_ETC_PC_STRUCT_MASS, &CEtcStypDlg::OnEtcPcStructMass)
	ON_BN_CLICKED(IDC_ETC_PC_STRUCT_MASS2, &CEtcStypDlg::OnEtcPcStructMass)
	ON_BN_CLICKED(IDC_ETC_PC_STRUCT_MASS3, &CEtcStypDlg::OnEtcPcStructMass)
	ON_BN_CLICKED(IDC_ETC_PC_CONSIDER_OFFSET_CHK, &CEtcStypDlg::OnEtcPcConsiderOffset)
	ON_BN_CLICKED(IDC_ETC_PC_CONVERT_SELFWEIGHT_CHK, &CEtcStypDlg::OnEtcPcSelfWeight)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEtcStypDlg message handlers

BOOL CEtcStypDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitDialogData();
	CtrlManager();
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEtcStypDlg::InitDialogData()
{
	// Initialize default values
	GetDlgItem(IDC_ETC_PC_GRAV)->SetWindowText(_T("9.8"));
	GetDlgItem(IDC_ETC_PC_TEMP)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ETC_PC_GRAV_UNIT)->SetWindowText(_T("m/s²"));
	GetDlgItem(IDC_ETC_PC_TEMP_UNIT)->SetWindowText(_T("°C"));
}

void CEtcStypDlg::OnOK()
{
	// TODO: Add extra validation here
	if (!UpdateData(TRUE)) return;
	
	// Process dialog data here
	
	CDialogEx::OnOK();
}

void CEtcStypDlg::CtrlManager()
{
	// Enable/disable controls based on selections
	if (m_nMassType == 1) // Consistent Mass
	{
		GetDlgItem(IDC_ETC_PC_CONSIDER_OFFSET_CHK)->EnableWindow(FALSE);
	}
	else // Lumped Mass
	{
		GetDlgItem(IDC_ETC_PC_CONSIDER_OFFSET_CHK)->EnableWindow(TRUE);
	}
	
	// Enable Convert options only when Convert Self-weight is checked
	GetDlgItem(IDC_ETC_PC_STRUCT_MASS)->EnableWindow(m_bConvertSelfWeight);
	GetDlgItem(IDC_ETC_PC_STRUCT_MASS2)->EnableWindow(m_bConvertSelfWeight);
	GetDlgItem(IDC_ETC_PC_STRUCT_MASS3)->EnableWindow(m_bConvertSelfWeight);
	
	// Enable Rotational MPF option only for Lumped Mass without offset
	BOOL bEnableRotMPF = (m_nMassType == 0 && !m_bConsiderOffset);
	GetDlgItem(IDC_ETC_CONSIDER_ROT_RIGID_MPF_CHK)->EnableWindow(bEnableRotMPF);
}

void CEtcStypDlg::OnEtcPcMassType()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CEtcStypDlg::OnEtcPcStructMass()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CEtcStypDlg::OnEtcPcConsiderOffset()
{
	UpdateData(TRUE);
	if (m_bConvertSelfWeight && m_bConsiderOffset)
	{
		m_nStructureMass = 0;
		CheckRadioButton(IDC_ETC_PC_STRUCT_MASS, IDC_ETC_PC_STRUCT_MASS3, IDC_ETC_PC_STRUCT_MASS);
	}
	UpdateData(FALSE);
	CtrlManager();
}

void CEtcStypDlg::OnEtcPcSelfWeight()
{
	UpdateData(TRUE);
	CtrlManager();
}