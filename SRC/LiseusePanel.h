#ifndef LISEUSEPANEL_H
#define LISEUSEPANEL_H

#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>

#include "LiseuseApp.h"

enum
{
    ID_QUIT = 1,
    ID_ABOUT,
    ID_LOAD,
    ID_SAVE,
    ID_PROCESS,
    ID_BEST_SIZE,
    ID_OPEN = 1,
    ID_OPEN_RECENT = 1,
    ID_SYNC_SETTING = 1,
    ID_ZOOM = 1,
    ID_DISPLAY = 1
};

class LiseusePanel: public wxPanel
{
public:
    LiseusePanel( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
    ~LiseusePanel() ;
	void LoadImage(wxString fileName) ;
	void SaveImage(wxString fileName) ;
	void ProcessImage() ;
	void BestSize() ;

private:
	int imageWidth ;
	int imageHeight ;
	wxBitmap imageBitmap ;		// used to display the image
	wxImage *imageRGB ;		// used to load the image
	unsigned char* myImage ;	// used to process the image

	void OnPaint(wxPaintEvent &event) ;

	DECLARE_EVENT_TABLE()
};

#endif
