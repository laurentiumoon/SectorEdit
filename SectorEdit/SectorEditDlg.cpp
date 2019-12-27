<<<<<<< HEAD

// SectorEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SectorEdit.h"
#include "SectorEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSectorEditDlg dialog




CSectorEditDlg::CSectorEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSectorEditDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSectorEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT_DES_PATH,m_EditDesPath);
	DDX_Control(pDX,IDC_EDIT_SOURCE_PATH,m_EditSourcePath);
	DDX_Control(pDX,IDC_RADIO_DISK,m_RadioDisk);
	DDX_Control(pDX,IDC_RADIO_FILE,m_RadioFile);
	DDX_Control(pDX,IDC_COMBO_DISK,m_ComboBoxDisk);
	DDX_Control(pDX,IDC_BUTN_BROWSE_SOURCE,m_ButnBrowseSource);
}

BEGIN_MESSAGE_MAP(CSectorEditDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTN_BROWSE_DES, &CSectorEditDlg::OnBnClickedButnBrowseDes)
	ON_BN_CLICKED(IDC_BUTN_BROWSE_SOURCE, &CSectorEditDlg::OnBnClickedButnBrowseSource)
	ON_BN_CLICKED(IDC_BUTN_READ, &CSectorEditDlg::OnBnClickedButnRead)
	ON_BN_CLICKED(IDC_BUTN_WRITE, &CSectorEditDlg::OnBnClickedButnWrite)
	ON_BN_CLICKED(IDC_RADIO_DISK, &CSectorEditDlg::OnBnClickedRadioDisk)
	ON_BN_CLICKED(IDC_RADIO_FILE, &CSectorEditDlg::OnBnClickedRadioFile)
	ON_CBN_SELCHANGE(IDC_COMBO_DISK, &CSectorEditDlg::OnCbnSelchangeComboDisk)
END_MESSAGE_MAP()


// CSectorEditDlg message handlers

BOOL CSectorEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CWnd*	lpWnd = NULL;

	lpWnd = GetDlgItem(IDC_BUTN_READ);
	lpWnd->EnableWindow(FALSE);
	lpWnd = GetDlgItem(IDC_BUTN_WRITE);
	lpWnd->EnableWindow(FALSE);

	m_EditSourcePath.EnableWindow(FALSE);
	m_ButnBrowseSource.EnableWindow(FALSE);

	m_RadioDisk.EnableWindow(FALSE);
	m_RadioFile.EnableWindow(FALSE);
	m_ComboBoxDisk.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSectorEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSectorEditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSectorEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSectorEditDlg::OnBnClickedButnBrowseDes()
{
	TCHAR			szFilePath[MAX_PATH] = {0};
	OPENFILENAME	ofn = {0};
	BOOL	bRet;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner	= m_hWnd;
	ofn.hInstance	= theApp.m_hInstance;
	ofn.lpstrFilter = _T("MBR File(*.mbr)\0*.mbr\0\0");
	ofn.lpstrFile	= szFilePath;
	ofn.nMaxFile	= MAX_PATH;
	ofn.Flags		= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

	bRet = GetOpenFileName(&ofn);
	if (bRet)
	{
		m_EditDesPath.SetWindowText(szFilePath);
		lstrcpy(m_szDesFilePath,szFilePath);

		CWnd*	lpWnd = NULL;

		lpWnd = GetDlgItem(IDC_BUTN_READ);
		lpWnd->EnableWindow(TRUE);
		lpWnd = GetDlgItem(IDC_BUTN_WRITE);
		lpWnd->EnableWindow(TRUE);

		m_RadioDisk.EnableWindow();
		m_RadioFile.EnableWindow();
		m_ComboBoxDisk.EnableWindow();

		m_RadioDisk.SetCheck(BST_CHECKED);

		m_MBR.SetDiskType(TRUE,0,NULL);

	}
}

void CSectorEditDlg::OnBnClickedButnBrowseSource()
{
	TCHAR			szFilePath[MAX_PATH] = {0};
	OPENFILENAME	ofn = {0};
	BOOL	bRet;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner	= m_hWnd;
	ofn.hInstance	= theApp.m_hInstance;
	ofn.lpstrFilter = _T("All File(*.*)\0*.*\0\0");
	ofn.lpstrFile	= szFilePath;
	ofn.nMaxFile	= MAX_PATH;
	ofn.Flags		= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

	bRet = GetOpenFileName(&ofn);
	if (bRet)
	{
		m_EditSourcePath.SetWindowText(szFilePath);
		lstrcpy(m_szSourceFilePath,szFilePath);

		CWnd*	lpWnd = NULL;

		lpWnd = GetDlgItem(IDC_BUTN_READ);
		lpWnd->EnableWindow(TRUE);
		lpWnd = GetDlgItem(IDC_BUTN_WRITE);
		lpWnd->EnableWindow(TRUE);

		m_RadioDisk.EnableWindow();
		m_RadioFile.EnableWindow();
		m_ComboBoxDisk.EnableWindow();

		m_MBR.SetDiskType(FALSE,-1,m_szSourceFilePath);

	}
}

void CSectorEditDlg::OnBnClickedButnRead()
{
	char	szMBR[SECTOR_SIZE]	= {0};
	TCHAR	szText[MAX_PATH]	= {0};
	TCHAR	szTitle[MAX_PATH]	= {0};

	HANDLE	hFileMBR = NULL;
	DWORD	dwWrited = 0;

	lstrcpy(szTitle,_T("Read MBR"));

	if (m_MBR.ReadMBR((LPBYTE)szMBR))
	{
		hFileMBR = CreateFile(m_szDesFilePath,GENERIC_WRITE | GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_ALWAYS,0,NULL);
		if (hFileMBR != INVALID_HANDLE_VALUE)
		{
			if (WriteFile(hFileMBR,szMBR,SECTOR_SIZE,&dwWrited,NULL))
			{
				lstrcpy(szText,_T("Read MBR successed"));
			}
			else
			{
				lstrcpy(szText,_T("Read MBR failed"));
			}
			CloseHandle(hFileMBR);
		}
	}
	else
	{
		lstrcpy(szText,_T("Read MBR failed"));
	}

	MessageBox(szText,szTitle,MB_OK);
}

void CSectorEditDlg::OnBnClickedButnWrite()
{
	BYTE	szMBR[MBR_SIZE] = {0};
	TCHAR	szText[MAX_PATH] = {0};
	TCHAR	szTitle[MAX_PATH]= {0};

	HANDLE	hFileMBR = NULL;
	DWORD	dwReaded = 0;

	hFileMBR = CreateFile(m_szDesFilePath,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if (hFileMBR != INVALID_HANDLE_VALUE)
	{
		if (ReadFile(hFileMBR,szMBR,MBR_SIZE,&dwReaded,NULL))
		{
			lstrcpy(szTitle,_T("Write MBR"));

			if (m_MBR.WriteMBR(szMBR))
			{
				lstrcpy(szText,_T("Write MBR successed"));
			}
			else
			{
				lstrcpy(szText,_T("Write MBR failed"));
			}
		}
		else
		{
			lstrcpy(szText,_T("read file failed"));
		}
		CloseHandle(hFileMBR);
	}
	else
	{
		lstrcpy(szText,_T("open file failed"));
	}

	MessageBox(szText,szTitle,MB_OK);
}

void CSectorEditDlg::OnBnClickedRadioDisk()
{
	if (m_RadioDisk.GetCheck() == BST_CHECKED)
	{
		m_ComboBoxDisk.EnableWindow();

		m_EditSourcePath.EnableWindow(FALSE);
		m_ButnBrowseSource.EnableWindow(FALSE);
		//m_MBR.SetDiskType(TRUE,m_ComboBoxDisk.GetCurSel(),NULL);
		m_MBR.SetDiskType(TRUE,0,NULL);
	}
	else
	{
		m_ComboBoxDisk.EnableWindow(FALSE);
		m_EditSourcePath.EnableWindow(TRUE);
		m_ButnBrowseSource.EnableWindow(TRUE);
		//m_MBR.SetDiskType(FALSE,-1,m_szSourceFilePath);
	}
}

void CSectorEditDlg::OnBnClickedRadioFile()
{
	if (m_RadioDisk.GetCheck() == BST_CHECKED)
	{
		m_ComboBoxDisk.EnableWindow();

		m_EditSourcePath.EnableWindow(FALSE);
		m_ButnBrowseSource.EnableWindow(FALSE);

		//m_MBR.SetDiskType(TRUE,m_ComboBoxDisk.GetCurSel(),NULL);
		m_MBR.SetDiskType(TRUE,0,NULL);

	}
	else
	{
		m_ComboBoxDisk.EnableWindow(FALSE);

		m_EditSourcePath.EnableWindow(TRUE);
		m_ButnBrowseSource.EnableWindow(TRUE);

		//m_MBR.SetDiskType(FALSE,-1,m_szSourceFilePath);
	}
}

void CSectorEditDlg::OnCbnSelchangeComboDisk()
{
	// TODO: Add your control notification handler code here
}
=======

// SectorEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SectorEdit.h"
#include "SectorEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSectorEditDlg dialog




CSectorEditDlg::CSectorEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSectorEditDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSectorEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT_DES_PATH,m_EditDesPath);
	DDX_Control(pDX,IDC_EDIT_SOURCE_PATH,m_EditSourcePath);
	DDX_Control(pDX,IDC_RADIO_DISK,m_RadioDisk);
	DDX_Control(pDX,IDC_RADIO_FILE,m_RadioFile);
	DDX_Control(pDX,IDC_COMBO_DISK,m_ComboBoxDisk);
	DDX_Control(pDX,IDC_BUTN_BROWSE_SOURCE,m_ButnBrowseSource);
}

BEGIN_MESSAGE_MAP(CSectorEditDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTN_BROWSE_DES, &CSectorEditDlg::OnBnClickedButnBrowseDes)
	ON_BN_CLICKED(IDC_BUTN_BROWSE_SOURCE, &CSectorEditDlg::OnBnClickedButnBrowseSource)
	ON_BN_CLICKED(IDC_BUTN_READ, &CSectorEditDlg::OnBnClickedButnRead)
	ON_BN_CLICKED(IDC_BUTN_WRITE, &CSectorEditDlg::OnBnClickedButnWrite)
	ON_BN_CLICKED(IDC_RADIO_DISK, &CSectorEditDlg::OnBnClickedRadioDisk)
	ON_BN_CLICKED(IDC_RADIO_FILE, &CSectorEditDlg::OnBnClickedRadioFile)
	ON_CBN_SELCHANGE(IDC_COMBO_DISK, &CSectorEditDlg::OnCbnSelchangeComboDisk)
END_MESSAGE_MAP()


// CSectorEditDlg message handlers

BOOL CSectorEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CWnd*	lpWnd = NULL;

	lpWnd = GetDlgItem(IDC_BUTN_READ);
	lpWnd->EnableWindow(FALSE);
	lpWnd = GetDlgItem(IDC_BUTN_WRITE);
	lpWnd->EnableWindow(FALSE);

	m_EditSourcePath.EnableWindow(FALSE);
	m_ButnBrowseSource.EnableWindow(FALSE);

	m_RadioDisk.EnableWindow(FALSE);
	m_RadioFile.EnableWindow(FALSE);
	m_ComboBoxDisk.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSectorEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSectorEditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSectorEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSectorEditDlg::OnBnClickedButnBrowseDes()
{
	TCHAR			szFilePath[MAX_PATH] = {0};
	OPENFILENAME	ofn = {0};
	BOOL	bRet;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner	= m_hWnd;
	ofn.hInstance	= theApp.m_hInstance;
	ofn.lpstrFilter = _T("MBR File(*.mbr)\0*.mbr\0\0");
	ofn.lpstrFile	= szFilePath;
	ofn.nMaxFile	= MAX_PATH;
	ofn.Flags		= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

	bRet = GetOpenFileName(&ofn);
	if (bRet)
	{
		m_EditDesPath.SetWindowText(szFilePath);
		lstrcpy(m_szDesFilePath,szFilePath);

		CWnd*	lpWnd = NULL;

		lpWnd = GetDlgItem(IDC_BUTN_READ);
		lpWnd->EnableWindow(TRUE);
		lpWnd = GetDlgItem(IDC_BUTN_WRITE);
		lpWnd->EnableWindow(TRUE);

		m_RadioDisk.EnableWindow();
		m_RadioFile.EnableWindow();
		m_ComboBoxDisk.EnableWindow();

		m_RadioDisk.SetCheck(BST_CHECKED);

		m_MBR.SetDiskType(TRUE,0,NULL);

	}
}

void CSectorEditDlg::OnBnClickedButnBrowseSource()
{
	TCHAR			szFilePath[MAX_PATH] = {0};
	OPENFILENAME	ofn = {0};
	BOOL	bRet;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner	= m_hWnd;
	ofn.hInstance	= theApp.m_hInstance;
	ofn.lpstrFilter = _T("All File(*.*)\0*.*\0\0");
	ofn.lpstrFile	= szFilePath;
	ofn.nMaxFile	= MAX_PATH;
	ofn.Flags		= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

	bRet = GetOpenFileName(&ofn);
	if (bRet)
	{
		m_EditSourcePath.SetWindowText(szFilePath);
		lstrcpy(m_szSourceFilePath,szFilePath);

		CWnd*	lpWnd = NULL;

		lpWnd = GetDlgItem(IDC_BUTN_READ);
		lpWnd->EnableWindow(TRUE);
		lpWnd = GetDlgItem(IDC_BUTN_WRITE);
		lpWnd->EnableWindow(TRUE);

		m_RadioDisk.EnableWindow();
		m_RadioFile.EnableWindow();
		m_ComboBoxDisk.EnableWindow();

		m_MBR.SetDiskType(FALSE,-1,m_szSourceFilePath);

	}
}

void CSectorEditDlg::OnBnClickedButnRead()
{
	char	szMBR[SECTOR_SIZE]	= {0};
	TCHAR	szText[MAX_PATH]	= {0};
	TCHAR	szTitle[MAX_PATH]	= {0};

	HANDLE	hFileMBR = NULL;
	DWORD	dwWrited = 0;

	lstrcpy(szTitle,_T("Read MBR"));

	if (m_MBR.ReadMBR((LPBYTE)szMBR))
	{
		hFileMBR = CreateFile(m_szDesFilePath,GENERIC_WRITE | GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_ALWAYS,0,NULL);
		if (hFileMBR != INVALID_HANDLE_VALUE)
		{
			if (WriteFile(hFileMBR,szMBR,SECTOR_SIZE,&dwWrited,NULL))
			{
				lstrcpy(szText,_T("Read MBR successed"));
			}
			else
			{
				lstrcpy(szText,_T("Read MBR failed"));
			}
			CloseHandle(hFileMBR);
		}
	}
	else
	{
		lstrcpy(szText,_T("Read MBR failed"));
	}

	MessageBox(szText,szTitle,MB_OK);
}

void CSectorEditDlg::OnBnClickedButnWrite()
{
	BYTE	szMBR[MBR_SIZE] = {0};
	TCHAR	szText[MAX_PATH] = {0};
	TCHAR	szTitle[MAX_PATH]= {0};

	HANDLE	hFileMBR = NULL;
	DWORD	dwReaded = 0;

	hFileMBR = CreateFile(m_szDesFilePath,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if (hFileMBR != INVALID_HANDLE_VALUE)
	{
		if (ReadFile(hFileMBR,szMBR,MBR_SIZE,&dwReaded,NULL))
		{
			lstrcpy(szTitle,_T("Write MBR"));

			if (m_MBR.WriteMBR(szMBR))
			{
				lstrcpy(szText,_T("Write MBR successed"));
			}
			else
			{
				lstrcpy(szText,_T("Write MBR failed"));
			}
		}
		else
		{
			lstrcpy(szText,_T("read file failed"));
		}
		CloseHandle(hFileMBR);
	}
	else
	{
		lstrcpy(szText,_T("open file failed"));
	}

	MessageBox(szText,szTitle,MB_OK);
}

void CSectorEditDlg::OnBnClickedRadioDisk()
{
	if (m_RadioDisk.GetCheck() == BST_CHECKED)
	{
		m_ComboBoxDisk.EnableWindow();

		m_EditSourcePath.EnableWindow(FALSE);
		m_ButnBrowseSource.EnableWindow(FALSE);
		//m_MBR.SetDiskType(TRUE,m_ComboBoxDisk.GetCurSel(),NULL);
		m_MBR.SetDiskType(TRUE,0,NULL);
	}
	else
	{
		m_ComboBoxDisk.EnableWindow(FALSE);
		m_EditSourcePath.EnableWindow(TRUE);
		m_ButnBrowseSource.EnableWindow(TRUE);
		//m_MBR.SetDiskType(FALSE,-1,m_szSourceFilePath);
	}
}

void CSectorEditDlg::OnBnClickedRadioFile()
{
	if (m_RadioDisk.GetCheck() == BST_CHECKED)
	{
		m_ComboBoxDisk.EnableWindow();

		m_EditSourcePath.EnableWindow(FALSE);
		m_ButnBrowseSource.EnableWindow(FALSE);

		//m_MBR.SetDiskType(TRUE,m_ComboBoxDisk.GetCurSel(),NULL);
		m_MBR.SetDiskType(TRUE,0,NULL);

	}
	else
	{
		m_ComboBoxDisk.EnableWindow(FALSE);

		m_EditSourcePath.EnableWindow(TRUE);
		m_ButnBrowseSource.EnableWindow(TRUE);

		//m_MBR.SetDiskType(FALSE,-1,m_szSourceFilePath);
	}
}

void CSectorEditDlg::OnCbnSelchangeComboDisk()
{
	// TODO: Add your control notification handler code here
}
>>>>>>> 5cfdcd7747275a2841092697d64542eefa1d1814
