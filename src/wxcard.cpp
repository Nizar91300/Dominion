#include <wx/wx.h>
#include <wx/statbmp.h>
#include<string>
#include<vector>
#include"resources.hpp"
#include"wxcard.hpp"
#include "Carte.h"



std::vector<std::string>  wxCard::ActionCards = {"artisan", "bandit", "bureaucrat", "cellar", "chapel",  "councilRoom",
 "feast", "festival", "gardens", "harbinger", "laboratory", "library", "market", "merchant", "militia",
"mine", "moat", "moneylender", "poacher","remodel", "sentry",  "smithy", "throneRoom",
"vassal", "village", "witch", "woodcutter","workshop"
};
std::vector<std::string>  wxCard::OtherCards = {"copper", "curse", "duchy", "estate", "province", "silver", "smithy", "gold"};


wxCard::wxCard(wxWindow* parent, wxPanel* parentPan, Carte* card, int occurrences, int paneWidth, int paneHeight, int imageWidth, int imageHeight, wxColour backgroundColor)
    : wxCard(parent, parentPan, card->getNom(), occurrences, paneWidth, paneHeight, imageWidth, imageHeight, backgroundColor) {
    m_carte = card;
}



wxCard::wxCard(wxWindow* parent, wxPanel* parentPan, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor) : wxPanel(parent){
  this->SetSize(paneWidth,paneHeight);
  
  m_parentPan = parentPan;
  m_parent = parent;

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
  //imageCtrl->Bind(wxEVT_ENTER_WINDOW, &wxCard::OnMouseEnter, this);
  //imageCtrl->Bind(wxEVT_LEAVE_WINDOW, &wxCard::OnMouseLeave, this);


  imageCtrl->Bind(wxEVT_LEFT_DOWN, &wxCard::OnMouseClick, this);
  imageCtrl->Bind(wxEVT_RIGHT_DOWN, &wxCard::OnRightClick, this);
  Bind(wxEVT_ENTER_WINDOW, &wxCard::OnMouseEnter, this);
  Bind(wxEVT_LEAVE_WINDOW, &wxCard::OnMouseLeave, this);
}


wxCard::wxCard(wxWindow* parent,wxPanel* parentPanel, const std::string& imageName, int occurrences) : wxCard::wxCard(parent, parentPanel,imageName,occurrences,250,400,250,400,wxColour(177, 168, 189)){}



wxCard::~wxCard(){}


void wxCard::UpdateOccurrences(int occurrences) {
  this->m_occurrences = occurrences;
  this->countText->SetLabel(wxString::Format("%d", occurrences));
  if(occurrences<2){
    this->countPanel->Hide();
  }
  Layout();
}



void wxCard::OnMouseClick(wxMouseEvent& event) {
    wxCommandEvent notifyEvent(wxEVT_COMMAND_LEFT_CLICK, GetId());
    std::pair <Carte*, wxWindow*>* data = new std::pair<Carte*, wxWindow*>(m_carte, m_parent);

    notifyEvent.SetClientData(static_cast<void*>(data));
    wxPostEvent(m_parentPan, notifyEvent);  // Notify the parent
    std::cout << "/* MOUSE CLICKED : event propage au parent */" << '\n';
    event.Skip();
}

void wxCard::OnRightClick(wxMouseEvent& event) {
    wxCommandEvent notifyEvent(wxEVT_RIGHT_DOWN, GetId());
    notifyEvent.SetString("Right Click");  // Include information about the event type
    wxPostEvent(m_parentPan, notifyEvent);  // Notify the parent
    event.Skip();
}

void wxCard::OnMouseEnter(wxMouseEvent& event) {
    wxCommandEvent notifyEvent(wxEVT_BUTTON, 1);
    notifyEvent.SetString(m_name);  // Include button name in the event
    wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
    event.Skip();
}

void wxCard::OnMouseLeave(wxMouseEvent& event) {
    wxCommandEvent notifyEvent(wxEVT_BUTTON, 2);
    notifyEvent.SetString(m_name);  // Include button name in the event
    wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
    event.Skip();
}
