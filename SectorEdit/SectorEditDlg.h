
// SectorEditDlg.h : header file
//

#pragma once
#include "MBR.h"

// CSectorEditDlg dialog
class CSectorEditDlg : public CDialog
{
// Construction
public:
	CSectorEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SECTOREDIT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

private:
	CEdit		m_EditDesPath;
	CEdit		m_EditSourcePath;
	TCHAR		m_szDesFilePath[MAX_PATH];
	TCHAR		m_szSourceFilePath[MAX_PATH];
	CMBR		m_MBR;

	CButton		m_ButnBrowseSource;
	CButton		m_RadioDisk;
	CButton		m_RadioFile;
	CComboBox	m_ComboBoxDisk;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButnBrowseDes();
	afx_msg void OnBnClickedButnBrowseSource();
	afx_msg void OnBnClickedButnRead();
	afx_msg void OnBnClickedButnWrite();
	afx_msg void OnBnClickedRadioDisk();
	afx_msg void OnBnClickedRadioFile();
	afx_msg void OnCbnSelchangeComboDisk();
};
