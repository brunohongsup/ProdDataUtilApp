#pragma once
#include <wx/msw/frame.h>
#include "ProdDataUtilApp.h"
#include "ProdDataUtilFrame.h"

enum
{
    ID_Hello = 1
};

class ProdDataUtilFrame : public wxFrame
{
public:
    ProdDataUtilFrame();

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
