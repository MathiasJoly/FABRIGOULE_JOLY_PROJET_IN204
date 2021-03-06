#ifndef LISEUSEPANEL_H
#define LISEUSEPANEL_H

#include <wx/image.h>
#include <wx/file.h>
#include <wx/bitmap.h>
#include <wx/scrolwin.h>
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dcmemory.h>

#include "LiseuseApp.h"
#include <list>
#include <cstdlib>
#include <cstdio>
#include <vector>

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

class LiseusePanel: public wxScrolled<wxPanel>
{
public:
  LiseusePanel( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
  ~LiseusePanel() ;
	void LoadImages(wxArrayString filesPaths) ;
	void SaveImage(wxString fileName) ;
	void ProcessImage() ;
	void BestSize() ;

private:
	int imageWidth ;
	int imageHeight ;
  int pageWidth ;
	int pageHeight ;
	wxBitmap imageBitmap ;		// used to display the image
	wxImage *imageRGB ;		// used to load the image
	unsigned char* myImage ;	// used to process the image

  std::list<wxBitmap> imagesBitmap ;		// used to display the image
	std::list<wxImage> *imagesRGB ;		// used to load the image
	std::vector<unsigned char*> myImages;	// used to process the image
  unsigned int nbPage;


	void OnPaint(wxPaintEvent &event) ;

	DECLARE_EVENT_TABLE()
};

#endif
