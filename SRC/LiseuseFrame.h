#ifndef LISEUSEFRAME_H
#define LISEUSEFRAME_H

#include "LiseuseApp.h"
#include "LiseusePanel.h"

class LiseuseFrame: public wxFrame
{
public:
	LiseuseFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

protected:
	void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSyncSetting(wxCommandEvent& event);
	void OnZoom(wxCommandEvent& event);
	void OnDisplay(wxCommandEvent& event);
	void OnBestSize(wxCommandEvent& WXUNUSED(event)) ;
	void OnOpenImage(wxCommandEvent& WXUNUSED(event) ) ;
	void OnSaveImage(wxCommandEvent & WXUNUSED(event)) ;
	void OnProcessImage(wxCommandEvent& WXUNUSED(event) ) ;
	void OnClose(wxCloseEvent& event) ;

        LiseusePanel *panel; // the canvas inside the main frame
	bool imageLoaded ;
	DECLARE_EVENT_TABLE()
};

#endif
