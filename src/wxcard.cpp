#include <wx/wx.h>
#include"resources.hpp"
#include <wx/statbmp.h>
#include"wxcard.hpp"
#include "Carte.h"


std::vector<std::string>  wxCard::cards = 
{"artisan", "bandit", "bureaucrat", "cellar", "chapel", "copper", "councilRoom", "curse", "duchy", "estate",
 "feast", "festival", "gardens", "gold", "harbinger", "laboratory", "library", "market", "merchant", "militia",
"mine", "moat", "moneylender", "poacher", "province", "remodel", "sentry", "silver", "smithy", "throneRoom",
"vassal", "village", "witch", "woodcutter","workshop"
};


wxCard::wxCard(wxWindow* parent, wxPanel* parentPan, Carte* card, int occurrences, int paneWidth, int paneHeight, int imageWidth, int imageHeight, wxColour backgroundColor)
    : wxCard(parent, parentPan, card->getNom(), occurrences, paneWidth, paneHeight, imageWidth, imageHeight, backgroundColor) {
    m_carte = card;
}



wxCard::wxCard(wxWindow* parent, wxPanel* parentPan, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor) : wxPanel(parent){
  this->SetSize(paneWidth,paneHeight);
  
  m_parentPan = parentPan;
  m_parent = parent;
  
  wxImage image = *(Resources::getInstance()->getImage(imageName));
  wxBitmap resized = wxBitmap( image.Scale( imageWidth, imageHeight /*, wxIMAGE_QUALITY_HIGH*/ ) );;

  this->SetBackgroundColour(backgroundColor);
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticBitmap* imageCtrl = new wxStaticBitmap(this, wxID_ANY, resized);
  mainSizer->Add(imageCtrl, 1, wxEXPAND | wxALL, 5);

  // Create a red square panel in the top-right corner for the count
  wxPanel* countPanel(NULL);
  wxStaticText* countText(NULL);
  if(occurrences>0){
    countPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(15, 15));
    countPanel->SetBackgroundColour(*wxRED);


    wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Comic Sans MS");
    // Center the occurrence text inside the red square
    countText = new wxStaticText(countPanel, wxID_ANY, wxString::Format("%d", occurrences), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    countText->SetForegroundColour(*wxWHITE);
    countText->SetFont(font);

    wxBoxSizer* countSizer = new wxBoxSizer(wxVERTICAL);
    countSizer->Add(countText, 1, wxALIGN_CENTER);
    countPanel->SetSizer(countSizer);

    // Absolute positioning for the count panel in the top-right
    countPanel->SetPosition(wxPoint(0,0)); // Adjust position as needed
  }
  // Add everything to the main sizer
  SetSizer(mainSizer);
  Layout();


  imageCtrl->Bind(wxEVT_LEFT_DOWN, &wxCard::OnMouseClick, this);
  imageCtrl->Bind(wxEVT_RIGHT_DOWN, &wxCard::OnRightClick, this);
  Bind(wxEVT_ENTER_WINDOW, &wxCard::OnMouseEnter, this);
  Bind(wxEVT_LEAVE_WINDOW, &wxCard::OnMouseLeave, this);
}


wxCard::wxCard(wxWindow* parent, wxPanel* parentPan, const std::string& imageName, int occurrences) : wxCard::wxCard(parent, parentPan,imageName,occurrences,250,400,250,400,wxColour(177, 168, 189)){}



wxCard::~wxCard(){}


void wxCard::UpdateOccurrences(int occurrences) {
  /*wxStaticText* countText = dynamic_cast<wxStaticText*>(FindWindowByLabel(wxString::Format("%d", occurrences - 1)));
  if (countText) {
    countText->SetLabel(wxString::Format("%d", occurrences));
    Layout(); // Refresh layout if count changes
  }*/
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
      std::cout << "/* MOUSE ENTERED */" << '\n';
        event.Skip();
}

void wxCard::OnMouseLeave(wxMouseEvent& event) {
        std::cout << "/* MOUSE LEFT */" << '\n';
        event.Skip();
}
