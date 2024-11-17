#include <wx/wx.h>
#include <wx/panel.h>
#include <vector>
#include <string>
#include "playPanel.hpp"
#include"wxcard.hpp"

#include "Modele.h"
#include "Carte.h"




PlayPanel::PlayPanel(wxFrame* parent, Modele* model) : wxPanel(parent),m_modele(model) {

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);


    this->mainPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    //------------------LEFT---------------------------------//
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* leftTopPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));
    wxPanel* leftPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));

    leftSizer->Add(leftTopPanel, 1, wxEXPAND | wxLEFT | wxBOTTOM, 1);
    leftSizer->Add(leftPanel, 4, wxEXPAND | wxLEFT, 1);




    //------------------CENTER---------------------------------//
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    //----------------//
    this->topPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 40));
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


    //----------------//
    this->centerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    centerPanel->SetBackgroundColour(wxColour(186, 219, 167));//green

    //----------------//
    this->playedPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    playedPanel->SetBackgroundColour(wxColour(137, 163, 122));

    //----------------//
    this->handPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    handPanel->SetBackgroundColour(wxColour(120, 160, 120));//pink


    verticalSizer->Add(topPanel, 0, wxEXPAND | wxBOTTOM, 1);
    verticalSizer->Add(centerPanel, 5, wxEXPAND | wxBOTTOM, 1);
    verticalSizer->Add(playedPanel, 2, wxEXPAND | wxBOTTOM, 1);
    verticalSizer->Add(handPanel, 2, wxEXPAND | wxBOTTOM, 1);


    //------------------Right---------------------------------//
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel* rightPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));
    rightPanel->SetBackgroundColour(wxColour(122, 148, 163));//red
    wxPanel* rightBottomPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, -1));
    rightBottomPanel->SetBackgroundColour(wxColour(122, 148, 163));//blue
    rightSizer->Add(rightPanel, 4, wxEXPAND | wxRIGHT | wxBOTTOM, 1);
    rightSizer->Add(rightBottomPanel, 1, wxEXPAND | wxRIGHT, 1);


    //---------------------------------------------------------------------//
    // Add the panels to their respective sizers
    mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL, 2);
    mainSizer->Add(verticalSizer, 5, wxEXPAND | wxALL, 2);
    mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL, 2);
    mainPanel->SetSizer(mainSizer);



    this->informationPanel = new wxPanel(this,wxID_ANY);
    informationPanel->SetBackgroundColour(wxColour(204, 219, 149));


    sizer->Add(mainPanel, 1, wxEXPAND | wxALL, 0);
    sizer->Add(informationPanel, 1, wxEXPAND | wxALL, 0);
    informationPanel->Hide();
    this->SetSizer(sizer);
    this->Layout();

    // afficher les cartes de la reserve
    //this->updateReserve();
    // afficher les cartes en main
    //this->updateMain();
    // afficher les cartes jouees
    //this->updatePlayedCards();


    Bind(wxEVT_CHAR_HOOK, &PlayPanel::onKeyPress, this);
}



PlayPanel::~PlayPanel(){
}



void PlayPanel::onKeyPress(wxKeyEvent& event) {
        // Check for a specific key (e.g., 'T' key to toggle)
        if (event.GetKeyCode() == 27) {
            if (mainPanel->IsShown()) {
                mainPanel->Hide();
                informationPanel->Show();
                informationPanel->SetFocus();
            } else {
                informationPanel->Hide();
                mainPanel->Show();
                mainPanel->SetFocus();
            }
            // Re-layout to apply changes
            this->Layout();
        } else {
            // Pass unhandled key events to the default handler
            event.Skip();
        }
    }













void PlayPanel::OnButtonClicked(wxCommandEvent& event) {
  /*//wxLogMessage(name);
  wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
  if (button) {
        wxString buttonName = button->GetLabel();
        //notify parent
        wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
        notifyEvent.SetString(buttonName);  // Include button name in the event
        wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
  }*/

}


void PlayPanel::updateReserve() {
    /*// Efface les enfants existants dans centerPanel pour les mettre à jour
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
        wxCard* card = new wxCard(centerPanel, carte->getNom(), quantite, 100, 160, 100, 160, wxColour(0, 0, 0));
        reserveSizer1->Add(card, 0, wxALL, 5);
    }

    // Ajoute les cartes dans le 2eme sizer
    for (size_t i = half; i < reserve.size(); i++, it++) {
        Carte* carte = it->first;
        int quantite = it->second;

        // cree une carte graphique pour chaque carte
        wxCard* card = new wxCard(centerPanel, carte->getNom(), quantite, 100, 160, 100, 160, wxColour(0, 0, 0));
        reserveSizer2->Add(card, 0, wxALL, 5);
    }

    // cree un sizer vertical pour organiser les deux sizers horizontaux
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(reserveSizer1, 0, wxALIGN_CENTER);
    mainSizer->Add(reserveSizer2, 0, wxALIGN_CENTER);

    // Applique le nouveau sizer à centerPanel
    centerPanel->SetSizer(mainSizer);
    centerPanel->Layout(); // refresh*/
}



// Met a jour l'affichage d'un panel avec une liste de cartes donne
void PlayPanel::updatePanel(wxPanel* pan, std::vector< std::pair<Carte*, int> > cartes) {
    /*// Efface les enfants existants dans pan pour les mettre à jour
    pan->DestroyChildren();

    // Création d'un sizer horizontal pour afficher la main sur une seule ligne
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* panSizer = new wxBoxSizer(wxHORIZONTAL);

    // Parcours chaque carte de la main
    for (auto& carte : cartes) {
        Carte* c = carte.first;
        int quantite = carte.second;

        // Ccarte graphique pour chaque carte
        wxCard* card = new wxCard(pan, c->getNom(), quantite, 50, 80, 50, 80, wxColour(0, 0, 0));

        // Ajouter la carte au sizer
        panSizer->Add(card, 0, wxALL, 5);
    }

    // Ajoute le sizer des cartes en main au sizer principal
    mainSizer->Add(panSizer, 0, wxALIGN_CENTER);

    // Applique le sizer à pan pour afficher les cartes
    pan->SetSizer(mainSizer);
    pan->Layout(); // rafraichit l'affichage*/
}


// rafrachit l'affichage des cartes en main
void PlayPanel::updateMain() {
    /*// Recupere les cartes en main dans le modele
    auto main = m_modele->getMain();

    // Ajoute les cartes dans le sizer
    updatePanel(handPanel, main);*/
}

// rafrachit l'affichage des cartes jouees
void PlayPanel::updatePlayedCards() {
    /*// Recupere les cartes jouees dans le modele
    auto played = m_modele->getPlayedCards();

    // Ajoute les cartes dans le sizer
    updatePanel(playedPanel, played);*/
}
