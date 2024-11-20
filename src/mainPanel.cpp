#include "mainPanel.hpp"
#include "resources.hpp"

#include "Modele.h"


BEGIN_EVENT_TABLE(MainPanel, wxPanel)
EVT_PAINT(MainPanel::paintEvent)
EVT_SIZE(MainPanel::OnSize)
END_EVENT_TABLE()


MainPanel::MainPanel(wxFrame* parent, Modele* model) : wxPanel(parent){
    m_modele = model;

    image = Resources::getInstance()->getImage("background-img");
    w = -1;
    h = -1;

    //buttons
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxButton* button1 = new wxButton(this, wxID_ANY, "New Game", wxDefaultPosition, wxSize(200, 30));
    wxButton* button2 = new wxButton(this, wxID_ANY, "Resume", wxDefaultPosition, wxSize(200, 30));
    wxButton* button3 = new wxButton(this, wxID_ANY, "Settings", wxDefaultPosition, wxSize(200, 30));
    wxButton* button4 = new wxButton(this, wxID_ANY, "About", wxDefaultPosition, wxSize(200, 30));
    wxButton* button5 = new wxButton(this, wxID_ANY, "Quit", wxDefaultPosition, wxSize(200, 30));

    button1->Bind(wxEVT_BUTTON, &MainPanel::OnButtonClicked, this);
    button2->Bind(wxEVT_BUTTON, &MainPanel::OnButtonClicked, this);
    button3->Bind(wxEVT_BUTTON, &MainPanel::OnButtonClicked, this);
    button4->Bind(wxEVT_BUTTON, &MainPanel::OnButtonClicked, this);
    button1->Bind(wxEVT_BUTTON, &MainPanel::OnButtonClicked, this);
    button5->Bind(wxEVT_BUTTON, &MainPanel::OnButtonClicked, this);

    //fonts
    wxFont customFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, "Comic Sans MS");
    button1->SetFont(customFont);
    button2->SetFont(customFont);
    button3->SetFont(customFont);
    button4->SetFont(customFont);
    button5->SetFont(customFont);

    //space between buttons
    vbox->AddStretchSpacer(1);
    vbox->Add(button1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 15);
    vbox->Add(button2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 15);
    vbox->Add(button3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 15);
    vbox->Add(button4, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 15);
    vbox->Add(button5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 15);
    vbox->AddStretchSpacer(1);
    this->SetSizer(vbox);
}


MainPanel::~MainPanel(){}

void MainPanel::paintEvent(wxPaintEvent & evt){
    wxPaintDC dc(this);// depending on your system you may need to look at double-buffered dcs
    render(dc);
}


void MainPanel::paintNow(){
    wxClientDC dc(this);// depending on your system you may need to look at double-buffered dcs
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate  method so that it can work no matter what type of DC (e.g. wxPaintDC or wxClientDC) is used.
 */
void MainPanel::render(wxDC&  dc){
    int neww, newh;
    dc.GetSize( &neww, &newh );
    if( neww != w || newh != h ){
        resized = wxBitmap( image->Scale( neww, newh /*, wxIMAGE_QUALITY_HIGH*/ ) );
        w = neww;
        h = newh;
        dc.DrawBitmap( resized, 0, 0, false );
    }else{
        dc.DrawBitmap( resized, 0, 0, false );
    }
}

/*
 * Here we call refresh to tell the panel to draw itself again.  So when the user resizes the image panel the image should be resized too.
 */
void MainPanel::OnSize(wxSizeEvent& event){
    Refresh();
    event.Skip();//skip the event.
}



void MainPanel::OnButtonClicked(wxCommandEvent& event) {
  //wxLogMessage(name);
  wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
  if (button) {
        wxString buttonName = button->GetLabel();
        wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
        notifyEvent.SetString(buttonName);  // Include button name in the event
        wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
  }
}
