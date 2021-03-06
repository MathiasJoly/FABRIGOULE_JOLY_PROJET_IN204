#ifndef _LISEUSEPANEL_CPP_
#define _LISEUSEPANEL_CPP_

#include "LiseusePanel.h"


BEGIN_EVENT_TABLE(LiseusePanel, wxPanel)
	EVT_PAINT(LiseusePanel::OnPaint)
END_EVENT_TABLE()

LiseusePanel::LiseusePanel( wxWindow *parent, wxWindowID id,const wxPoint &pos, const wxSize &size ): wxScrolled<wxPanel>(parent, id)
{
	myImage=NULL;
	imageRGB = NULL;
//	this->SetScrollRate(20,20);
	this->SetScrollbars(1,1,100,100);
	this->ShowScrollbars(wxSHOW_SB_ALWAYS,wxSHOW_SB_DEFAULT);
}

LiseusePanel::~LiseusePanel()
{
	if (myImage)
		free(myImage) ;
	if (imageRGB)
		delete imageRGB ;
}

void LiseusePanel::LoadImage(wxString fileName)
{
	if (myImage)
		free (myImage) ;
	if (imageRGB)
		delete imageRGB ;

	// open image dialog box
	imageRGB = new wxImage(fileName, wxBITMAP_TYPE_ANY, -1);
	// ANY => can load many image formats
	imageBitmap = wxBitmap(*imageRGB, -1); // ...to get the corresponding bitmap

	imageWidth = imageRGB->GetWidth() ;
	imageHeight = imageRGB->GetHeight() ;


	this->SetScrollbars(1,1,imageWidth,imageHeight,0,0);

	myImage = (unsigned char*)malloc(imageWidth * imageHeight * 3) ;
	memcpy(myImage, imageRGB->GetData(), imageWidth * imageHeight * 3) ;

// update GUI size
	SetSize(imageWidth, imageHeight) ;
	GetParent()->SetClientSize(GetSize()) ;

// update display
	Refresh(false) ;
}

void LiseusePanel::SaveImage(wxString fileName)
{
	bool b ;

	wxImage* tempImage = new wxImage(imageWidth, imageHeight, myImage, true);
	// lend my image buffer...
	b = tempImage->SaveFile(fileName) ;
	delete(tempImage) ;		// buffer not needed any more

	if(!b)
		wxMessageBox(wxT("A problem occured during saving"));
}

void LiseusePanel::ProcessImage()
// example of fast and trivial process (negative)
// you can replace it with your own
// you can also use methods from the wxImage class itself
{
	long int i = imageWidth*imageHeight*3 ;

// myImage is a monodimentional vector of pixels (RGBRGB...)
	while (i--)
		myImage[i] = 255 - myImage[i] ;

	Refresh(false); // update display
}

void LiseusePanel::BestSize()
{
	SetSize(imageWidth, imageHeight) ;	// ideal size for canvas
	GetParent()->SetClientSize(GetSize());	// force the main frame to show the whole canvas
}

void LiseusePanel::OnPaint(wxPaintEvent &WXUNUSED(event))
// update the main window content
{
	wxImage* tempImage;  // the bridge between my image buffer and the bitmap to display

	wxPaintDC dc(this);
	DoPrepareDC(dc);

//	this->Refresh();
	//this->Update();

	if (myImage)
	{
		tempImage = new wxImage(imageWidth, imageHeight, myImage, true);
		// lend my image buffer...
		imageBitmap = wxBitmap(*tempImage, -1); // ...to get the corresponding bitmap
		delete(tempImage) ;		// buffer not needed any more

//		dc.Clear();
		dc.DrawBitmap(imageBitmap, 0, 0);
		dc.DrawBitmap(imageBitmap, imageWidth+10, 0);

		//dc.SelectObject(imageBitmap);
		//dc.SetTextForeground(255,255,0);
		wxString text("Test Annotation");
		dc.DrawText(text,80,5);
	};
}

#endif
