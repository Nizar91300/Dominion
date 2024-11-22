#include <wx/wx.h>
#include <wx/panel.h>
#include"endGame.hpp"


EndGame::EndGame(wxWindow* parent) : wxPanel(parent){


  this->sizer = new wxBoxSizer(wxVERTICAL);


  wxFont comicFont(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Comic Sans MS");
  wxStaticText* text = new wxStaticText(this, wxID_ANY, "The End");
  text->SetFont(comicFont);
  this->sizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 50);



  Bind(wxEVT_CHAR_HOOK, &EndGame::OnQuit, this);
  Bind(wxEVT_LEFT_DOWN, &EndGame::OnQuit, this);
  Bind(wxEVT_RIGHT_DOWN, &EndGame::OnQuit, this);

  SetSizer(this->sizer);
  Layout();

}



EndGame::~EndGame(){}



void EndGame::OnQuit(wxEvent& event) {
  wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
  notifyEvent.SetString("Quit");  // Include button name in the event
  wxPostEvent(this->GetParent()->GetParent(), notifyEvent); // Send event to parent frame
}



void EndGame::setUpPanel(std::vector<int>& points){

  this->SetBackgroundColour(wxColour(175, 201, 198));
  wxFont comicFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Comic Sans MS");
  for (int i = 0; i < points.size(); ++i) {
      std::string joueurText = "Joueur " + std::to_string(i + 1) + " : " + std::to_string(points[i]) + " points de victoire";
      wxStaticText* playerLabel = new wxStaticText(this, wxID_ANY, joueurText);
      playerLabel->SetFont(comicFont);
      this->sizer->Add(playerLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  }
  Layout();
  Refresh();
}
