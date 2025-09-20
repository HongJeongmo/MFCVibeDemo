#include "pch.h"
#include "MFCVibeDemo.h"
#include "BuildingControlDlg.h"
#include "afxdialogex.h"

// CBuildingControlDlg 대화 상자

IMPLEMENT_DYNAMIC(CBuildingControlDlg, CDialogEx)

CBuildingControlDlg::CBuildingControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BUILDING_CONTROL_DIALOG, pParent)
	, m_bUseGroundLevel(FALSE)
	, m_dGroundLevel(0.0)
	, m_bConsiderUnderground(FALSE)
	, m_dBedrockLevel(0.0)
	, m_bConsiderMassBelow(FALSE)
	, m_bStoryShearForce(TRUE)
	, m_bConsiderWindSeismic(TRUE)
	, m_bEccentricityRatio(FALSE)
	, m_nStoryCenterType(0)
	, m_strLoadCase(_T(""))
	, m_dScaleFactor(1.0)
	, m_strXDirectionalLoadCase(_T(""))
	, m_strYDirectionalLoadCase(_T(""))
	, m_bStoryResponse(FALSE)
	, m_nStoryResponseType(0)
	, m_bStoryDrift(FALSE)
{
}

CBuildingControlDlg::~CBuildingControlDlg()
{
}

void CBuildingControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	// Data exchange for variables
	DDX_Check(pDX, IDC_CHK_USE_GROUND_LEVEL, m_bUseGroundLevel);
	DDX_Text(pDX, IDC_EDIT_GROUND_LEVEL, m_dGroundLevel);
	DDX_Check(pDX, IDC_CHK_CONSIDER_UNDERGROUND, m_bConsiderUnderground);
	DDX_Text(pDX, IDC_EDIT_BEDROCK_LEVEL, m_dBedrockLevel);
	DDX_Check(pDX, IDC_CHK_CONSIDER_MASS_BELOW, m_bConsiderMassBelow);
	DDX_Check(pDX, IDC_CHK_STORY_SHEAR_FORCE, m_bStoryShearForce);
	DDX_Check(pDX, IDC_CHK_CONSIDER_WIND_SEISMIC, m_bConsiderWindSeismic);
	DDX_Check(pDX, IDC_CHK_ECCENTRICITY_RATIO, m_bEccentricityRatio);
	DDX_Radio(pDX, IDC_RADIO_USE_MASS, m_nStoryCenterType);
	DDX_CBString(pDX, IDC_COMBO_LOAD_CASE, m_strLoadCase);
	DDX_Text(pDX, IDC_EDIT_SCALE_FACTOR, m_dScaleFactor);
	DDX_CBString(pDX, IDC_COMBO_X_DIRECTIONAL, m_strXDirectionalLoadCase);
	DDX_CBString(pDX, IDC_COMBO_Y_DIRECTIONAL, m_strYDirectionalLoadCase);
	DDX_Check(pDX, IDC_CHK_STORY_RESPONSE, m_bStoryResponse);
	DDX_Radio(pDX, IDC_RADIO_STORY_CENTER, m_nStoryResponseType);
	DDX_Check(pDX, IDC_CHK_STORY_DRIFT, m_bStoryDrift);
	
	// Data exchange for controls
	DDX_Control(pDX, IDC_CHK_USE_GROUND_LEVEL, m_chkUseGroundLevel);
	DDX_Control(pDX, IDC_EDIT_GROUND_LEVEL, m_editGroundLevel);
	DDX_Control(pDX, IDC_CHK_CONSIDER_UNDERGROUND, m_chkConsiderUnderground);
	DDX_Control(pDX, IDC_EDIT_BEDROCK_LEVEL, m_editBedrockLevel);
	DDX_Control(pDX, IDC_CHK_CONSIDER_MASS_BELOW, m_chkConsiderMassBelow);
	DDX_Control(pDX, IDC_CHK_STORY_SHEAR_FORCE, m_chkStoryShearForce);
	DDX_Control(pDX, IDC_CHK_CONSIDER_WIND_SEISMIC, m_chkConsiderWindSeismic);
	DDX_Control(pDX, IDC_CHK_ECCENTRICITY_RATIO, m_chkEccentricityRatio);
	DDX_Control(pDX, IDC_RADIO_USE_MASS, m_radioUseMass);
	DDX_Control(pDX, IDC_RADIO_USE_AXIAL_FORCE, m_radioUseAxialForce);
	DDX_Control(pDX, IDC_RADIO_USE_SHEAR_FORCE, m_radioUseShearForce);
	DDX_Control(pDX, IDC_COMBO_LOAD_CASE, m_comboLoadCase);
	DDX_Control(pDX, IDC_EDIT_SCALE_FACTOR, m_editScaleFactor);
	DDX_Control(pDX, IDC_LIST_LOAD_CASE, m_listLoadCase);
	DDX_Control(pDX, IDC_COMBO_X_DIRECTIONAL, m_comboXDirectional);
	DDX_Control(pDX, IDC_COMBO_Y_DIRECTIONAL, m_comboYDirectional);
	DDX_Control(pDX, IDC_CHK_STORY_RESPONSE, m_chkStoryResponse);
	DDX_Control(pDX, IDC_RADIO_STORY_CENTER, m_radioStoryCenter);
	DDX_Control(pDX, IDC_RADIO_STORY_AVERAGE, m_radioStoryAverage);
	DDX_Control(pDX, IDC_CHK_STORY_DRIFT, m_chkStoryDrift);
}

BEGIN_MESSAGE_MAP(CBuildingControlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_USE_GROUND_LEVEL, &CBuildingControlDlg::OnBnClickedChkUseGroundLevel)
	ON_BN_CLICKED(IDC_CHK_CONSIDER_UNDERGROUND, &CBuildingControlDlg::OnBnClickedChkConsiderUnderground)
	ON_BN_CLICKED(IDC_CHK_STORY_RESPONSE, &CBuildingControlDlg::OnBnClickedChkStoryResponse)
	ON_BN_CLICKED(IDC_BTN_ADD, &CBuildingControlDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CBuildingControlDlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CBuildingControlDlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_LOAD_CASE_SELECT, &CBuildingControlDlg::OnBnClickedBtnLoadCaseSelect)
	ON_BN_CLICKED(IDC_BTN_X_DIRECTIONAL_SELECT, &CBuildingControlDlg::OnBnClickedBtnXDirectionalSelect)
	ON_BN_CLICKED(IDC_BTN_Y_DIRECTIONAL_SELECT, &CBuildingControlDlg::OnBnClickedBtnYDirectionalSelect)
END_MESSAGE_MAP()

// CBuildingControlDlg 메시지 처리기

BOOL CBuildingControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitializeControls();
	InitializeListControl();
	UpdateControlStates();

	return TRUE;
}

void CBuildingControlDlg::InitializeControls()
{
	// Initialize combo boxes with sample data
	m_comboLoadCase.AddString(_T("DL"));
	m_comboLoadCase.AddString(_T("LL"));
	m_comboLoadCase.AddString(_T("WL"));
	m_comboLoadCase.AddString(_T("EL"));
	m_comboLoadCase.SetCurSel(0);

	m_comboXDirectional.AddString(_T("DL"));
	m_comboXDirectional.AddString(_T("LL"));
	m_comboXDirectional.AddString(_T("WL"));
	m_comboXDirectional.AddString(_T("EL"));
	m_comboXDirectional.SetCurSel(0);

	m_comboYDirectional.AddString(_T("DL"));
	m_comboYDirectional.AddString(_T("LL"));
	m_comboYDirectional.AddString(_T("WL"));
	m_comboYDirectional.AddString(_T("EL"));
	m_comboYDirectional.SetCurSel(0);

	// Set default values
	m_editGroundLevel.SetWindowText(_T("0"));
	m_editBedrockLevel.SetWindowText(_T("0"));
	m_editScaleFactor.SetWindowText(_T("1"));

	// Set initial checkbox states
	m_chkStoryShearForce.SetCheck(BST_CHECKED);
	m_chkConsiderWindSeismic.SetCheck(BST_CHECKED);
	m_radioUseMass.SetCheck(BST_CHECKED);
	m_radioStoryCenter.SetCheck(BST_CHECKED);
}

void CBuildingControlDlg::InitializeListControl()
{
	// Set up list control columns
	CRect rect;
	m_listLoadCase.GetClientRect(&rect);
	int nColWidth = rect.Width() / 2;

	m_listLoadCase.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listLoadCase.InsertColumn(0, _T("Load Case"), LVCFMT_LEFT, nColWidth);
	m_listLoadCase.InsertColumn(1, _T("Scale"), LVCFMT_LEFT, nColWidth);
}

void CBuildingControlDlg::UpdateControlStates()
{
	UpdateData(TRUE);

	// Enable/disable ground level edit based on checkbox
	m_editGroundLevel.EnableWindow(m_bUseGroundLevel);

	// Enable/disable bedrock level edit based on checkbox
	m_editBedrockLevel.EnableWindow(m_bConsiderUnderground);

	// Enable/disable story response radio buttons based on checkbox
	m_radioStoryCenter.EnableWindow(m_bStoryResponse);
	m_radioStoryAverage.EnableWindow(m_bStoryResponse);
}

// Message handlers
void CBuildingControlDlg::OnBnClickedChkUseGroundLevel()
{
	UpdateControlStates();
}

void CBuildingControlDlg::OnBnClickedChkConsiderUnderground()
{
	UpdateControlStates();
}

void CBuildingControlDlg::OnBnClickedChkStoryResponse()
{
	UpdateControlStates();
}

void CBuildingControlDlg::OnBnClickedBtnAdd()
{
	UpdateData(TRUE);
	
	// Add selected load case and scale factor to list
	CString strLoadCase, strScale;
	m_comboLoadCase.GetWindowText(strLoadCase);
	m_editScaleFactor.GetWindowText(strScale);
	
	if (!strLoadCase.IsEmpty())
	{
		int nIndex = m_listLoadCase.GetItemCount();
		m_listLoadCase.InsertItem(nIndex, strLoadCase);
		m_listLoadCase.SetItemText(nIndex, 1, strScale);
	}
}

void CBuildingControlDlg::OnBnClickedBtnModify()
{
	int nSelected = m_listLoadCase.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected != -1)
	{
		UpdateData(TRUE);
		
		CString strLoadCase, strScale;
		m_comboLoadCase.GetWindowText(strLoadCase);
		m_editScaleFactor.GetWindowText(strScale);
		
		m_listLoadCase.SetItemText(nSelected, 0, strLoadCase);
		m_listLoadCase.SetItemText(nSelected, 1, strScale);
	}
}

void CBuildingControlDlg::OnBnClickedBtnDelete()
{
	int nSelected = m_listLoadCase.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected != -1)
	{
		m_listLoadCase.DeleteItem(nSelected);
	}
}

void CBuildingControlDlg::OnBnClickedBtnLoadCaseSelect()
{
	// TODO: Implement load case selection dialog
	AfxMessageBox(_T("Load case selection dialog not implemented yet."));
}

void CBuildingControlDlg::OnBnClickedBtnXDirectionalSelect()
{
	// TODO: Implement X-directional load case selection dialog
	AfxMessageBox(_T("X-directional load case selection dialog not implemented yet."));
}

void CBuildingControlDlg::OnBnClickedBtnYDirectionalSelect()
{
	// TODO: Implement Y-directional load case selection dialog
	AfxMessageBox(_T("Y-directional load case selection dialog not implemented yet."));
}