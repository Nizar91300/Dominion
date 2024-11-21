#include <wx/wx.h>
#include <wx/panel.h>
#include "infoPanel.hpp"
#include"wxcard.hpp"


InfoPanel::InfoPanel(wxWindow* parent) : wxPanel(parent){

  SetBackgroundColour(wxColour(204, 219, 149));
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);


  wxFont comicFont(30, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Comic Sans MS");
  wxStaticText* text = new wxStaticText(this, wxID_ANY, "Click on the mouse or in the keyboard to exit");
  text->SetFont(comicFont);
  mainSizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 50);

  this->informationCard = new wxCard(this, "gold", 1, 300, 480, 300, 480, wxColour(0, 0, 0));
  mainSizer->Add(informationCard, 0, wxALIGN_CENTER | wxALL, 0);

  Bind(wxEVT_CHAR_HOOK, &InfoPanel::OnQuit, this);
  Bind(wxEVT_LEFT_DOWN, &InfoPanel::OnQuit, this);
  Bind(wxEVT_RIGHT_DOWN, &InfoPanel::OnQuit, this);

  SetSizer(mainSizer);
  Layout();

}



InfoPanel::~InfoPanel(){}



void InfoPanel::OnQuit(wxEvent& event) {
  wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
  notifyEvent.SetString("Switch");  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
}

void InfoPanel::updateImage(std::string imageName){
  this->informationCard->updateImage(imageName,250,400);
}
