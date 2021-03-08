#ifndef _LISEUSEPANEL_CPP_
#define _LISEUSEPANEL_CPP_

#include "LiseusePanel.h"


BEGIN_EVENT_TABLE(LiseusePanel, wxPanel)
	EVT_PAINT(LiseusePanel::OnPaint)
	EVT_RIGHT_DOWN(LiseusePanel::OnRightClick)
	EVT_LEFT_DOWN(LiseusePanel::OnListboxLDown)
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
	pageWidth = 618;
	pageHeight = 800;
	wxSize pagesOrderListSize = wxSize(700,150);
	wxPoint* pagesOrderListPos = new wxPoint(0,0);
	pagesOrderList = new wxEditableListBox(GetParent(), 50, "Pages order", *pagesOrderListPos, pagesOrderListSize, wxEL_ALLOW_DELETE);
}

LiseusePanel::~LiseusePanel()
{
	if (imageRGB)
		delete imageRGB ;
}

void LiseusePanel::LoadImages(wxArrayString filesPaths) {
	imagesLoaded = false;
	nbPages = filesPaths.GetCount();
	std::cout << "there is this nb of pages to load " << nbPages << "\n";
	pagesVector.resize(nbPages);
	files.vector = {};
	for(unsigned int i=0; i<nbPages; i++) {

		wxString filePath = filesPaths.Item(i);
		std::cout << "filesPath(i) : " << filesPaths.Item(i)	<< "\n";
		wxString fileName = filePath.AfterLast('/');
		File file = {.name = fileName, .path = filePath, .pageNumber = i};
		files.vector.push_back(file);
		if ( !filePath.empty() ) {
			if (imageRGB)
				delete imageRGB;

			// open image dialog box
			std::cout << "file path : " << filePath	<< "\n";
			imageRGB = new wxImage(filePath, wxBITMAP_TYPE_ANY, -1);
			std::cout << imageRGB->IsOk() << " : there is data in imageRGB\n";
			// ANY => can load many image formats
//			imageWidth = imageRGB->GetWidth();
	//		imageHeight = imageRGB->GetHeight();
			imageRGB->Rescale(pageWidth, pageHeight, wxIMAGE_QUALITY_BICUBIC);
			wxImage tempImage = imageRGB->Copy();
			pagesVector.at(i) = tempImage;

			//update GUI
			SetScrollbars(1,1,nbPages*pageWidth,pageHeight,0,0);
			if (nbPages > 1)
				SetSize(2*pageWidth, pageHeight);
			else
				SetSize(pageWidth, pageHeight);
			GetParent()->SetClientSize(GetSize());
//			Fit();
//			SetClientSize(GetParent()->GetSize());
			// update display
			Refresh(false);
		}
	}
	wxArrayString fileNames = {};
	files.GetNames(&fileNames);

	pagesOrderList->SetStrings(fileNames);
	pagesOrderList->GetStrings(pagesArray);
	imagesLoaded = true;
}

void LiseusePanel::SaveImage(wxString filePath)
{
	bool b ;

	wxMemoryDC mdc(imageBitmap);

	wxFont* font = new wxFont(wxFontInfo(8));
	mdc.SetFont(*font);

	mdc.DrawBitmap(imageBitmap, 0, 0);
	for (int i=0; i < annotations.size(); i++)
	{
		// Afficher les annotations
		mdc.DrawText(annotations.at(i).note,annotations.at(i).pt.x-3,annotations.at(i).pt.y-11);
	};

	wxImage tempImage = imageBitmap.ConvertToImage();
	b = tempImage.SaveFile(filePath) ;

	if(!b)
		wxMessageBox(wxT("A problem occured during saving"));
}

void LiseusePanel::BestSize()
{
	SetSize(imageWidth, imageHeight) ;	// ideal size for canvas
	GetParent()->SetClientSize(GetSize());	// force the main frame to show the whole canvas
}

void LiseusePanel::OnPaint(wxPaintEvent &WXUNUSED(event))
// update the main window content. Appelé avec Refresh()
{
	std::cout << "OnPaint is called" << "\n";

	pagesOrderList->GetStrings(pagesArrayNew);
	if (imagesLoaded)
		UpdatePagesVector();
	wxPaintDC dc(this);
	DoPrepareDC(dc);
	wxFont* font = new wxFont(wxFontInfo(8));
	dc.SetFont(*font);
	if (imageRGB)
	{
		// Show pages
		for (int i=0; i < nbPages; i++) {
			imageBitmap = wxBitmap(pagesVector.at(i), -1); // ...to get the corresponding bitmap
			dc.DrawBitmap(imageBitmap, i*(pageWidth), 0);
		}
		// Show annotations
		for (int i=0; i < annotations.size(); i++) {
			Annotation annotation = annotations.at(i);
			std::cout << i << " eme annotation has pageNumber " << annotation.pageNumber << " and as label   " << annotation.note << "\n";
			dc.DrawText(annotation.note,annotation.pt.x-3 + pageWidth*annotation.pageNumber, annotation.pt.y-11);
		};
	};
}

void LiseusePanel::UpdatePagesVector() {
	if (pagesArray != pagesArrayNew) {
		nbPages = pagesArrayNew.GetCount();
		for(unsigned int i=0; i<nbPages; i++) {
			wxString fileName = pagesArrayNew.Item(i);
			wxString filePath = files.FindPath(fileName);

			if (i<nbPages-1 && fileName == pagesArray.Item(i+1)) {
				std::cout << "We launch ChangeAnnotationsPlacements\n";
				ChangeAnnotationsPlacements(i);
				files.ChangePagePosition(i, pagesArrayNew, pagesArray);
			};

			if ( !filePath.empty() ) {
				if (imageRGB)
					delete imageRGB;
				// open image dialog box
				imageRGB = new wxImage(filePath, wxBITMAP_TYPE_ANY, -1);
				imageRGB->Rescale(pageWidth, pageHeight, wxIMAGE_QUALITY_BICUBIC);
				wxImage tempImage = imageRGB->Copy();
				pagesVector.at(i) = tempImage;
				//update GUI
				if (nbPages > 1)
					SetSize(2*pageWidth, pageHeight);
				else
					SetSize(pageWidth, pageHeight);
				GetParent()->SetClientSize(GetSize());
				GetParent()->Update();
			}
		}
	pagesArray = pagesArrayNew;
	}
}

void LiseusePanel::ChangeAnnotationsPlacements(unsigned int pageNb) {
	if (pagesArrayNew.GetCount() < pagesArray.GetCount()) {
		std::cout << "annotation n° " << pageNb << " has pgNb " << annotations.at(pageNb).pageNumber << "\n";
		if (annotations.at(pageNb).pageNumber == 0) {
			Annotation temp = annotations.back();
			annotations.at(pageNb) = annotations.back();
			annotations.pop_back();
			std::cout << "pageNb of erased annotation is " << annotations.at(pageNb).pageNumber << "\n";
			pageNb--;
		}
		else {
			std::cout << "annotation n° " << pageNb << " had pgNb " << annotations.at(pageNb).pageNumber << "\n";
			annotations.at(pageNb).pageNumber = annotations.at(pageNb).pageNumber - 1;
			std::cout << "annotation n° " << pageNb << " has now pgNb " << annotations.at(pageNb).pageNumber << "\n";
		}
	}
	else {
		for (int i=0; i < annotations.size(); i++) {
			if (annotations.at(i).pageNumber == pageNb)
				annotations.at(i).pageNumber = pageNb+1;
			else if (annotations.at(i).pageNumber == pageNb+1)
				annotations.at(i).pageNumber = pageNb;
		}
	}
}

void LiseusePanel::OnListboxLDown(wxMouseEvent& event) {
	Refresh();
	Update();
}

void LiseusePanel::OnRightClick(wxMouseEvent& event)
{
	Refresh();
	Update();
	if (imageRGB)
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
			undo = (c_x >= a_x-3) && (c_x <= a_x + a_l*5) && (c_y >= a_y-12) && (c_y <= a_y+3);
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
	Annotation temp_annotation = {.note = myNote, .pt = myPt, .pageNumber = temp_annotation.pt.x / pageWidth};
	std::cout << "Annotation on page " << temp_annotation.pageNumber << "\n";
	temp_annotation.pt.x = temp_annotation.pt.x % pageWidth;
	annotations.push_back(temp_annotation);
}


#endif
