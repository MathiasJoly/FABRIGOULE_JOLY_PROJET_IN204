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
	annotations = {};
//	this->SetScrollRate(20,20);
	this->SetScrollbars(20,20,100,100);
	this->ShowScrollbars(wxSHOW_SB_ALWAYS,wxSHOW_SB_DEFAULT);
	cursor = new wxPoint(0,0);
	annotations.resize(0);
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

void LiseusePanel::PrintPDF(wxString fileName,wxString mimeType)
{
	/*
	wxFileTypeInfo ftInfo = new wxFileTypeInfo(mimeType);
	wxFileType ft = new wxFileType(ftInfo);
	wxString* command = new wxString();
	bool succes = ft.GetPrintCommand(command,
	*/
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
		for (int i=0; i < pagesVector.size(); i++) {
			imageBitmap = wxBitmap(pagesVector.at(i), -1); // ...to get the corresponding bitmap

			dc.DrawBitmap(imageBitmap, i*(imageWidth+10), 0);
		}
		for (int i=0; i < annotations.size(); i++) {
			dc.DrawText(annotations.at(i).note,annotations.at(i).pt.x-5,annotations.at(i).pt.y-15);
		}
	}
}


void LiseusePanel::OnClick(wxMouseEvent& event)
{
	if (!event.RightUp()) event.Skip();
	else if (imageRGB)
	{
		wxImage copieRGB = imageRGB->Copy();
		*cursor = event.GetPosition() + this->GetViewStart();
		wxTextEntryDialog dlg(this,_T("Ecrivez votre annotation!"),_T("Annotation :"));
		if ( dlg.ShowModal() == wxID_OK )
		{
			// We can be certain that this string contains letters only.
			wxString value = dlg.GetValue();
			Annoter(value,*cursor);
			Undo(copieRGB);
		};
	};
}

void LiseusePanel::OnMouseCaptureLost(wxMouseCaptureLostEvent& event)
{
        event.Skip();
}

void LiseusePanel::Undo(wxImage copie)
{
	wxTextEntryDialog dlg(this,_T("Cette annotation vous convient-elle ?"),_T("Verification :"));
	if ( dlg.ShowModal() == wxID_OK )
	{
		wxString reponse = dlg.GetValue();
		bool convenable = reponse.IsSameAs("OUI") | reponse.IsSameAs("Oui") | reponse.IsSameAs("oui") | reponse.IsSameAs("O") | reponse.IsSameAs("o") |
					reponse.IsSameAs("YES") | reponse.IsSameAs("Yes") | reponse.IsSameAs("yes") | reponse.IsSameAs("Y") | reponse.IsSameAs("y") ;
		if ( !convenable )
		{
			*imageRGB = copie;
			Refresh();
		};
	};
}

void LiseusePanel::Annoter(wxString myNote, wxPoint myPt)
{
	std::cout<< "Annoter is called" << "\n";
	Annotation temp_annotation = {.note = myNote, .pt = myPt};
	annotations.push_back(temp_annotation);
	std::cout<<"annotations list is of size : " << annotations.size() << "\n";

/*
		imageBitmap = wxBitmap(*imageRGB, -1); // ...to get the corresponding bitmap

		wxMemoryDC mdc(imageBitmap);
		DoPrepareDC(mdc); // le scroll ne déforme plus l'image

		wxFont* font = new wxFont(wxFontInfo(6));
		mdc.SetFont(*font);

		mdc.DrawBitmap(imageBitmap, 0, 0);

		mdc.DrawText(note,pt.x-5,pt.y-8);

		*imageRGB = imageBitmap.ConvertToImage();
*/
		Refresh(false);
}


#endif
