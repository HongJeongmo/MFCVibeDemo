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
	double	m_dGroundLevel;
	BOOL	m_bConsiderUndergroundSeismic;
	double	m_dBedrockLevel;
	BOOL	m_bConsiderMassBelowGround;
	BOOL	m_bStoryShearForceRatio;
	BOOL	m_bConsiderWindSeismicLoads;
	BOOL	m_bEccentricityRatio;
	int		m_nStoryCenterType;  // 0: Use Mass, 1: Use Axial Force, 2: Use Shear Force
	CString	m_strLoadCase;
	double	m_dScaleFactor;
	CString	m_strXDirectionalLoadCase;
	CString	m_strYDirectionalLoadCase;
	BOOL	m_bStoryResponseTimeHistory;
	int		m_nStoryResponseType;  // 0: Story Center, 1: Story Average
	BOOL	m_bStoryDriftByMaxVertical;

protected:
	void InitDialogData();
	void CtrlManager();

	// Message handlers
	afx_msg void OnUseGroundLevel();
	afx_msg void OnConsiderUndergroundSeismic();
	afx_msg void OnConsiderMassBelowGround();
	afx_msg void OnEccentricityRatio();
	afx_msg void OnStoryCenterType();
	afx_msg void OnStoryResponseTimeHistory();
	afx_msg void OnStoryResponseType();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedXDirectionalButton();
	afx_msg void OnBnClickedYDirectionalButton();
};