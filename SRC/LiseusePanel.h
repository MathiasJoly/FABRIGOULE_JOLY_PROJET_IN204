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
    ID_SMALL = 15,
    ID_MEDIUM = 16,
    ID_LARGE = 17,
    ID_EXTRA_LARGE = 18,
};

struct Annotation {
  wxString note;
  wxPoint pt;
  unsigned int pageNumber;
};

struct File {
	wxString name;
	wxString path;
	unsigned int pageNumber;
};

struct Files {
	std::vector<File> vector;

	wxString FindName(int num) {
  	for (int i=0; i<vector.size(); i++) {
  		if (num == vector[i].pageNumber)
  		return vector[i].name;
  		}
  	return ("");
  };

	wxString FindPath(wxString fileName) {
  	for (int i=0; i<vector.size(); i++) {
  		if (fileName == vector[i].name)
  		return vector[i].path;
  		}
  	std::cout << "No such a file in opened pages" << "\n";
  	return ("");
	};

	void GetNames(wxArrayString* names) {
    *names = {};
  	for (int i=0; i<vector.size(); i++) {
  		(*names).Add(vector[i].name);
  		};
	};

	wxArrayString GetPaths(wxArrayString* paths) {
    *paths = {};
    std::cout << "vector size" <<vector.size() <<"\n";
    for (int i=0; i<vector.size(); i++) {
      std::cout << "check in GetPaths : "<<i<<"\n";
  		(*paths).Add(vector[i].path);
  		};
	};

	void SetPageNumber(wxString fileName, int num) {
  	bool succes = false;
  	for (int i=0; i<vector.size(); i++) {
  		succes = fileName == vector[i].name ;
  		if (succes) vector[i].pageNumber = num ;
  		};
  	if (!succes) std::cout << "No such a file in opened pages" << "\n";
	};

  void ChangePagePosition(unsigned int pageNb, wxArrayString pagesArrayNew, wxArrayString pagesArray) {
    std::cout << "ChangePagePosition is called\n";
    if (pagesArrayNew.GetCount() < pagesArray.GetCount()) {
      std::cout << "Case Delete : file pageNumber was " << vector.at(pageNb).pageNumber << "\n";
			    --(vector.at(pageNb).pageNumber);// == (vector.at(i).pageNumber - 1);
      std::cout << "Case Delete : file pageNumber is " << vector.at(pageNb).pageNumber << "\n";
  		}
  	else {
      for (int i=0; i < vector.size(); i++) {
        std::cout << "Case Swap : file pageNumber was " << vector.at(i).pageNumber << "\n";
        if (vector.at(i).pageNumber == pageNb)
          vector.at(i).pageNumber = pageNb+1;
        else if (vector.at(i).pageNumber == pageNb+1)
          vector.at(i).pageNumber = pageNb;
        std::cout << "Case Swap : file pageNumber is " << vector.at(i).pageNumber << "\n";
      };
    };
  };
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
    void ChangeAnnotationsPlacements(unsigned int PageNumber);

  	wxPoint *cursor;
    bool imagesLoaded;
    std::vector<wxImage> pagesVector;
    wxEditableListBox* pagesOrderList;
    unsigned int nbPages;
    unsigned int pageWidth;
    unsigned int pageHeight;
    wxArrayString pagesArray;
    Files files;


  private:
  	int imageWidth ;
  	int imageHeight ;
  	wxBitmap imageBitmap ;		// used to display the image
  	wxImage *imageRGB ;		// used to load the image
    std::vector<Annotation> annotations;
    wxArrayString pagesArrayNew;


    void UpdatePagesVector();
  	void OnPaint(wxPaintEvent &event);
    void OnPaint();

  	DECLARE_EVENT_TABLE()
};

#endif
