#ifndef _LISEUSEPANEL_CPP_
#define _LISEUSEPANEL_CPP_

#include "LiseusePanel.h"


BEGIN_EVENT_TABLE(LiseusePanel, wxPanel)
	EVT_PAINT(LiseusePanel::OnPaint)
END_EVENT_TABLE()

LiseusePanel::LiseusePanel( wxWindow *parent, wxWindowID id,const wxPoint &pos, const wxSize &size ): wxScrolled<wxPanel>(parent, id)
{
  nbPage = 0;
	myImage=NULL;
	imageRGB = NULL;
  pageWidth = 800;
  pageHeight = 950;
  std::list<wxBitmap> imagesBitmap = {};
  std::list<wxImage> imagesRGB = {};
  myImages = {};
//	this->SetScrollRate(20,20);
  SetSize(1300, 1000);
	GetParent()->SetClientSize(GetSize()) ;

	this->SetScrollbars(20,20,100,100);
	this->ShowScrollbars(wxSHOW_SB_ALWAYS,wxSHOW_SB_DEFAULT);
}

LiseusePanel::~LiseusePanel()
{
	if (myImage)
		free(myImage) ;
	if (imageRGB)
		delete imageRGB ;
}

void LiseusePanel::LoadImages(wxArrayString filesPaths)
{
	if (myImage)
		free (myImage) ;
	if (imageRGB)
		delete imageRGB ;

  nbPage = filesPaths.GetCount();
  std::cout << "nbPage = " << nbPage << "\n";

	// open image dialog box
  for (int i=0; i < nbPage; i++) {
    std::cout << "enter for loop in LoadImages. i = " << i << "\n";
    wxString fileName = filesPaths.Item(i);
    imageRGB = new wxImage(fileName, wxBITMAP_TYPE_ANY, -1);
    imageRGB->Rescale(pageWidth, pageHeight);
  	// ANY => can load many image formats
  	imageBitmap = wxBitmap(*imageRGB, -1); // ...to get the corresponding bitmap

    imagesRGB->resize(nbPage);
//    imagesRGB->push_back(*imageRGB);
    std::cout << "test" << "\n";
    imagesBitmap.push_back(imageBitmap);

  	imageWidth = imageRGB->GetWidth();
  	imageHeight = imageRGB->GetHeight();
    std::cout << imageWidth << "\n";
    myImage = (unsigned char*)malloc(pageWidth * pageHeight * 3);
    memcpy(myImage, imageRGB->GetData(), pageWidth * pageHeight * 3) ;
    myImages.push_back(myImage);
    std::cout << "myImages is of size : " << myImages.size() << "\n";
  }


// update GUI size
//	SetSize(1500, 1000);
//	GetParent()->SetClientSize(GetSize()) ;

  this->SetScrollbars(1,1,pageWidth*2,pageHeight,0,0);

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
	DoPrepareDC(dc); // le scroll ne déforme plus l'image

  std::cout << "OnPaint is called" << "\n";
	if (myImage)
	{
    for (int i=0; i < nbPage; i++) {
      tempImage = new wxImage(imageWidth, imageHeight, myImages.at(1), true);
  		// lend my image buffer...
  		imageBitmap = wxBitmap(*tempImage, -1); // ...to get the corresponding bitmap
  		delete(tempImage) ;		// buffer not needed any more
      dc.DrawBitmap(imageBitmap, i*(imageWidth+10), 0);
    }


		wxMemoryDC mdc(imageBitmap);
//		DoPrepareDC(mdc); // le scroll ne déforme plus l'image

//		dc.Clear();
//    for (int i = 0, i < filesPaths.GetCount(), i++) {
  //    dc.DrawBitmap(filesPaths.Item)
    //}
//		dc.DrawBitmap(imageBitmap, 0, 0);;
//  	DoPrepareDC(dc);
//		dc.DrawBitmap(imageBitmap, imageWidth+10, 0);

		//dc.SelectObject(imageBitmap);
		//dc.SetTextForeground(255,255,0);
		wxString text("Test Annotation");
		dc.DrawText(text,80,5);

		*imageRGB = imageBitmap.ConvertToImage();
		memcpy(myImage, imageRGB->GetData(), imageWidth * imageHeight * 3) ;
		//imageWidth = imageWidth;

	};
}

#endif
