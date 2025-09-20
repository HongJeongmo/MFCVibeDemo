#pragma once
#include "afxdialogex.h"

// CBuildingControlDlg 대화 상자

class CBuildingControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBuildingControlDlg)

public:
	CBuildingControlDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBuildingControlDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUILDING_CONTROL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	// Control variables
	BOOL m_bUseGroundLevel;
	double m_dGroundLevel;
	BOOL m_bConsiderUnderground;
	double m_dBedrockLevel;
	BOOL m_bConsiderMassBelow;
	BOOL m_bStoryShearForce;
	BOOL m_bConsiderWindSeismic;
	BOOL m_bEccentricityRatio;
	int m_nStoryCenterType; // 0: Use Mass, 1: Use Axial Force, 2: Use Shear Force
	CString m_strLoadCase;
	double m_dScaleFactor;
	CString m_strXDirectionalLoadCase;
	CString m_strYDirectionalLoadCase;
	BOOL m_bStoryResponse;
	int m_nStoryResponseType; // 0: Story Center, 1: Story Average
	BOOL m_bStoryDrift;

	// Control objects
	CButton m_chkUseGroundLevel;
	CEdit m_editGroundLevel;
	CButton m_chkConsiderUnderground;
	CEdit m_editBedrockLevel;
	CButton m_chkConsiderMassBelow;
	CButton m_chkStoryShearForce;
	CButton m_chkConsiderWindSeismic;
	CButton m_chkEccentricityRatio;
	CButton m_radioUseMass;
	CButton m_radioUseAxialForce;
	CButton m_radioUseShearForce;
	CComboBox m_comboLoadCase;
	CEdit m_editScaleFactor;
	CListCtrl m_listLoadCase;
	CComboBox m_comboXDirectional;
	CComboBox m_comboYDirectional;
	CButton m_chkStoryResponse;
	CButton m_radioStoryCenter;
	CButton m_radioStoryAverage;
	CButton m_chkStoryDrift;

	// Message handlers
	afx_msg void OnBnClickedChkUseGroundLevel();
	afx_msg void OnBnClickedChkConsiderUnderground();
	afx_msg void OnBnClickedChkStoryResponse();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnLoadCaseSelect();
	afx_msg void OnBnClickedBtnXDirectionalSelect();
	afx_msg void OnBnClickedBtnYDirectionalSelect();

private:
	void UpdateControlStates();
	void InitializeControls();
	void InitializeListControl();
};