#include <wx/wx.h>
#include <wx/panel.h>
#include <vector>
#include <string>
#include "playPanel.hpp"
#include"wxcard.hpp"

#include "Modele.h"
#include "Carte.h"




PlayPanel::PlayPanel(wxFrame* parent, Modele* model) : wxPanel(parent),parentFrame(parent) {
    m_modele = model;

    // Main sizer for the entire window (horizontal layout)
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    //----------------------------------------------------------------------//
    //------------------LEFT PANEL(yellow)---------------------------------//
    //--------------------------------------------------------------------//
    wxPanel* leftPanel = new wxPanel(this, wxID_ANY);
    //leftPanel->SetBackgroundColour(wxColour(163, 146, 122));//yellow


    // Vertical sizer for left, center, and right panels
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    //---------------------------------------------------------------------//
    //------------------TOP PANEL(dark red)-------------------------------//
    //-------------------------------------------------------------------//
    this->topPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 50));
    //topPanel->SetBackgroundColour(wxColour(163, 146, 122));//reddish
      wxBoxSizer* buttonTopSizer = new wxBoxSizer(wxHORIZONTAL);
      wxButton* resignButton = new wxButton(topPanel, wxID_ANY,"Resign" , wxDefaultPosition, wxSize(80, 30));
      wxButton* quitButton = new wxButton(topPanel, wxID_ANY,"Quit" , wxDefaultPosition, wxSize(80, 30));
      wxButton* saveButton = new wxButton(topPanel, wxID_ANY, "Save" , wxDefaultPosition, wxSize(80, 30));
      resignButton->Bind(wxEVT_BUTTON, &PlayPanel::OnButtonClicked, this);
      quitButton->Bind(wxEVT_BUTTON, &PlayPanel::OnButtonClicked, this);
      saveButton->Bind(wxEVT_BUTTON, &PlayPanel::OnButtonClicked, this);
      buttonTopSizer->Add(quitButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
      buttonTopSizer->Add(resignButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
      buttonTopSizer->Add(saveButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
      topPanel->SetSizer(buttonTopSizer);


    //---------------------------------------------------------------------//
    //------------------Center panel (green)------------------------------//
    //-------------------------------------------------------------------//
    this->centerPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));
    centerPanel->SetBackgroundColour(wxColour(186, 219, 167));//green




    //---------------------------------------------------------------------//
    //------------------Played panel (cyan)------------------------------//
    //-------------------------------------------------------------------//
    this->playedPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 100));
    playedPanel->SetBackgroundColour(wxColour(137, 163, 122));




    //---------------------------------------------------------------------//
    //------------------Bottom panel (Pink)-------------------------------//
    //-------------------------------------------------------------------//
    this->handPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 100));
    handPanel->SetBackgroundColour(wxColour(120, 160, 120));//pink

    // Bottom sizer for played, hand, and small blue panels
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);





    //---------------------------------------------------------------------//
    //------------------Right panel (red)---------------------------------//
    //-------------------------------------------------------------------//
    wxPanel* rightPanel = new wxPanel(this, wxID_ANY,wxDefaultPosition, wxSize(100, -1));
    rightPanel->SetBackgroundColour(wxColour(122, 148, 163));//red




    //---------------------------------------------------------------------//
    //------------------bottom right panel (red)--------------------------//
    //-------------------------------------------------------------------//
    wxPanel* smallBluePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, -1));
    smallBluePanel->SetBackgroundColour(wxColour(122, 148, 163));//blue

    //---------------------------------------------------------------------//
    // Add the panels to their respective sizers
    mainSizer->Add(leftPanel, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(verticalSizer, 5, wxEXPAND | wxALL, 5);
    mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL, 5);

    verticalSizer->Add(topPanel, 0, wxEXPAND | wxBOTTOM, 5);
    verticalSizer->Add(centerPanel, 5, wxEXPAND | wxBOTTOM, 5);
    verticalSizer->Add(playedPanel, 2, wxEXPAND | wxBOTTOM, 5);
    verticalSizer->Add(handPanel, 2, wxEXPAND | wxBOTTOM, 5);

    rightSizer->Add(rightPanel, 4, wxEXPAND | wxRIGHT | wxBOTTOM, 5);
    rightSizer->Add(smallBluePanel, 1, wxEXPAND | wxRIGHT, 5);

    // Set the main sizer for the frame
    SetSizer(mainSizer);
    Layout();

    // afficher les cartes de la reserve
    this->updateReserve();

    // afficher les cartes en main
    this->updateMain();

    // afficher les cartes jouees
    this->updatePlayedPanel();
}



PlayPanel::~PlayPanel(){
}

void PlayPanel::OnButtonClicked(wxCommandEvent& event) {
  //wxLogMessage(name);
  wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
  if (button) {
        wxString buttonName = button->GetLabel();
        //notify parent
        wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
        notifyEvent.SetString(buttonName);  // Include button name in the event
        wxPostEvent(this->parentFrame, notifyEvent); // Send event to parent frame
  }

}


void PlayPanel::updateReserve() {
    // Efface les enfants existants dans centerPanel pour les mettre à jour
    centerPanel->DestroyChildren();

    // Cree deux sizers horizontaux
    wxBoxSizer* reserveSizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* reserveSizer2 = new wxBoxSizer(wxHORIZONTAL);

    // Recupere la reserve dans le modèle
    auto reserve = m_modele->getReserve();

    // Divise les cartes en deux parties
    size_t half = reserve.size() / 2;
    auto it = reserve.begin();

    // Ajoute les cartes dans le 1er sizer
    for (size_t i = 0; i < half; i++, it++) {
        Carte* carte = it->first;
        int quantite = it->second;

        // cree une carte graphique pour chaque carte 
        wxCard* card = new wxCard(centerPanel, carte->getNom(), quantite, 140, 224, 140, 224, wxColour(0, 0, 0));
        reserveSizer1->Add(card, 0, wxALL, 5);
    }

    // Ajoute les cartes dans le 2eme sizer
    for (size_t i = half; i < reserve.size(); i++, it++) {
        Carte* carte = it->first;
        int quantite = it->second;

        // cree une carte graphique pour chaque carte
        wxCard* card = new wxCard(centerPanel, carte->getNom(), quantite, 140, 224, 140, 224, wxColour(0, 0, 0));
        reserveSizer2->Add(card, 0, wxALL, 5);
    }

    // cree un sizer vertical pour organiser les deux sizers horizontaux
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(reserveSizer1, 0, wxALIGN_CENTER);
    mainSizer->Add(reserveSizer2, 0, wxALIGN_CENTER);

    // Applique le nouveau sizer à centerPanel
    centerPanel->SetSizer(mainSizer);
    centerPanel->Layout(); // refresh
}

void PlayPanel::updateMain() {
    // Efface les enfants existants dans handPanel pour les mettre à jour
    handPanel->DestroyChildren();

    // Création d'un sizer horizontal pour afficher la main sur une seule ligne
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* handSizer = new wxBoxSizer(wxHORIZONTAL);

    // Récupère la main du joueur dans le modèle
    auto main = m_modele->getMain();

    // Parcours chaque carte de la main
    for (auto& carte : main) {
        // Ccarte graphique pour chaque carte
        wxCard* card = new wxCard(handPanel, carte->getNom(), 1, 120, 180, 120, 180, wxColour(0, 0, 0));

        // Ajouter la carte au sizer
        handSizer->Add(card, 0, wxALL, 5);
    }

    // Ajoute le sizer des cartes en main au sizer principal
    mainSizer->Add(handSizer, 0, wxALIGN_CENTER);

    // Applique le sizer à handPanel pour afficher les cartes
    handPanel->SetSizer(mainSizer);
    handPanel->Layout(); // rafraichit l'affichage
}


void PlayPanel::updatePlayedPanel(){
    // Efface les enfants existants dans playedPanel pour les mettre à jour
    playedPanel->DestroyChildren();

    // Création d'un sizer horizontal pour afficher la main sur une seule ligne
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* handSizer = new wxBoxSizer(wxHORIZONTAL);

    // Récupère la main du joueur dans le modèle
    auto main = m_modele->getPlayedCards();

    // Parcours chaque carte de la main
    for (auto& carte : main) {
        // Ccarte graphique pour chaque carte
        wxCard* card = new wxCard(playedPanel, carte->getNom(), 1, 120, 180, 120, 180, wxColour(0, 0, 0));

        // Ajouter la carte au sizer
        handSizer->Add(card, 0, wxALL, 5);
    }

    // Ajoute le sizer des cartes en main au sizer principal
    mainSizer->Add(handSizer, 0, wxALIGN_CENTER);

    // Applique le sizer à playedPanel pour afficher les cartes
    playedPanel->SetSizer(mainSizer);
    playedPanel->Layout(); // rafraichit l'affichage
}



