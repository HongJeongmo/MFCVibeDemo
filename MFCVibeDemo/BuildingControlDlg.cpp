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
	, m_bConsiderUnderground(FALSE)
	, m_bConsiderMass(FALSE)
	, m_bStoryShearForce(TRUE)
	, m_bConsiderWindSeismic(TRUE)
	, m_bEccentricity(FALSE)
	, m_nStoryCenterType(0)
	, m_bStoryResponse(FALSE)
	, m_bStoryDrift(FALSE)
	, m_strGroundLevel(_T("0"))
	, m_strBedrockLevel(_T("0"))
	, m_strScaleFactor(_T("1"))
	, m_nLoadCase(0)
	, m_nXLoadCase(0)
	, m_nYLoadCase(0)
	, m_nStoryResponseType(0)
{
}

void CBuildingControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_BC_USE_GROUND_LEVEL_CHK, m_bUseGroundLevel);
	DDX_Text(pDX, IDC_BC_GROUND_LEVEL_EDIT, m_strGroundLevel);
	DDX_Check(pDX, IDC_BC_CONSIDER_UNDERGROUND_CHK, m_bConsiderUnderground);
	DDX_Text(pDX, IDC_BC_BEDROCK_LEVEL_EDIT, m_strBedrockLevel);
	DDX_Check(pDX, IDC_BC_CONSIDER_MASS_CHK, m_bConsiderMass);
	DDX_Check(pDX, IDC_BC_STORY_SHEAR_FORCE_CHK, m_bStoryShearForce);
	DDX_Check(pDX, IDC_BC_CONSIDER_WIND_SEISMIC_CHK, m_bConsiderWindSeismic);
	DDX_Check(pDX, IDC_BC_ECCENTRICITY_CHK, m_bEccentricity);
	DDX_Radio(pDX, IDC_BC_USE_MASS_RADIO, m_nStoryCenterType);
	DDX_Text(pDX, IDC_BC_SCALE_FACTOR_EDIT, m_strScaleFactor);
	DDX_CBIndex(pDX, IDC_BC_LOAD_CASE_COMBO, m_nLoadCase);
	DDX_CBIndex(pDX, IDC_BC_X_LOAD_CASE_COMBO, m_nXLoadCase);
	DDX_CBIndex(pDX, IDC_BC_Y_LOAD_CASE_COMBO, m_nYLoadCase);
	DDX_Check(pDX, IDC_BC_STORY_RESPONSE_CHK, m_bStoryResponse);
	DDX_Radio(pDX, IDC_BC_STORY_CENTER_RADIO, m_nStoryResponseType);
	DDX_Check(pDX, IDC_BC_STORY_DRIFT_CHK, m_bStoryDrift);
}

BEGIN_MESSAGE_MAP(CBuildingControlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BC_USE_GROUND_LEVEL_CHK, &CBuildingControlDlg::OnUseGroundLevel)
	ON_BN_CLICKED(IDC_BC_CONSIDER_UNDERGROUND_CHK, &CBuildingControlDlg::OnConsiderUnderground)
	ON_BN_CLICKED(IDC_BC_CONSIDER_MASS_CHK, &CBuildingControlDlg::OnConsiderMass)
	ON_BN_CLICKED(IDC_BC_STORY_SHEAR_FORCE_CHK, &CBuildingControlDlg::OnStoryShearForce)
	ON_BN_CLICKED(IDC_BC_CONSIDER_WIND_SEISMIC_CHK, &CBuildingControlDlg::OnConsiderWindSeismic)
	ON_BN_CLICKED(IDC_BC_ECCENTRICITY_CHK, &CBuildingControlDlg::OnEccentricity)
	ON_BN_CLICKED(IDC_BC_USE_MASS_RADIO, &CBuildingControlDlg::OnStoryCenterType)
	ON_BN_CLICKED(IDC_BC_USE_AXIAL_FORCE_RADIO, &CBuildingControlDlg::OnStoryCenterType)
	ON_BN_CLICKED(IDC_BC_USE_SHEAR_FORCE_RADIO, &CBuildingControlDlg::OnStoryCenterType)
	ON_BN_CLICKED(IDC_BC_STORY_CENTER_RADIO, &CBuildingControlDlg::OnStoryResponse)
	ON_BN_CLICKED(IDC_BC_STORY_AVERAGE_RADIO, &CBuildingControlDlg::OnStoryResponse)
	ON_BN_CLICKED(IDC_BC_STORY_RESPONSE_CHK, &CBuildingControlDlg::OnStoryResponse)
	ON_BN_CLICKED(IDC_BC_STORY_DRIFT_CHK, &CBuildingControlDlg::OnStoryDrift)
	ON_BN_CLICKED(IDC_BC_ADD_BTN, &CBuildingControlDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BC_MODIFY_BTN, &CBuildingControlDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_BC_DELETE_BTN, &CBuildingControlDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BC_LOAD_CASE_BTN, &CBuildingControlDlg::OnBnClickedLoadCaseBtn)
	ON_BN_CLICKED(IDC_BC_X_LOAD_CASE_BTN, &CBuildingControlDlg::OnBnClickedXLoadCaseBtn)
	ON_BN_CLICKED(IDC_BC_Y_LOAD_CASE_BTN, &CBuildingControlDlg::OnBnClickedYLoadCaseBtn)
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
	// Initialize ground level and bedrock level unit labels
	GetDlgItem(IDC_BC_GROUND_LEVEL_UNIT)->SetWindowText(_T("m"));
	GetDlgItem(IDC_BC_BEDROCK_LEVEL_UNIT)->SetWindowText(_T("m"));
	
	// Initialize load case combo boxes with sample data
	CComboBox* pLoadCaseCombo = (CComboBox*)GetDlgItem(IDC_BC_LOAD_CASE_COMBO);
	if (pLoadCaseCombo)
	{
		pLoadCaseCombo->AddString(_T("Load Case 1"));
		pLoadCaseCombo->AddString(_T("Load Case 2"));
		pLoadCaseCombo->AddString(_T("Load Case 3"));
		pLoadCaseCombo->SetCurSel(0);
	}
	
	CComboBox* pXLoadCaseCombo = (CComboBox*)GetDlgItem(IDC_BC_X_LOAD_CASE_COMBO);
	if (pXLoadCaseCombo)
	{
		pXLoadCaseCombo->AddString(_T("X Load Case 1"));
		pXLoadCaseCombo->AddString(_T("X Load Case 2"));
		pXLoadCaseCombo->SetCurSel(0);
	}
	
	CComboBox* pYLoadCaseCombo = (CComboBox*)GetDlgItem(IDC_BC_Y_LOAD_CASE_COMBO);
	if (pYLoadCaseCombo)
	{
		pYLoadCaseCombo->AddString(_T("Y Load Case 1"));
		pYLoadCaseCombo->AddString(_T("Y Load Case 2"));
		pYLoadCaseCombo->SetCurSel(0);
	}
	
	// Initialize load case list
	UpdateLoadCaseList();
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
	// Enable/disable Ground Level edit based on checkbox
	GetDlgItem(IDC_BC_GROUND_LEVEL_EDIT)->EnableWindow(m_bUseGroundLevel);
	GetDlgItem(IDC_BC_GROUND_LEVEL_UNIT)->EnableWindow(m_bUseGroundLevel);
	
	// Enable/disable Bedrock Level edit based on underground checkbox
	GetDlgItem(IDC_BC_BEDROCK_LEVEL_EDIT)->EnableWindow(m_bConsiderUnderground);
	GetDlgItem(IDC_BC_BEDROCK_LEVEL_UNIT)->EnableWindow(m_bConsiderUnderground);
	
	// Enable/disable Story Center options based on eccentricity checkbox
	GetDlgItem(IDC_BC_USE_MASS_RADIO)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_USE_AXIAL_FORCE_RADIO)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_USE_SHEAR_FORCE_RADIO)->EnableWindow(m_bEccentricity);
	
	// Enable/disable load case controls based on eccentricity
	GetDlgItem(IDC_BC_LOAD_CASE_COMBO)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_LOAD_CASE_BTN)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_SCALE_FACTOR_EDIT)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_LOAD_CASE_LIST)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_ADD_BTN)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_MODIFY_BTN)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_DELETE_BTN)->EnableWindow(m_bEccentricity);
	
	// Enable/disable Story Stiffness Center options based on eccentricity
	GetDlgItem(IDC_BC_X_LOAD_CASE_COMBO)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_X_LOAD_CASE_BTN)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_Y_LOAD_CASE_COMBO)->EnableWindow(m_bEccentricity);
	GetDlgItem(IDC_BC_Y_LOAD_CASE_BTN)->EnableWindow(m_bEccentricity);
	
	// Enable/disable Story Response radio buttons based on checkbox
	GetDlgItem(IDC_BC_STORY_CENTER_RADIO)->EnableWindow(m_bStoryResponse);
	GetDlgItem(IDC_BC_STORY_AVERAGE_RADIO)->EnableWindow(m_bStoryResponse);
}

void CBuildingControlDlg::UpdateLoadCaseList()
{
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_BC_LOAD_CASE_LIST);
	if (pListCtrl)
	{
		// Setup list control columns
		pListCtrl->DeleteAllItems();
		while (pListCtrl->DeleteColumn(0));
		
		// Set list control style
		pListCtrl->SetExtendedStyle(pListCtrl->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		
		pListCtrl->InsertColumn(0, _T("Load Case"), LVCFMT_LEFT, 120);
		pListCtrl->InsertColumn(1, _T("Scale"), LVCFMT_LEFT, 60);
		
		// Add sample data
		int nItem = pListCtrl->InsertItem(0, _T("Sample Load Case"));
		pListCtrl->SetItemText(nItem, 1, _T("1.0"));
	}
}

void CBuildingControlDlg::OnUseGroundLevel()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnConsiderUnderground()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnConsiderMass()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnStoryShearForce()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnConsiderWindSeismic()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnEccentricity()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnStoryCenterType()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnStoryResponse()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnStoryDrift()
{
	UpdateData(TRUE);
	CtrlManager();
}

void CBuildingControlDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	
	// Add new load case to list
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_BC_LOAD_CASE_LIST);
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_BC_LOAD_CASE_COMBO);
	
	if (pListCtrl && pCombo)
	{
		CString strLoadCase;
		pCombo->GetWindowText(strLoadCase);
		
		int nItem = pListCtrl->InsertItem(pListCtrl->GetItemCount(), strLoadCase);
		pListCtrl->SetItemText(nItem, 1, m_strScaleFactor);
	}
}

void CBuildingControlDlg::OnBnClickedModify()
{
	UpdateData(TRUE);
	
	// Modify selected load case in list
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_BC_LOAD_CASE_LIST);
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_BC_LOAD_CASE_COMBO);
	
	if (pListCtrl && pCombo)
	{
		int nSelected = pListCtrl->GetNextItem(-1, LVNI_SELECTED);
		if (nSelected >= 0)
		{
			CString strLoadCase;
			pCombo->GetWindowText(strLoadCase);
			
			pListCtrl->SetItemText(nSelected, 0, strLoadCase);
			pListCtrl->SetItemText(nSelected, 1, m_strScaleFactor);
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

void CBuildingControlDlg::OnBnClickedLoadCaseBtn()
{
	// Open load case selection dialog
	// TODO: Implement load case selection dialog
	AfxMessageBox(_T("Load Case selection dialog will be implemented here"));
}

void CBuildingControlDlg::OnBnClickedXLoadCaseBtn()
{
	// Open X-directional load case selection dialog
	// TODO: Implement load case selection dialog
	AfxMessageBox(_T("X-Directional Load Case selection dialog will be implemented here"));
}

void CBuildingControlDlg::OnBnClickedYLoadCaseBtn()
{
	// Open Y-directional load case selection dialog
	// TODO: Implement load case selection dialog
	AfxMessageBox(_T("Y-Directional Load Case selection dialog will be implemented here"));
}