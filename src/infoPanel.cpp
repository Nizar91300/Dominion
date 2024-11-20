#include <wx/wx.h>
#include <wx/panel.h>
#include "infoPanel.hpp"
#include"wxcard.hpp"


InfoPanel::InfoPanel(wxFrame* parent) : wxPanel(parent){

  SetBackgroundColour(wxColour(204, 219, 149));
  wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
  wxCard* informationCard = new wxCard(this, "gold", 1, 250, 400, 250, 400, wxColour(0, 0, 0));
  mainSizer->AddSpacer(200);
  mainSizer->Add(informationCard, 0, wxALIGN_CENTER | wxALL, 5);
  wxStaticText* description = new wxStaticText(this, wxID_ANY, "Title:\nDescription:Nec vox aerebatur acervis \nut saltem speatur impleri.");
  mainSizer->Add(description, 0, wxALIGN_CENTER | wxALL, 5);

  Bind(wxEVT_CHAR_HOOK, &InfoPanel::OnQuit, this);
  Bind(wxEVT_COMMAND_LEFT_CLICK, &InfoPanel::OnQuit, this);
  Bind(wxEVT_COMMAND_RIGHT_CLICK, &InfoPanel::OnQuit, this);
  Bind(wxEVT_BUTTON, &InfoPanel::OnQuit, this);

  SetSizer(mainSizer);
  Layout();

}



InfoPanel::~InfoPanel(){}



void InfoPanel::OnQuit(wxEvent& event) {
  wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
  notifyEvent.SetString("Back");  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
}



void updateImage(){

}
void updateText(){

}
