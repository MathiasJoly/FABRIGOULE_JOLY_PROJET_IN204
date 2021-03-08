#ifndef LISEUSEFRAME_H
#define LISEUSEFRAME_H

#include "LiseuseApp.h"
#include "LiseusePanel.h"
#include <wx/filedlg.h>
#include <vector>

class LiseuseFrame: public wxFrame
{
public:
	LiseuseFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	LiseusePanel *panel; // the canvas inside the main frame
	wxArrayString filesPaths;
	void OnListboxLDown(wxMouseEvent & event);

protected:
	void OnQuit(wxCommandEvent& event);
	void OnOrder(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSyncSetting(wxCommandEvent& event);
	void OnZoom(wxCommandEvent& event);
	void OnDisplay(wxCommandEvent& event);
	void OnBestSize(wxCommandEvent& WXUNUSED(event));
	void OnSmall(wxCommandEvent& WXUNUSED(event));
	void OnMedium(wxCommandEvent& WXUNUSED(event));
	void OnLarge(wxCommandEvent& WXUNUSED(event));
	void OnExtraLarge(wxCommandEvent& WXUNUSED(event));
	void OnOpenImage(wxCommandEvent& WXUNUSED(event) ) ;
	void OnSaveImage(wxCommandEvent & WXUNUSED(event)) ;
	void OnClose(wxCloseEvent& event) ;
	void ResizePanel(wxSizeEvent& event);

	wxImage tempImage;
	std::vector<wxImage> pagesVector;
	bool imageLoaded;
	bool orderShown;

	DECLARE_EVENT_TABLE()
};

#endif
