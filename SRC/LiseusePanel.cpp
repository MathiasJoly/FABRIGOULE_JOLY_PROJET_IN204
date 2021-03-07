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

	imageWidth = 657;
	imageHeight = 850;

	imageRGB->Rescale(imageWidth, imageHeight, wxIMAGE_QUALITY_BICUBIC);
	wxImage tempImage = imageRGB->Copy();

	return tempImage;
}

void LiseusePanel::SaveImage(wxString fileName)
{
	bool b ;

	wxMemoryDC mdc(imageBitmap);

	wxFont* font = new wxFont(wxFontInfo(8));
	mdc.SetFont(*font);

	mdc.DrawBitmap(imageBitmap, 0, 0);
	for (int i=0; i < annotations.size(); i++) 
	{
		// Afficher les annotations
		mdc.DrawText(annotations.at(i).note,annotations.at(i).pt.x-5,annotations.at(i).pt.y-15);
	};

	wxImage tempImage = imageBitmap.ConvertToImage();
	b = tempImage.SaveFile(fileName) ;

	if(!b)
		wxMessageBox(wxT("A problem occured during saving"));
}

void LiseusePanel::BestSize()
{
	SetSize(imageWidth, imageHeight) ;	// ideal size for canvas
	GetParent()->SetClientSize(GetSize());	// force the main frame to show the whole canvas
}

void LiseusePanel::LoadPagesVector(std::vector<wxImage> vector) 
{
	pagesVector = vector;
}

void LiseusePanel::OnPaint(wxPaintEvent &WXUNUSED(event))
// update the main window content. Appelé avec Refresh()
{

	wxPaintDC dc(this);
	DoPrepareDC(dc);
	wxFont* font = new wxFont(wxFontInfo(8));
	dc.SetFont(*font);
	if (imageRGB)
	{
		for (int i=0; i < pagesVector.size(); i++) 
		{
			// Afficher les images
			imageBitmap = wxBitmap(pagesVector.at(i), -1); 
			dc.DrawBitmap(imageBitmap, i*(imageWidth), 0);
		};
		for (int i=0; i < annotations.size(); i++) 
		{
			// Afficher les annotations
			dc.DrawText(annotations.at(i).note,annotations.at(i).pt.x-5,annotations.at(i).pt.y-15);
		};
	};
}


void LiseusePanel::OnClick(wxMouseEvent& event)
{
	if (!event.RightUp()) event.Skip();
	else if (imageRGB)
	{
		*cursor = event.GetPosition() + this->GetViewStart();
		int i = 0;
		int a_x, a_y;  //coordonnées de début de l'annotation
		int a_l;  //longueur de l'annotation
		int marge_b, marge_h, marge_d, marge_g; //encadrement de l'annotation
		int c_x = cursor->x;
		int c_y = cursor->y;
		bool undo = false;
		while (i < annotations.size() && !undo)
		{
			a_x = annotations.at(i).pt.x;
			a_y = annotations.at(i).pt.y;
			a_l = annotations.at(i).note.Length();
			undo = (c_x >= a_x-10) && (c_x <= a_x + a_l*5) && (c_y >= a_y-15) && (c_y <= a_y+5);
			i++;
		}
		if (undo) 
		{
			wxString s = annotations.at(i-1).note;
			wxString *choices = new wxString();
			wxSingleChoiceDialog dlg1(this,_T("Voulez-vous supprimmer cette annotation?"),s,0,choices);
			if ( dlg1.ShowModal() == wxID_OK ) annotations.erase(annotations.begin()+i-1);	
		}			
		else 
		{
			wxTextEntryDialog dlg2(this,_T("Ecrivez votre annotation!"),_T("Annotation :"));
			if ( dlg2.ShowModal() == wxID_OK )
			{
				// We can be certain that this string contains letters only.
				wxString value = dlg2.GetValue();
				if (!value.IsSameAs("")) Annoter(value,*cursor);
			};
		};
		Refresh();
	};
}

void LiseusePanel::OnMouseCaptureLost(wxMouseCaptureLostEvent& event)
{
        event.Skip();
}

void LiseusePanel::Annoter(wxString myNote, wxPoint myPt)
{
	Annotation temp_annotation = {.note = myNote, .pt = myPt};
	annotations.push_back(temp_annotation);
}


#endif
