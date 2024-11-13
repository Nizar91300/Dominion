#include <wx/wx.h>
#include <wx/slider.h>
#include"settingsPanel.hpp"
#include"wxcard.hpp"


SettingsPanel::SettingsPanel(wxWindow* parent): wxPanel(parent),parentFrame(parent){
    SetBackgroundColour(wxColour(86, 118, 153));
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    //--------------------buttons--------------------
    wxButton* backButton = new wxButton(this, wxID_ANY, "Back");
    wxButton* resetButton = new wxButton(this, wxID_ANY, "Reset");
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(backButton, 0, wxALL, 5);
    buttonSizer->Add(resetButton, 0, wxALL, 5);
    backButton->Bind(wxEVT_BUTTON, &SettingsPanel::OnButtonClicked, this);
    resetButton->Bind(wxEVT_BUTTON, &SettingsPanel::OnButtonClicked, this);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 30);
    mainSizer->AddSpacer(15);

    //--------------------other--------------------
    wxStaticText* totalPlayersLabel = new wxStaticText(this, wxID_ANY, "Total Players:");
    totalPlayersLabel->SetForegroundColour(wxColour(243, 210, 161));
    mainSizer->Add(totalPlayersLabel, 0, wxALIGN_CENTER, 20);

    totalPlayersSlider = new wxSlider(this, wxID_ANY, 5, 5, 8, wxDefaultPosition, wxSize(300,50), wxSL_HORIZONTAL | wxSL_LABELS);
    mainSizer->Add(totalPlayersSlider, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    // Slider for Human Players
    wxStaticText* humanPlayersLabel = new wxStaticText(this, wxID_ANY, "Human Players:");
    humanPlayersLabel->SetForegroundColour(wxColour(243, 210, 161));
    mainSizer->Add(humanPlayersLabel, 0, wxALIGN_CENTER, 20);

    humanPlayersSlider = new wxSlider(this, wxID_ANY, 1, 1, 5, wxDefaultPosition, wxSize(300,50), wxSL_HORIZONTAL | wxSL_LABELS);
    mainSizer->Add(humanPlayersSlider, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    // Slider for Sound
    wxStaticText* soundLabel = new wxStaticText(this, wxID_ANY, "Sound:");
    soundLabel->SetForegroundColour(wxColour(243, 210, 161));
    mainSizer->Add(soundLabel, 0, wxALIGN_CENTER, 20);

    soundSlider = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize(300,50), wxSL_HORIZONTAL | wxSL_LABELS);
    mainSizer->Add(soundSlider, 0, wxALIGN_CENTER, 20);


    totalPlayersSlider->Bind(wxEVT_SLIDER, &SettingsPanel::OnTotalPlayersChanged, this);
    humanPlayersSlider->Bind(wxEVT_SLIDER, &SettingsPanel::OnHumanPlayersChanged, this);
    mainSizer->AddSpacer(30);

    wxStaticText* cardsLabel = new wxStaticText(this, wxID_ANY, "Initial Cards:");
    cardsLabel->SetForegroundColour(wxColour(243, 210, 161));
    mainSizer->Add(cardsLabel, 0, wxALIGN_CENTER, 20);


    //--------------------grid--------------------
    int numPanels = 15;
    int numColumns = 3;
    wxScrolledWindow* gridContainer = new wxScrolledWindow(this,wxID_ANY, wxDefaultPosition, wxSize(800,-1), wxVSCROLL);
    gridContainer->SetScrollRate(5, 5);;

    int numRows = (numPanels + numColumns - 1) / numColumns; // Calculate rows needed
    wxGridSizer* gridSizer = new wxGridSizer(numRows, numColumns, 5, 5); // 5px gap between panels
    for (int i = 0; i < numPanels; ++i) {
        wxCard* card = new wxCard(gridContainer,"gold", 0);
        gridSizer->Add(card, 0, wxALIGN_CENTER, 2);
    }
    gridContainer->SetSizer(gridSizer);
    gridContainer->FitInside();
    mainSizer->Add(gridContainer, 1, wxEXPAND | wxALL, 10);

    // Set the main sizer
    SetSizer(mainSizer);

}



void SettingsPanel::OnTotalPlayersChanged(wxCommandEvent& event) {
    int totalPlayers = totalPlayersSlider->GetValue();
    humanPlayersSlider->SetMax(totalPlayers);
}



void SettingsPanel::OnHumanPlayersChanged(wxCommandEvent& event) {
    //int humanPlayers = humanPlayersSlider->GetValue();
}


void SettingsPanel::OnButtonClicked(wxCommandEvent& event) {
  //wxLogMessage(name);
  wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
  if (button) {
        wxString buttonName = button->GetLabel();
        wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
        notifyEvent.SetString(buttonName);  // Include button name in the event
        wxPostEvent(this->parentFrame, notifyEvent); // Send event to parent frame
  }

}
