#include <wx/wx.h>
#include <wx/sizer.h>
#include <vector>
#include "voleurPanel.hpp"
#include "wxcard.hpp"

#include "playPanel.hpp"
#include "Carte.h"


//N must be pair
VoleurPanel::VoleurPanel(wxWindow* parent) : wxPanel(parent) {
  // Main vertical sizer for layout
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
  wxFont comicFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Comic Sans MS");
  wxStaticText* text = new wxStaticText(this, wxID_ANY, "This is the first 2 cards from other players");
  text->SetFont(comicFont);
  mainSizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 50);

  int numPanels = 5;
  int numColumns = 3;
  int numRows = (numPanels + numColumns - 1) / numColumns;
  wxGridSizer* gridSizer = new wxGridSizer(numRows, numColumns, 5, 5);


  for (int i = 0; i < numPanels; ++i) {
      // Create a horizontal box sizer to group two panels  push_back(card);
      wxPanel* wrapperPanel = new wxPanel(this, wxID_ANY);
      wxBoxSizer* wrapperSizer = new wxBoxSizer(wxVERTICAL);

      //label
      wxStaticText* label = new wxStaticText(wrapperPanel, wxID_ANY, "Player");
      wrapperSizer->Add(label, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

      //cards
      wxPanel* pairPanel = new wxPanel(wrapperPanel, wxID_ANY);
      wxBoxSizer* pairSizer = new wxBoxSizer(wxHORIZONTAL);
      wxCard* panel1 = new wxCard(pairPanel,"gold", 0,150,240,150,240,*wxRED);
      wxCard* panel2 = new wxCard(pairPanel,"gold", 0,150,240,150,240,*wxRED);
      pairSizer->Add(panel1, 1, wxALL, 2);
      pairSizer->Add(panel2, 1, wxALL, 2);
      pairPanel->SetSizer(pairSizer);

      wrapperSizer->Add(pairPanel, 0, wxALL, 2);
      wrapperPanel->SetSizer(wrapperSizer);
      gridSizer->Add(wrapperPanel, 1, wxALL, 5);

      std::vector<wxCard*> wxcards={panel1,panel2};
      this->cards.push_back(wxcards);
      this->panels.push_back(wrapperPanel);
      this->texts.push_back(label);
  }
  // Add the grid to the main sizer
  mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);


  Bind(wxEVT_CHAR_HOOK, &VoleurPanel::OnQuit, this);
  Bind(wxEVT_LEFT_DOWN, &VoleurPanel::OnQuit, this);
  Bind(wxEVT_RIGHT_DOWN, &VoleurPanel::OnQuit, this);

  // Set the sizer for this panel
  SetSizer(mainSizer);
}

void VoleurPanel::setUpPanel(std::vector<std::vector<Carte*>>& cartes, std::vector<int>& players){

  for (int i = 0; i < panels.size(); i++) {
    this->panels[i]->Hide();
  }

  for (size_t i = 0; i < cartes.size(); i++) {
    this->texts[i]->SetLabel(  "Player "+std::to_string(players[i])  );
    this->cards[i][0]->updateImage(cartes[i][0]->getNom(),150,240);
    this->cards[i][1]->updateImage(cartes[i][1]->getNom(),150,240);

    this->panels[i]->SetBackgroundColour(PlayPanel::PLAYER_COLOURS[players[i]]);
    this->cards[i][0]->SetBackgroundColour(PlayPanel::PLAYER_COLOURS[players[i]]);
    this->cards[i][1]->SetBackgroundColour(PlayPanel::PLAYER_COLOURS[players[i]]);

    this->panels[i]->Show();
  }
  Layout();
  Refresh();
}


void VoleurPanel::OnQuit(wxEvent& event) {
  wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
  notifyEvent.SetString("Switch");  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
}
