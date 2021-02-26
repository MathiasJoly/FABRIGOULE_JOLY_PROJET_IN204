#ifndef _LISEUSEAPP_CPP_
#define _LISEUSEAPP_CPP_

#include "LiseuseApp.h"
#include "LiseuseFrame.h"

IMPLEMENT_APP(LiseuseApp);

bool LiseuseApp::OnInit()
{
    wxInitAllImageHandlers() ;

    LiseuseFrame* frame = new LiseuseFrame(_T(APP_NAME), wxDefaultPosition, wxSize(400,300)) ;
    frame->Show(true) ;
    SetTopWindow(frame) ;
    return true ;
}

#endif
