#include <wx/wx.h>
#include <wx/slider.h>
#include <set>
#include"settingsPanel.hpp"
#include"resources.hpp"
#include"wxcard.hpp"

#include "Modele.h"

#define HEIGHLIGHT_COLOUR wxColour(255, 252, 51)
#define SELECTED_COLOUR wxColour(173, 240, 180)



SettingsPanel::SettingsPanel(wxWindow* parent, Modele* model): wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL),m_modele(model),m_cardsSelected(10){


  Resources::getInstance()->getSettings(this->m_totalPlayers,this->m_humanPlayers,this->m_sound,this->m_chosenCards);
  /*m_totalPlayers = 5;//todo
  m_humanPlayers = 5;//todo
  m_sound = 50;//todo
  //todo
  m_chosenCards.insert("artisan");
  m_chosenCards.insert("bandit");
  m_chosenCards.insert("bureaucrat");
  m_chosenCards.insert("cellar");
  m_chosenCards.insert("chapel");*/

  this->SetBackgroundColour(wxColour(86, 118, 153));//background color
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);//sizer

  //--------------------buttons--------------------
  wxButton* backButton = new wxButton(this, wxID_ANY, "Back");
  wxButton* resetButton = new wxButton(this, wxID_ANY, "Reset");
  wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
  buttonSizer->Add(backButton, 0, wxALL, 5);
  buttonSizer->Add(resetButton, 0, wxALL, 5);
  backButton->Bind(wxEVT_BUTTON, &SettingsPanel::OnBackButtonClicked, this);
  resetButton->Bind(wxEVT_BUTTON, &SettingsPanel::OnResetButtonClicked, this);
  mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 30);
  mainSizer->AddSpacer(15);


  wxPanel* firstPanel = new wxPanel(this);
  wxBoxSizer* firstPanelSizer = new wxBoxSizer(wxVERTICAL);

  //--------------------text--------------------
  wxStaticText* totalPlayersLabel = new wxStaticText(firstPanel, wxID_ANY, "Total Players:");
  totalPlayersLabel->SetForegroundColour(wxColour(243, 210, 161));
  firstPanelSizer->Add(totalPlayersLabel, 0, wxALIGN_CENTER, 20);

  //--------------------slider--------------------
  m_totalPlayersSlider = new wxSlider(firstPanel, wxID_ANY, m_totalPlayers, 2, 6, wxDefaultPosition, wxSize(300,50), wxSL_HORIZONTAL | wxSL_LABELS);
  firstPanelSizer->Add(m_totalPlayersSlider, 0, wxALIGN_CENTER | wxBOTTOM, 20);
  m_totalPlayersSlider->Bind(wxEVT_SLIDER, &SettingsPanel::OnTotalPlayersChanged, this);

  //--------------------text--------------------
  wxStaticText* humanPlayersLabel = new wxStaticText(firstPanel, wxID_ANY, "Human Players:");
  humanPlayersLabel->SetForegroundColour(wxColour(243, 210, 161));
  firstPanelSizer->Add(humanPlayersLabel, 0, wxALIGN_CENTER, 20);

  //--------------------slider--------------------
  m_humanPlayersSlider = new wxSlider(firstPanel, wxID_ANY, m_humanPlayers, 1, 6, wxDefaultPosition, wxSize(300,50), wxSL_HORIZONTAL | wxSL_LABELS);
  firstPanelSizer->Add(m_humanPlayersSlider, 0, wxALIGN_CENTER | wxBOTTOM, 20);
  m_humanPlayersSlider->Bind(wxEVT_SLIDER, &SettingsPanel::OnHumanPlayersChanged, this);

  //--------------------text--------------------
  wxStaticText* soundLabel = new wxStaticText(firstPanel, wxID_ANY, "Sound:");
  soundLabel->SetForegroundColour(wxColour(243, 210, 161));
  firstPanelSizer->Add(soundLabel, 0, wxALIGN_CENTER, 20);

  //--------------------slider--------------------
  m_soundSlider = new wxSlider(firstPanel, wxID_ANY, m_sound, 0, 100, wxDefaultPosition, wxSize(300,50), wxSL_HORIZONTAL | wxSL_LABELS);
  firstPanelSizer->Add(m_soundSlider, 0, wxALIGN_CENTER, 20);
  m_soundSlider->Bind(wxEVT_SLIDER, &SettingsPanel::OnSoundChange, this);

  firstPanel->SetSizer(firstPanelSizer);
  mainSizer->Add(firstPanel, 0, wxALIGN_CENTER, 2);

  //----------------------------------------
  mainSizer->AddSpacer(50);
  //----------------------------------------

  wxPanel* secondPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 2500));
  wxBoxSizer* secondPanelSizer = new wxBoxSizer(wxVERTICAL);

  //--------------------text--------------------
  m_cardsLabel = new wxStaticText(secondPanel, wxID_ANY, "Initial Cards: 10");
  m_cardsLabel->SetForegroundColour(wxColour(243, 210, 161));
  secondPanelSizer->Add(m_cardsLabel, 0, wxALIGN_CENTER, 20);

  //--------------------grid--------------------
  int numPanels = wxCard::ActionCards.size();
  int numColumns = 4;
  wxPanel* gridContainer = new wxPanel(secondPanel);
  int numRows = (numPanels + numColumns - 1) / numColumns;
  wxGridSizer* gridSizer = new wxGridSizer(numRows, numColumns, 5, 5); // 5px gap between panels

  for(const auto& c : wxCard::ActionCards){

    wxColour colour;
    if(m_chosenCards.find(c) != m_chosenCards.end()){
      colour = SELECTED_COLOUR;
    }

    wxCard* card = new wxCard(gridContainer,c, 0,200,320,180,288,colour);
    this->m_gridCards.push_back(card);
    gridSizer->Add(card, 0, wxALIGN_CENTER, 2);
  }

  gridContainer->SetSizer(gridSizer);
  gridContainer->Bind(wxEVT_BUTTON, &SettingsPanel::OnCardEvent, this);
  secondPanelSizer->Add(gridContainer, 1, wxEXPAND | wxALL, 2);

  secondPanel->SetSizer(secondPanelSizer);
  mainSizer->Add(secondPanel, 1, wxEXPAND | wxALL, 1);


  // Set the main sizer
  this->SetScrollRate(0, 10);
  this->SetSizer(mainSizer);
  mainSizer->FitInside(this);
  SetVirtualSize(mainSizer->GetMinSize());
}


SettingsPanel::~SettingsPanel(){
  Resources::getInstance()->setSettings(this->m_totalPlayers,this->m_humanPlayers,this->m_sound,this->m_chosenCards);
}



void SettingsPanel::OnTotalPlayersChanged(wxCommandEvent& event) {
    this->m_totalPlayers = m_totalPlayersSlider->GetValue();
    m_humanPlayersSlider->SetMax(m_totalPlayers);
    this->m_humanPlayers = m_humanPlayersSlider->GetValue();
}



void SettingsPanel::OnHumanPlayersChanged(wxCommandEvent& event) {
    this->m_humanPlayers = m_humanPlayersSlider->GetValue();
}




void SettingsPanel::OnSoundChange(wxCommandEvent& event) {
  this->m_sound = m_soundSlider->GetValue();
  //todo
}




void SettingsPanel::OnBackButtonClicked(wxCommandEvent& event){
  wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
  notifyEvent.SetString("Back");  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
}






void SettingsPanel::OnResetButtonClicked(wxCommandEvent& event){
  this->m_totalPlayers = 5;
  m_totalPlayersSlider->SetValue(m_totalPlayers);
  m_humanPlayersSlider->SetMax(m_totalPlayers);
  this->m_humanPlayers = 1;
  m_humanPlayersSlider->SetValue(m_humanPlayers);
  this->m_sound  = 50;
  m_soundSlider->SetValue(m_sound);
  this->m_cardsSelected = 10;
  this->m_chosenCards = {"cellar", "market", "militia", "mine", "moat", "remodel", "smithy", "village", "woodcutter",  "workshop"};

  for(const auto& cp : this->m_gridCards){
    wxColour colour;
    if(m_chosenCards.find(cp->m_name) != m_chosenCards.end()){colour = SELECTED_COLOUR;}
    cp->SetBackgroundColour(colour);
  }

  Refresh();
  //todo reset parameters
}


void SettingsPanel::OnCardEvent(wxCommandEvent& event){
  wxString cardName = event.GetString();
  for(const auto c : m_gridCards){
    if (c->m_name == cardName){
      wxColour newColour;

      switch (event.GetId()) {
        case 1:
          newColour = HEIGHLIGHT_COLOUR;break;

        case 2:
          if(m_chosenCards.find(c->m_name) != m_chosenCards.end()){newColour = SELECTED_COLOUR;}
          break;

        case 3:
          if(m_chosenCards.find(c->m_name) != m_chosenCards.end()){
            m_chosenCards.erase(c->m_name);
          }else{
            m_chosenCards.insert(c->m_name);
            newColour = SELECTED_COLOUR;
          }
          break;
      }
      c->SetBackgroundColour(newColour);
      break;
    }
  }
  this->Refresh();
}
