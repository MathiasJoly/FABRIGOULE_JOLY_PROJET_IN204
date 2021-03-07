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
#include <wx/editlbox.h>
#include <wx/arrstr.h>
#include <wx/string.h>
#include <wx/listctrl.h>

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
    ID_ORDER = 14,
};

struct Annotation {
  wxString note;
  wxPoint pt;
};

struct Files {
  wxArrayString names;
  wxArrayString paths;

  wxString findPath(wxString fileName) {
    for (int i=0; i<names.GetCount(); i++) {
      if (fileName == names.Item(i))
        return paths.Item(i);
    }
      std::cout << "No such a file in opened pages" << "\n";
      return ("");
  }
};

class LiseusePanel: public wxScrolled<wxPanel>
{
public:
    LiseusePanel( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
    ~LiseusePanel() ;
  void LoadImages(wxArrayString filesPaths);
	void SaveImage(wxString filePath) ;
	void BestSize() ;
	void Annoter(wxString note, wxPoint pt) ;
	void OnRightClick(wxMouseEvent& event);
  void OnListboxLDown(wxMouseEvent& event);
  void OnMouseDown(wxMouseEvent & event);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
	void LoadPagesVector(std::vector<wxImage> vector);

	wxImage LoadImage(wxString fileName) ;
	wxPoint *cursor;
  std::vector<wxImage> pagesVector;
  wxEditableListBox* pagesOrderList;
  unsigned int nbPages;
  unsigned int pageWidth;
  unsigned int pageHeight;


private:
	int imageWidth ;
	int imageHeight ;
	wxBitmap imageBitmap ;		// used to display the image
	wxImage *imageRGB ;		// used to load the image
  std::vector<Annotation> annotations;
  wxArrayString pagesArray;
  wxArrayString pagesArrayNew;
  Files files;


  void UpdatePagesVector();
	void OnPaint(wxPaintEvent &event);
  void OnPaint();

	DECLARE_EVENT_TABLE()
};

#endif
