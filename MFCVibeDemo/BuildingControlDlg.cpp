// BuildingControlDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCVibeDemo.h"
#include "BuildingControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuildingControlDlg dialog

IMPLEMENT_DYNAMIC(CBuildingControlDlg, CDialogEx)

CBuildingControlDlg::CBuildingControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BUILDING_CONTROL, pParent)
	, m_bUseGroundLevel(FALSE)
	, m_dGroundLevel(0.0)
	, m_bConsiderUndergroundSeismic(FALSE)
	, m_dBedrockLevel(0.0)
	, m_bConsiderMassBelowGround(FALSE)
	, m_bStoryShearForceRatio(TRUE)
	, m_bConsiderWindSeismicLoads(TRUE)
	, m_bEccentricityRatio(FALSE)
	, m_nStoryCenterType(0)
	, m_strLoadCase(_T(""))
	, m_dScaleFactor(1.0)
	, m_strXDirectionalLoadCase(_T(""))
	, m_strYDirectionalLoadCase(_T(""))
	, m_bStoryResponseTimeHistory(FALSE)
	, m_nStoryResponseType(0)
	, m_bStoryDriftByMaxVertical(FALSE)
{
}

void CBuildingControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_BC_USE_GROUND_LEVEL_CHK, m_bUseGroundLevel);
	DDX_Text(pDX, IDC_BC_GROUND_LEVEL_EDIT, m_dGroundLevel);
	DDX_Check(pDX, IDC_BC_CONSIDER_UNDERGROUND_CHK, m_bConsiderUndergroundSeismic);
	DDX_Text(pDX, IDC_BC_BEDROCK_LEVEL_EDIT, m_dBedrockLevel);
	DDX_Check(pDX, IDC_BC_CONSIDER_MASS_BELOW_CHK, m_bConsiderMassBelowGround);
	DDX_Check(pDX, IDC_BC_STORY_SHEAR_FORCE_CHK, m_bStoryShearForceRatio);
	DDX_Check(pDX, IDC_BC_CONSIDER_WIND_SEISMIC_CHK, m_bConsiderWindSeismicLoads);
	DDX_Check(pDX, IDC_BC_ECCENTRICITY_RATIO_CHK, m_bEccentricityRatio);
	DDX_Radio(pDX, IDC_BC_USE_MASS_RADIO, m_nStoryCenterType);
	DDX_CBString(pDX, IDC_BC_LOAD_CASE_COMBO, m_strLoadCase);
	DDX_Text(pDX, IDC_BC_SCALE_FACTOR_EDIT, m_dScaleFactor);
	DDX_CBString(pDX, IDC_BC_X_DIRECTIONAL_COMBO, m_strXDirectionalLoadCase);
	DDX_CBString(pDX, IDC_BC_Y_DIRECTIONAL_COMBO, m_strYDirectionalLoadCase);
	DDX_Check(pDX, IDC_BC_STORY_RESPONSE_CHK, m_bStoryResponseTimeHistory);
	DDX_Radio(pDX, IDC_BC_STORY_CENTER_RADIO, m_nStoryResponseType);
	DDX_Check(pDX, IDC_BC_STORY_DRIFT_CHK, m_bStoryDriftByMaxVertical);
}

BEGIN_MESSAGE_MAP(CBuildingControlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BC_USE_GROUND_LEVEL_CHK, &CBuildingControlDlg::OnUseGroundLevel)
	ON_BN_CLICKED(IDC_BC_CONSIDER_UNDERGROUND_CHK, &CBuildingControlDlg::OnConsiderUndergroundSeismic)
	ON_BN_CLICKED(IDC_BC_CONSIDER_MASS_BELOW_CHK, &CBuildingControlDlg::OnConsiderMassBelowGround)
	ON_BN_CLICKED(IDC_BC_ECCENTRICITY_RATIO_CHK, &CBuildingControlDlg::OnEccentricityRatio)
	ON_BN_CLICKED(IDC_BC_USE_MASS_RADIO, &CBuildingControlDlg::OnStoryCenterType)
	ON_BN_CLICKED(IDC_BC_USE_AXIAL_FORCE_RADIO, &CBuildingControlDlg::OnStoryCenterType)
	ON_BN_CLICKED(IDC_BC_USE_SHEAR_FORCE_RADIO, &CBuildingControlDlg::OnStoryCenterType)
	ON_BN_CLICKED(IDC_BC_STORY_RESPONSE_CHK, &CBuildingControlDlg::OnStoryResponseTimeHistory)
	ON_BN_CLICKED(IDC_BC_STORY_CENTER_RADIO, &CBuildingControlDlg::OnStoryResponseType)
	ON_BN_CLICKED(IDC_BC_STORY_AVERAGE_RADIO, &CBuildingControlDlg::OnStoryResponseType)
	ON_BN_CLICKED(IDC_BC_ADD_BUTTON, &CBuildingControlDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BC_MODIFY_BUTTON, &CBuildingControlDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_BC_DELETE_BUTTON, &CBuildingControlDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BC_X_DIRECTIONAL_BUTTON, &CBuildingControlDlg::OnBnClickedXDirectionalButton)
	ON_BN_CLICKED(IDC_BC_Y_DIRECTIONAL_BUTTON, &CBuildingControlDlg::OnBnClickedYDirectionalButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildingControlDlg message handlers

BOOL CBuildingControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitDialogData();
	CtrlManager();
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CBuildingControlDlg::InitDialogData()
{
	// Initialize default values
	GetDlgItem(IDC_BC_GROUND_LEVEL_UNIT)->SetWindowText(_T("m"));
	GetDlgItem(IDC_BC_BEDROCK_LEVEL_UNIT)->SetWindowText(_T("m"));
	
	// Initialize combo boxes with sample data
	CComboBox* pLoadCaseCombo = (CComboBox*)GetDlgItem(IDC_BC_LOAD_CASE_COMBO);
	if (pLoadCaseCombo)
	{
		pLoadCaseCombo->AddString(_T("Load Case 1"));
		pLoadCaseCombo->AddString(_T("Load Case 2"));
		pLoadCaseCombo->AddString(_T("Load Case 3"));
	}
	
	CComboBox* pXDirectionalCombo = (CComboBox*)GetDlgItem(IDC_BC_X_DIRECTIONAL_COMBO);
	if (pXDirectionalCombo)
	{
		pXDirectionalCombo->AddString(_T("X-Direction Case 1"));
		pXDirectionalCombo->AddString(_T("X-Direction Case 2"));
	}
	
	CComboBox* pYDirectionalCombo = (CComboBox*)GetDlgItem(IDC_BC_Y_DIRECTIONAL_COMBO);
	if (pYDirectionalCombo)
	{
		pYDirectionalCombo->AddString(_T("Y-Direction Case 1"));
		pYDirectionalCombo->AddString(_T("Y-Direction Case 2"));
	}
	
	// Initialize list control
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_BC_LOAD_CASE_LIST);
	if (pListCtrl)
	{
		// Set extended styles for the list control
		pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		
		// Insert columns with adjusted widths for the smaller dialog
		pListCtrl->InsertColumn(0, _T("Load Case"), LVCFMT_LEFT, 90);
		pListCtrl->InsertColumn(1, _T("Scale"), LVCFMT_LEFT, 45);
	}
}

void CBuildingControlDlg::OnOK()
{
	// TODO: Add extra validation here
	if (!UpdateData(TRUE)) return;
	
	// Process dialog data here
	
	CDialogEx::OnOK();
}

void CBuildingControlDlg::CtrlManager()
{
	// Enable/disable Ground Level edit box based on checkbox
	GetDlgItem(IDC_BC_GROUND_LEVEL_EDIT)->EnableWindow(m_bUseGroundLevel);
	
	// Enable/disable Bedrock Level edit box based on checkbox
	GetDlgItem(IDC_BC_BEDROCK_LEVEL_EDIT)->EnableWindow(m_bConsiderUndergroundSeismic);
	
	// Enable/disable Story Center controls based on Eccentricity Ratio checkbox
	GetDlgItem(IDC_BC_USE_MASS_RADIO)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_USE_AXIAL_FORCE_RADIO)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_USE_SHEAR_FORCE_RADIO)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_LOAD_CASE_COMBO)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_SCALE_FACTOR_EDIT)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_LOAD_CASE_LIST)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_ADD_BUTTON)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_MODIFY_BUTTON)->EnableWindow(m_bEccentricityRatio);
	GetDlgItem(IDC_BC_DELETE_BUTTON)->EnableWindow(m_bEccentricityRatio);
	
	// Enable/disable Story Response controls based on checkbox
	GetDlgItem(IDC_BC_STORY_CENTER_RADIO)->EnableWindow(m_bStoryResponseTimeHistory);
	GetDlgItem(IDC_BC_STORY_AVERAGE_RADIO)->EnableWindow(m_bStoryResponseTimeHistory);
}

void CBuildingControlDlg::OnUseGroundLevel()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnConsiderUndergroundSeismic()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnConsiderMassBelowGround()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnEccentricityRatio()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnStoryCenterType()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnStoryResponseTimeHistory()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnStoryResponseType()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	// Add load case to list
	if (!m_strLoadCase.IsEmpty())
	{
		CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_BC_LOAD_CASE_LIST);
		if (pListCtrl)
		{
			int nIndex = pListCtrl->GetItemCount();
			pListCtrl->InsertItem(nIndex, m_strLoadCase);
			
			CString strScale;
			strScale.Format(_T("%.2f"), m_dScaleFactor);
			pListCtrl->SetItemText(nIndex, 1, strScale);
		}
	}
}

void CBuildingControlDlg::OnBnClickedModify()
{
	UpdateData(TRUE);
	// Modify selected load case in list
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_BC_LOAD_CASE_LIST);
	if (pListCtrl)
	{
		int nSelected = pListCtrl->GetNextItem(-1, LVNI_SELECTED);
		if (nSelected >= 0)
		{
			pListCtrl->SetItemText(nSelected, 0, m_strLoadCase);
			
			CString strScale;
			strScale.Format(_T("%.2f"), m_dScaleFactor);
			pListCtrl->SetItemText(nSelected, 1, strScale);
		}
	}
}

void CBuildingControlDlg::OnBnClickedDelete()
{
	// Delete selected load case from list
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_BC_LOAD_CASE_LIST);
	if (pListCtrl)
	{
		int nSelected = pListCtrl->GetNextItem(-1, LVNI_SELECTED);
		if (nSelected >= 0)
		{
			pListCtrl->DeleteItem(nSelected);
		}
	}
}

void CBuildingControlDlg::OnBnClickedXDirectionalButton()
{
	// Handle X-Directional button click
	// This would typically open a selection dialog
}

void CBuildingControlDlg::OnBnClickedYDirectionalButton()
{
	// Handle Y-Directional button click
	// This would typically open a selection dialog
}