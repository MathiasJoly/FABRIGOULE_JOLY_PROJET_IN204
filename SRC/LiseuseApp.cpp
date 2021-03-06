#ifndef _LISEUSEAPP_CPP_
#define _LISEUSEAPP_CPP_

#include "LiseuseApp.h"
#include "LiseuseFrame.h"

IMPLEMENT_APP(LiseuseApp);

bool LiseuseApp::OnInit()
{
    wxInitAllImageHandlers();
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    LiseuseFrame* frame = new LiseuseFrame(_T(APP_NAME), wxDefaultPosition, wxSize(400,300));
//    sizer->Add(frame->panel, 1, wxALL | wxEXPAND, 120);
//    frame->SetSizer(sizer);

    frame->Show(true) ;
    SetTopWindow(frame) ;
//    wxDisplay display(wxDisplay::GetFromWindow(pointertoyourframe));
//    wxRect screen = display.GetClientArea();
    return true ;
}

#endif
