#ifndef _LISEUSEFRAME_CPP_
#define _LISEUSEFRAME_CPP_

#include "LiseuseFrame.h"

BEGIN_EVENT_TABLE(LiseuseFrame, wxFrame)
	EVT_MENU(ID_NEW,  LiseuseFrame::OnNewImage)
	EVT_MENU(ID_OPEN, LiseuseFrame::OnOpenImage)
	EVT_MENU(ID_SAVE,  LiseuseFrame::OnSaveImage)
	EVT_MENU(ID_WRITE_FILE, LiseuseFrame::OnWriteFile)
	EVT_MENU(ID_QUIT,  LiseuseFrame::OnQuit)
	EVT_MENU(ID_ABOUT, LiseuseFrame::OnAbout)
	EVT_MENU(ID_BEST_SIZE,  LiseuseFrame::OnBestSize)
	EVT_MENU(ID_SMALL,  LiseuseFrame::OnSmall)
	EVT_MENU(ID_MEDIUM,  LiseuseFrame::OnMedium)
	EVT_MENU(ID_LARGE,  LiseuseFrame::OnLarge)
	EVT_MENU(ID_EXTRA_LARGE,  LiseuseFrame::OnExtraLarge)
	EVT_MENU(ID_ORDER, LiseuseFrame::OnOrder)
	EVT_LEFT_DOWN(LiseuseFrame::OnListboxLDown)
	EVT_SIZE(LiseuseFrame::ResizePanel)
	EVT_CLOSE(LiseuseFrame::OnClose)
END_EVENT_TABLE()


LiseuseFrame::LiseuseFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	wxMenu *menuFile = new wxMenu();

	menuFile->Append(ID_NEW, _T("&New image(s) ..."));
	menuFile->Append(ID_OPEN, _T("&Open image file ..."));
	menuFile->Append(ID_SAVE, _T("&Save image as..."));
	menuFile->AppendSeparator();
	menuFile->Append(ID_WRITE_FILE, _T("&Write file..."));
	menuFile->AppendSeparator();
	menuFile->Append(ID_QUIT, _T("&Exit"));

	wxMenu *menuHelp = new wxMenu();
	menuHelp->Append(ID_ABOUT, _T("&About..."));

	wxMenu *menuView = new wxMenu();
/*	menuView->Append(ID_ZOOM, "&Zoom");
	menuView->AppendSeparator();
	menuView->Append(ID_DISPLAY, "&Display");
	menuView->Append(ID_BEST_SIZE, _T("&Best size"));*/
	menuView->Append(ID_ORDER, _T("&Order"));
	menuView->AppendSeparator();
	menuView->Append(ID_SMALL, _T("&Small"));
	menuView->Append(ID_MEDIUM, _T("&Medium"));
	menuView->Append(ID_LARGE, _T("&Large"));
	menuView->Append(ID_EXTRA_LARGE, _T("&Extra Large"));

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(menuFile, _T("&File"));
	menuBar->Append(menuHelp, _T("&Help"));
	menuBar->Append(menuView, _T("&View"));
	SetMenuBar( menuBar );
	CreateStatusBar();

	// create the panel that will manage the image
	panel = new LiseusePanel( this, -1, wxDefaultPosition, wxDefaultSize);
	panel->pagesOrderList->Connect(wxEVT_LIST_ITEM_SELECTED, wxMouseEventHandler(LiseuseFrame::OnListboxLDown), NULL, this);
	imageLoaded = false;
	panel->pagesOrderList->Hide();
	orderShown = false;
	Centre() ;
}

void LiseuseFrame::OnListboxLDown(wxMouseEvent & event)
{
		Refresh();
		Update();
    event.Skip();
}

void LiseuseFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true) ;
}

void LiseuseFrame::OnOrder(wxCommandEvent& WXUNUSED(event))
{
	if (orderShown)
  	panel->pagesOrderList->Hide();
	else
		panel->pagesOrderList->Show();
	orderShown = !orderShown;
}

void LiseuseFrame::OnClose(wxCloseEvent& event)
{
	delete panel ;
	event.Skip() ;
}

void LiseuseFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _T("Pour annoter faites un clic droit\nPour effacer faites un clic droit sur l'annotation à supprimer"),
                  _T(APP_NAME), wxOK | wxICON_INFORMATION ) ;
}

void LiseuseFrame::OnNewImage(wxCommandEvent& WXUNUSED(event) )
{
	wxBitmap bitmap;

	wxFileDialog openFileDialog(this,
		_("Open .jpg files"), "", "", "All files (*.*)|*.*",
		wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

		if (openFileDialog.ShowModal() == wxID_CANCEL)
			return; // the user changed idea

	openFileDialog.GetPaths(filesPaths);
	panel->NewImages(filesPaths);
	imageLoaded = true;
}

void LiseuseFrame::OnOpenImage(wxCommandEvent& WXUNUSED(event) )
{
	wxBitmap bitmap;

	wxFileDialog openFileDialog(this, _("Open .partition files"), "", "", "Partition files (*.partition)|*.partition", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // the user changed idea

	wxString filePathWX = openFileDialog.GetPath();
	std::string filePath = filePathWX.ToStdString();
	panel->OpenImages(filePath);
	imageLoaded = true;
}

void LiseuseFrame::OnSaveImage(wxCommandEvent & WXUNUSED(event))
{
//	char str[128] = "" ; // proposed file name

	if (!imageLoaded)
		return ;

	wxString filePath = wxFileSelector(_T("Save image as"),_T(""),_T(""),_T("*.bmp"), _T("BMP files (*.bmp)|*.bmp|GIF files (*gif)|*.gif|JPEG files (*jpg)|*.jpg|PNG files (*png)|*.png|TIFF files (*tif)|*.tif|XPM files (*xpm)|*.xpm|All files (*.*)|*.*"), wxFD_SAVE );
	if ( !filePath.empty() )
		panel->SaveImage(filePath) ;
}

void LiseuseFrame::OnWriteFile(wxCommandEvent& WXUNUSED(event))
{
	if(!imageLoaded)
		return ;

	wxString filePathWX = wxFileSelector(_T("Save image names in textfile as"),_T(""),_T(""),_T("*.txt"), _T("Partition files (*.partition)|*.partition"), wxFD_SAVE );
	if ( !filePathWX.empty() )
	{
		std::string filePath = filePathWX.ToStdString();
		panel->WriteFile(filePath) ;
	}
}

void LiseuseFrame::OnBestSize(wxCommandEvent& WXUNUSED(event))
{
    panel->BestSize() ;
}

void LiseuseFrame::OnSmall(wxCommandEvent& WXUNUSED(event)) {
	panel->pageWidth = 308;
	panel->pageHeight = 400;
	panel->imagesLoaded = false;
	panel->files.GetPaths(&filesPaths);
	std::cout << "check\n";
	panel->NewImages(filesPaths);
}

void LiseuseFrame::OnMedium(wxCommandEvent& WXUNUSED(event)) {
	panel->pageWidth = 462;
	panel->pageHeight = 600;
	panel->imagesLoaded = false;
	panel->files.GetPaths(&filesPaths);
	std::cout << "check\n";
	panel->NewImages(filesPaths);
}

void LiseuseFrame::OnLarge(wxCommandEvent& WXUNUSED(event)) {
	panel->pageWidth = 618;
	panel->pageHeight = 800;
	panel->imagesLoaded = false;
	panel->files.GetPaths(&filesPaths);
	std::cout << "check\n";
	panel->NewImages(filesPaths);
}

void LiseuseFrame::OnExtraLarge(wxCommandEvent& WXUNUSED(event)) {
	panel->pageWidth = 772;
	panel->pageHeight = 1000;
	panel->imagesLoaded = false;
	panel->files.GetPaths(&filesPaths);
	std::cout << "check\n";
	panel->NewImages(filesPaths);
}

void LiseuseFrame::ResizePanel(wxSizeEvent& event) {
	std::cout << "Frame is resized\n";
	panel->SetSize(GetClientSize());
}

#endif
