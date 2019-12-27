<<<<<<< HEAD

// SectorEdit.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSectorEditApp:
// See SectorEdit.cpp for the implementation of this class
//

class CSectorEditApp : public CWinAppEx
{
public:
	CSectorEditApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

=======

// SectorEdit.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSectorEditApp:
// See SectorEdit.cpp for the implementation of this class
//

class CSectorEditApp : public CWinAppEx
{
public:
	CSectorEditApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

>>>>>>> 5cfdcd7747275a2841092697d64542eefa1d1814
extern CSectorEditApp theApp;