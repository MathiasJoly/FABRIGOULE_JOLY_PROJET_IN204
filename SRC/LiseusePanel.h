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
#include <iostream>
#include <fstream>

#include "LiseuseApp.h"

enum
{
    ID_QUIT = 1,
    ID_ABOUT = 2,
    ID_NEW = 3,
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
    ID_WRITE_FILE = 15
};

struct Annotation {
  wxString note;
  wxPoint pt;
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
	}

	wxString FindPath(wxString fileName) {
	for (int i=0; i<vector.size(); i++) {
		if (fileName == vector[i].name)
		return vector[i].path;
		}
	std::cout << "No such a file in opened pages" << "\n";
	return ("");
	}

	void GetNames(wxArrayString* names) {
	for (int i=0; i<vector.size(); i++) {
		(*names).Add(vector[i].name);
		};
	}

	void GetPaths(wxArrayString* paths) {
	for (int i=0; i<vector.size(); i++) {
		(*paths).Add(vector[i].path);
		};
	}

	void SetPageNumber(wxString fileName, int num) {
	bool succes = false;
	for (int i=0; i<vector.size(); i++) {
		succes = fileName == vector[i].name ;
		if (succes) vector[i].pageNumber = num ;
		};
	if (!succes) std::cout << "No such a file in opened pages" << "\n";
	}
	
};

class LiseusePanel: public wxScrolled<wxPanel>
{
public:
    LiseusePanel( wxWindow *parent, wxWindowID, const wxPoint &pos, const wxSize &size ) ;
    ~LiseusePanel() ;
  	void NewImages(wxArrayString filesPaths);
	void OpenImages(std::string Nom);
	void SaveImage(wxString filePath) ;
	void BestSize() ;
	void Annoter(wxString note, wxPoint pt) ;
	void WriteFile(std::string Nom);
	void OnRightClick(wxMouseEvent& event);
  void OnListboxLDown(wxMouseEvent& event);
  void OnMouseDown(wxMouseEvent & event);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
//	void LoadPagesVector(std::vector<wxImage> vector);

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

  void SetPosition(const wxPoint& position);
  void UpdatePagesVector();
	void OnPaint(wxPaintEvent &event);
  void OnPaint();

	DECLARE_EVENT_TABLE()
};

#endif
