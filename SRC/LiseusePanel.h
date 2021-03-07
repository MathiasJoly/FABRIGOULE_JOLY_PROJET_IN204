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
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/mimetype.h>
#include <wx/utils.h>
#include <vector>

#include "LiseuseApp.h"

enum
{
    ID_QUIT = 1,
    ID_ABOUT = 2,
    ID_LOAD = 3,
    ID_NOTE = 4,
    ID_SAVE = 5,
    ID_BEST_SIZE = 7,
    ID_OPEN = 8,
    ID_OPEN_RECENT = 9,
    ID_SYNC_SETTING = 10,
    ID_ZOOM = 11,
    ID_DISPLAY = 12,
    ID_PDF = 13,
};

class LiseusePanel: public wxScrolled<wxPanel>
{
public:
    LiseusePanel( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
    ~LiseusePanel() ;
	wxImage LoadImage(wxString fileName) ;
	void SaveImage(wxString fileName) ;
	void PrintPDF(wxString fileName,wxString mimeType) ;
	void BestSize() ;
	void Annoter(wxString note, wxPoint pt) ;
	void Undo(wxImage copie);
	void OnClick(wxMouseEvent& event) ;
	void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
  void LoadPagesVector(std::vector<wxImage> vector);
	wxPoint *cursor;
  std::vector<wxImage> pagesVector;

private:
	int imageWidth ;
	int imageHeight ;
	wxBitmap imageBitmap ;		// used to display the image
	wxImage *imageRGB ;		// used to load the image

	void OnPaint(wxPaintEvent &event) ;

	DECLARE_EVENT_TABLE()
};

#endif
