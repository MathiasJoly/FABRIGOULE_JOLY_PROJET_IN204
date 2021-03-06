#ifndef _LISEUSEPANEL_CPP_
#define _LISEUSEPANEL_CPP_

#include "LiseusePanel.h"


BEGIN_EVENT_TABLE(LiseusePanel, wxPanel)
	EVT_PAINT(LiseusePanel::OnPaint)
	EVT_MOUSE_EVENTS(LiseusePanel::OnClick)
	EVT_MOUSE_CAPTURE_LOST(LiseusePanel::OnMouseCaptureLost)
END_EVENT_TABLE()

LiseusePanel::LiseusePanel( wxWindow *parent, wxWindowID id,const wxPoint &pos, const wxSize &size ): wxScrolled<wxPanel>(parent, id)
{
	imageRGB = NULL;
//	this->SetScrollRate(20,20);
	this->SetScrollbars(20,20,100,100);
	this->ShowScrollbars(wxSHOW_SB_ALWAYS,wxSHOW_SB_DEFAULT);
	cursor = new wxPoint(0,0);
}

LiseusePanel::~LiseusePanel()
{
	if (imageRGB)
		delete imageRGB ;
}

wxImage LiseusePanel::LoadImage(wxString fileName)
{
	if (imageRGB)
		delete imageRGB;

	// open image dialog box
	imageRGB = new wxImage(fileName, wxBITMAP_TYPE_ANY, -1);
	// ANY => can load many image formats
//	imageWidth = imageRGB->GetWidth();
//	imageHeight = imageRGB->GetHeight();
	imageWidth = 657;
	imageHeight = 850;

	imageRGB->Rescale(imageWidth, imageHeight, wxIMAGE_QUALITY_BICUBIC);
	wxImage tempImage = imageRGB->Copy();

	return tempImage;
}

void LiseusePanel::SaveImage(wxString fileName)
{
	bool b ;

	unsigned char* myImage = (unsigned char*)malloc(imageWidth * imageHeight * 3) ;
	memcpy(myImage, imageRGB->GetData(), imageWidth * imageHeight * 3) ;

	wxImage* tempImage = new wxImage(imageWidth, imageHeight, myImage, true);
	// lend my image buffer...
	b = tempImage->SaveFile(fileName) ;
	delete(tempImage) ;		// buffer not needed any more
	free(myImage);

	if(!b)
		wxMessageBox(wxT("A problem occured during saving"));
}

void LiseusePanel::BestSize()
{
	SetSize(imageWidth, imageHeight) ;	// ideal size for canvas
	GetParent()->SetClientSize(GetSize());	// force the main frame to show the whole canvas
}

void LiseusePanel::LoadPagesVector(std::vector<wxImage> vector) {
	pagesVector = vector;
}

void LiseusePanel::OnPaint(wxPaintEvent &WXUNUSED(event))
// update the main window content
{

	wxPaintDC dc(this);
	DoPrepareDC(dc); // le scroll ne déforme plus l'image

	if (imageRGB)
	{
		std::cout << "imageRGB : " << imageRGB << " and pagesVector.at(0) : " << &(pagesVector.at(0))
																					 << " and pagesVector.at(3) : "
																					 << " and pagesVector.at(1) : " << &(pagesVector.at(1)) << "\n";
		for (int i=0; i < pagesVector.size(); i++) {
			imageBitmap = wxBitmap(pagesVector.at(i), -1); // ...to get the corresponding bitmap

			dc.DrawBitmap(imageBitmap, i*(imageWidth+10), 0);
		}
		//dc.DrawBitmap(imageBitmap, imageWidth+10, 0);

//		imageBitmap = wxBitmap(*(pagesVector.at(1)), -1);
//		dc.DrawBitmap(imageBitmap, 0, 0);

	};
}

void LiseusePanel::OnClick(wxMouseEvent& event)
{
	if (imageRGB) event.Skip();
	if (!event.RightUp()) event.Skip();
	else
	{
		*cursor = event.GetPosition();
		wxTextEntryDialog dlg(this,_T("Ecrivez votre annotation!"),_T("Annotation :"));
		if ( dlg.ShowModal() == wxID_OK )
		{
			// We can be certain that this string contains letters only.
			wxString value = dlg.GetValue();
			Annoter(value,*cursor);
		};
	};
}

void LiseusePanel::OnMouseCaptureLost(wxMouseCaptureLostEvent& event)
{
        event.Skip();
}

void LiseusePanel::Annoter(wxString note, wxPoint pt)
{

	if (imageRGB)
	{

		imageBitmap = wxBitmap(*imageRGB, -1); // ...to get the corresponding bitmap

		wxMemoryDC mdc(imageBitmap);
		DoPrepareDC(mdc); // le scroll ne déforme plus l'image

		wxFont* font = new wxFont(wxFontInfo(6));
		mdc.SetFont(*font);

		mdc.DrawBitmap(imageBitmap, 0, 0);

		mdc.DrawText(note,pt.x-5,pt.y-8);

		*imageRGB = imageBitmap.ConvertToImage();

		this->Refresh();
	};
}


#endif
