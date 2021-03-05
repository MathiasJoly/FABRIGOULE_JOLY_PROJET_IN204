#ifndef LISEUSEPANEL_H
#define LISEUSEPANEL_H

#include <memory>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>

#include "LiseuseApp.h"

enum
{
    ID_QUIT = 1,
    ID_ABOUT = 2,
    ID_LOAD = 3,
    ID_SAVE = 4,
    ID_PROCESS = 5,
    ID_BEST_SIZE = 6,
    ID_OPEN = 7,
    ID_OPEN_RECENT = 8,
    ID_SYNC_SETTING = 9,
    ID_ZOOM = 10,
    ID_DISPLAY = 11
};

class LiseusePanel: public wxScrolled<wxPanel>
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
