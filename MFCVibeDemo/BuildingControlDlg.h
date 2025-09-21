#pragma once
#include "Resource.h"

// CBuildingControlDlg dialog
class CBuildingControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBuildingControlDlg)

public:
	CBuildingControlDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CBuildingControlDlg() {}

// Dialog Data
	enum { IDD = IDD_BUILDING_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	// Dialog control variables
	BOOL	m_bUseGroundLevel;
	BOOL	m_bConsiderUnderground;
	BOOL	m_bConsiderMass;
	BOOL	m_bStoryShearForce;
	BOOL	m_bConsiderWindSeismic;
	BOOL	m_bEccentricity;
	int		m_nStoryCenterType;  // 0: Use Mass, 1: Use Axial Force, 2: Use Shear Force
	BOOL	m_bStoryResponse;    // Changed from int to BOOL
	BOOL	m_bStoryDrift;
	CString	m_strGroundLevel;
	CString	m_strBedrockLevel;
	CString	m_strScaleFactor;
	int		m_nLoadCase;
	int		m_nXLoadCase;
	int		m_nYLoadCase;
	int		m_nStoryResponseType; // 0: Story Center, 1: Story Average

protected:
	void InitDialogData();
	void CtrlManager();
	void UpdateLoadCaseList();

	// Message handlers
	afx_msg void OnUseGroundLevel();
	afx_msg void OnConsiderUnderground();
	afx_msg void OnConsiderMass();
	afx_msg void OnStoryShearForce();
	afx_msg void OnConsiderWindSeismic();
	afx_msg void OnEccentricity();
	afx_msg void OnStoryCenterType();
	afx_msg void OnStoryResponse();
	afx_msg void OnStoryDrift();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedLoadCaseBtn();
	afx_msg void OnBnClickedXLoadCaseBtn();
	afx_msg void OnBnClickedYLoadCaseBtn();
};