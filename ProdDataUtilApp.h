#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <wx/wx.h>

class ProdDataUtilApp : public wxApp
{
public:
	bool OnInit() override;

	int OnExit() override;
};

DECLARE_APP(ProdDataUtilApp)