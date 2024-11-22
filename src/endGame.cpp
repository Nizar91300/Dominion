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
      std::string joueurText = "Player " + std::to_string(i + 1) + " : " + std::to_string(points[i]) + " victory points.";
      wxStaticText* playerLabel = new wxStaticText(this, wxID_ANY, joueurText);
      playerLabel->SetFont(comicFont);
      this->sizer->Add(playerLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  }

  this->sizer->AddSpacer(20);

  // afficher le gagant et le score mais tenir compte des ex aequo
  int max = points[0];
  std::vector<int> winners;

  for (int i = 0; i < points.size(); ++i) {
      if (points[i] > max) {
          max = points[i];
          winners.clear();
          winners.push_back(i);
      }
      else if (points[i] == max) {
          winners.push_back(i);
      }
  }

  if (winners.size() == 1) {
      std::string winnerText = "Player " + std::to_string(winners[0] + 1) + " has won with a score of " + std::to_string(max) + " victory points.";
      wxStaticText* winnerLabel = new wxStaticText(this, wxID_ANY, winnerText);
      winnerLabel->SetFont(comicFont);
      this->sizer->Add(winnerLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  }
  else {
      std::string winnerText = "The players ";
      for (int i = 0; i < winners.size(); ++i) {
          winnerText += std::to_string(winners[i] + 1);
          if (i < winners.size() - 1) {
              winnerText += ", ";
          }
      }
      winnerText += " have won with a score of " + std::to_string(max) + " victory points.";
      wxStaticText* winnerLabel = new wxStaticText(this, wxID_ANY, winnerText);
      winnerLabel->SetFont(comicFont);
      this->sizer->Add(winnerLabel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
  }


  Layout();
  Refresh();
}
