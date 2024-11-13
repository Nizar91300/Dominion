#include <wx/wx.h>
#include"resources.hpp"
#include <wx/statbmp.h>
#include"wxcard.hpp"


std::vector<std::string>  wxCard::cards = {"estate", "duchy", "province", "curse","copper","silver","gold"};
/*
wxCard::wxCard(wxWindow* parent, const std::string& imageName, int occurrences) : wxPanel(parent){
  this->SetSize(250,400);
  wxImage image = Resources::getInstance().getImage(imageName);
  wxBitmap resized = wxBitmap( image.Scale( 250, 400 ) );;

  this->SetBackgroundColour(wxColour(0, 128, 0));
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticBitmap* imageCtrl = new wxStaticBitmap(this, wxID_ANY, resized);
  mainSizer->Add(imageCtrl, 1, wxEXPAND | wxALL, 5);

  // Create a red square panel in the top-right corner for the count
  wxPanel* countPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(30, 30));
  countPanel->SetBackgroundColour(*wxRED);


  wxFont font(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Comic Sans MS");
  // Center the occurrence text inside the red square
  wxStaticText* countText = new wxStaticText(countPanel, wxID_ANY, wxString::Format("%d", occurrences), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  countText->SetForegroundColour(*wxWHITE);
  countText->SetFont(font);

  wxBoxSizer* countSizer = new wxBoxSizer(wxVERTICAL);
  countSizer->Add(countText, 1, wxALIGN_CENTER);
  countPanel->SetSizer(countSizer);

  // Absolute positioning for the count panel in the top-right
  countPanel->SetPosition(wxPoint(0,0)); // Adjust position as needed

  // Add everything to the main sizer
  SetSizer(mainSizer);
  Layout();
}*/
wxCard::wxCard(wxWindow* parent, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor) : wxPanel(parent){
  this->SetSize(paneWidth,paneHeight);
  wxImage image = *(Resources::getInstance()->getImage(imageName));  //todo !!!!!!
  wxBitmap resized = wxBitmap( image.Scale( imageWidth, imageHeight /*, wxIMAGE_QUALITY_HIGH*/ ) );;

  this->SetBackgroundColour(backgroundColor);
  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticBitmap* imageCtrl = new wxStaticBitmap(this, wxID_ANY, resized);
  mainSizer->Add(imageCtrl, 1, wxEXPAND | wxALL, 5);

  // Create a red square panel in the top-right corner for the count
  wxPanel* countPanel;
  wxStaticText* countText;
  if(occurrences>0){
    countPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(30, 30));
    countPanel->SetBackgroundColour(*wxRED);


    wxFont font(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Comic Sans MS");
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
}


wxCard::wxCard(wxWindow* parent, const std::string& imageName, int occurrences) : wxCard::wxCard(parent,imageName,occurrences,250,400,250,400,wxColour(177, 168, 189)){}



wxCard::~wxCard(){}


void wxCard::UpdateOccurrences(int occurrences) {
  /*wxStaticText* countText = dynamic_cast<wxStaticText*>(FindWindowByLabel(wxString::Format("%d", occurrences - 1)));
  if (countText) {
    countText->SetLabel(wxString::Format("%d", occurrences));
    Layout(); // Refresh layout if count changes
  }*/
}
