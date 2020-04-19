
// WirtualnaKam.h: główny plik nagłówkowy aplikacji WirtualnaKam
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // główne symbole


// CWirtualnaKamApp:
// Aby uzyskać implementację klasy, zobacz WirtualnaKam.cpp
//

class CWirtualnaKamApp : public CWinAppEx
{
public:
	CWirtualnaKamApp() noexcept;


// Przesłania
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementacja
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWirtualnaKamApp theApp;
