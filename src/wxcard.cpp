#include <wx/wx.h>
#include <wx/statbmp.h>
#include<string>
#include<vector>
#include"resources.hpp"
#include"wxcard.hpp"



std::vector<std::string>  wxCard::ActionCards = {"artisan", "bandit", "bureaucrat", "cellar", "chapel",  "councilRoom",
 "feast", "festival", "gardens", "harbinger", "laboratory", "library", "market", "merchant", "militia",
"mine", "moat", "moneylender", "poacher","remodel", "sentry",  "smithy", "throneRoom",
"vassal", "village", "witch", "woodcutter","workshop"
};
std::vector<std::string>  wxCard::OtherCards = {"copper", "curse", "duchy", "estate", "province", "silver", "smithy", "gold"};



wxCard::wxCard(wxWindow* parent, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor)
          : wxPanel(parent),m_name(imageName),m_occurrences(occurrences){

  this->SetSize(paneWidth,paneHeight);
  this->SetBackgroundColour(backgroundColor);
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  //--------------------image--------------------
  wxImage image = *(Resources::getInstance()->getImage(imageName));
  wxBitmap resized = wxBitmap( image.Scale( imageWidth, imageHeight) );;
  wxStaticBitmap* imageCtrl = new wxStaticBitmap(this, wxID_ANY, resized);
  mainSizer->Add(imageCtrl, 1, wxEXPAND | wxALL, 5);

  //--------------------count--------------------

  this->countPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(15, 15));
  this->countPanel->SetBackgroundColour(*wxRED);

  wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Comic Sans MS");
  this->countText = new wxStaticText(countPanel, wxID_ANY, wxString::Format("%d", occurrences), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  this->countText->SetForegroundColour(*wxWHITE);
  this->countText->SetFont(font);

  wxBoxSizer* countSizer = new wxBoxSizer(wxVERTICAL);
  countSizer->Add(countText, 1, wxALIGN_CENTER);
  countPanel->SetSizer(countSizer);
  countPanel->SetPosition(wxPoint(0,0));

  if(occurrences<2){
    this->countPanel->Hide();
  }

  SetSizer(mainSizer);
  Layout();
  //--------------------events--------------------
  imageCtrl->Bind(wxEVT_LEFT_DOWN, &wxCard::OnMouseClick, this);
  imageCtrl->Bind(wxEVT_ENTER_WINDOW, &wxCard::OnMouseEnter, this);
  imageCtrl->Bind(wxEVT_LEAVE_WINDOW, &wxCard::OnMouseLeave, this);

}


wxCard::wxCard(wxWindow* parent, const std::string& imageName, int occurrences) :
      wxCard::wxCard(parent,imageName,occurrences,250,400,250,400,wxColour(177, 168, 189)){}



wxCard::~wxCard(){}


void wxCard::UpdateOccurrences(int occurrences) {
  this->m_occurrences = occurrences;
  this->countText->SetLabel(wxString::Format("%d", occurrences));
  if(occurrences<2){
    this->countPanel->Hide();
  }
  Layout();
}


void wxCard::OnMouseEnter(wxMouseEvent& event){
  wxCommandEvent notifyEvent(wxEVT_BUTTON, 1);
  notifyEvent.SetString(m_name);  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
  event.Skip();
}


void wxCard::OnMouseLeave(wxMouseEvent& event){
  wxCommandEvent notifyEvent(wxEVT_BUTTON, 2);
  notifyEvent.SetString(m_name);  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
  event.Skip();
}


void wxCard::OnMouseClick(wxMouseEvent& event){
  wxCommandEvent notifyEvent(wxEVT_BUTTON, 3);
  notifyEvent.SetString(m_name);  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
  event.Skip();
}
