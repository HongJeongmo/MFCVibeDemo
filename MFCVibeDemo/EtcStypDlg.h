#pragma once
#include "Resource.h"

// CEtcStypDlg dialog
class CEtcStypDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEtcStypDlg)

public:
	CEtcStypDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEtcStypDlg() {}

// Dialog Data
	enum { IDD = IDD_ETC_STYP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	// Dialog control variables
	int		m_nStructType;
	int   	m_nMassType;
	int		m_nStructureMass;
	BOOL  	m_bConsiderOffset;
	BOOL  	m_bConvertSelfWeight;
	BOOL	m_bAlignBeam;
	BOOL	m_bAlignSlab;
	BOOL	m_bConsiderRotMPF;

protected:
	void InitDialogData();
	void CtrlManager();

	// Message handlers
	afx_msg void OnEtcPcMassType();
	afx_msg void OnEtcPcStructMass();
	afx_msg void OnEtcPcSelfWeight();
	afx_msg void OnEtcPcConsiderOffset();
};
