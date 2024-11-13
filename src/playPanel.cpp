#include <wx/wx.h>
#include <wx/panel.h>
#include "playPanel.hpp"
#include"wxcard.hpp"





PlayPanel::PlayPanel(wxFrame* parent) : wxPanel(parent),parentFrame(parent) {
    // Main sizer for the entire window (horizontal layout)
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    //----------------------------------------------------------------------//
    //------------------LEFT PANEL(yellow)---------------------------------//
    //--------------------------------------------------------------------//
    wxPanel* leftPanel = new wxPanel(this, wxID_ANY);
    //leftPanel->SetBackgroundColour(wxColour(163, 146, 122));//yellow


    // Vertical sizer for left, center, and right panels
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    //---------------------------------------------------------------------//
    //------------------TOP PANEL(dark red)-------------------------------//
    //-------------------------------------------------------------------//
    wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 50));
    //topPanel->SetBackgroundColour(wxColour(163, 146, 122));//reddish
      wxBoxSizer* buttonTopSizer = new wxBoxSizer(wxHORIZONTAL);
      wxButton* resignButton = new wxButton(topPanel, wxID_ANY,"Resign" , wxDefaultPosition, wxSize(80, 30));
      wxButton* quitButton = new wxButton(topPanel, wxID_ANY,"Quit" , wxDefaultPosition, wxSize(80, 30));
      wxButton* saveButton = new wxButton(topPanel, wxID_ANY, "Save" , wxDefaultPosition, wxSize(80, 30));
      resignButton->Bind(wxEVT_BUTTON, &PlayPanel::OnButtonClicked, this);
      quitButton->Bind(wxEVT_BUTTON, &PlayPanel::OnButtonClicked, this);
      saveButton->Bind(wxEVT_BUTTON, &PlayPanel::OnButtonClicked, this);
      buttonTopSizer->Add(quitButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
      buttonTopSizer->Add(resignButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
      buttonTopSizer->Add(saveButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
      topPanel->SetSizer(buttonTopSizer);


    //---------------------------------------------------------------------//
    //------------------Center panel (green)------------------------------//
    //-------------------------------------------------------------------//
    wxPanel* centerPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));
    centerPanel->SetBackgroundColour(wxColour(186, 219, 167));//green

    //---------------------------------------------------------------------//
    //------------------Played panel (cyan)------------------------------//
    //-------------------------------------------------------------------//
    wxPanel* lightBluePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 100));
    lightBluePanel->SetBackgroundColour(wxColour(137, 163, 122));

    wxBoxSizer* lightBluePanelSizer = new wxBoxSizer(wxHORIZONTAL);

    for (int i = 0; i < 15; ++i) {
        wxCard* card = new wxCard(lightBluePanel,"gold", 90,50,80,50,80,wxColour(0,0,0));
        lightBluePanelSizer->Add(card, 0, wxALL, 5);
    }
    lightBluePanel->SetSizer(lightBluePanelSizer);



    //---------------------------------------------------------------------//
    //------------------Bottom panel (Pink)-------------------------------//
    //-------------------------------------------------------------------//
    wxPanel* pinkPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 100));
    pinkPanel->SetBackgroundColour(wxColour(120, 160, 120));//pink










    // Bottom sizer for light blue, pink, and small blue panels
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    //---------------------------------------------------------------------//
    //------------------Right panel (red)---------------------------------//
    //-------------------------------------------------------------------//
    wxPanel* rightPanel = new wxPanel(this, wxID_ANY,wxDefaultPosition, wxSize(100, -1));
    //rightPanel->SetBackgroundColour(wxColour(122, 148, 163));//red

    //---------------------------------------------------------------------//
    //------------------bottom right panel (red)--------------------------//
    //-------------------------------------------------------------------//
    wxPanel* smallBluePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, -1));
    smallBluePanel->SetBackgroundColour(wxColour(122, 148, 163));//blue







    //---------------------------------------------------------------------//
    // Add the panels to their respective sizers
    mainSizer->Add(leftPanel, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(verticalSizer, 5, wxEXPAND | wxALL, 5);
    mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL, 5);

    verticalSizer->Add(topPanel, 0, wxEXPAND | wxBOTTOM, 5);
    verticalSizer->Add(centerPanel, 5, wxEXPAND | wxBOTTOM, 5);
    verticalSizer->Add(lightBluePanel, 2, wxEXPAND | wxBOTTOM, 5);
    verticalSizer->Add(pinkPanel, 2, wxEXPAND | wxBOTTOM, 5);

    rightSizer->Add(rightPanel, 4, wxEXPAND | wxRIGHT | wxBOTTOM, 5);
    rightSizer->Add(smallBluePanel, 1, wxEXPAND | wxRIGHT, 5);
    // Set the main sizer for the frame
    SetSizer(mainSizer);
    Layout();
}



PlayPanel::~PlayPanel(){

}

void PlayPanel::OnButtonClicked(wxCommandEvent& event) {
  //wxLogMessage(name);
  wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
  if (button) {
        wxString buttonName = button->GetLabel();
        //notify parent
        wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
        notifyEvent.SetString(buttonName);  // Include button name in the event
        wxPostEvent(this->parentFrame, notifyEvent); // Send event to parent frame
  }

}
