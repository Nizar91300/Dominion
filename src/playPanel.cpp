#include <wx/wx.h>
#include <wx/panel.h>
#include <vector>
#include <string>

#include "playPanel.hpp"
#include"wxcard.hpp"
#include"infoPanel.hpp"
#include"endGame.hpp"

#include "Modele.h"
#include "Carte.h"


std::vector<wxColour> PlayPanel::PLAYER_COLOURS={wxColour(250, 112, 124),wxColour(252, 114, 218),wxColour(59, 59, 245),wxColour(129, 232, 252),wxColour(241, 245, 184),wxColour(245, 198, 176)};



PlayPanel::PlayPanel(wxFrame* parent, Modele* model) : wxPanel(parent),m_modele(model) {

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    this->mainPanel = new wxPanel(this,wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    //------------------LEFT---------------------------------//
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);




    //---------Left top panel-------//
    wxPanel* leftTopPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));
    wxBoxSizer* buttonTopSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* resignButton = new wxButton(leftTopPanel, wxID_ANY,"Resign" , wxDefaultPosition, wxSize(80, 30));
    wxButton* quitButton = new wxButton(leftTopPanel, wxID_ANY,"Quit" , wxDefaultPosition, wxSize(80, 30));
    wxButton* saveButton = new wxButton(leftTopPanel, wxID_ANY, "Save" , wxDefaultPosition, wxSize(80, 30));
    resignButton->Bind(wxEVT_BUTTON, &PlayPanel::OnResign, this);
    quitButton->Bind(wxEVT_BUTTON, &PlayPanel::OnQuit, this);
    saveButton->Bind(wxEVT_BUTTON, &PlayPanel::OnSave, this);
    buttonTopSizer->Add(quitButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonTopSizer->Add(resignButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    buttonTopSizer->Add(saveButton, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    leftTopPanel->SetSizer(buttonTopSizer);

    //---------Left mid panel-------//
    wxPanel* leftMidPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));

    //---------Left stats panel-------//
    wxPanel* statsPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));
    wxBoxSizer* statsSizer = new wxBoxSizer(wxVERTICAL);

    this->actionsText = new wxStaticText(statsPanel, wxID_ANY, "Remaining actions: 1" , wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    this->achatText = new wxStaticText(statsPanel, wxID_ANY, "Remaining purchases: 0" , wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    this->piecesText = new wxStaticText(statsPanel, wxID_ANY, "Remaining coins: 0" , wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);


    wxFont font = wxFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial");

    actionsText->SetFont(font);
    achatText->SetFont(font);
    piecesText->SetFont(font);


    statsSizer->Add(actionsText, 1, wxALIGN_CENTER | wxALL, 5);
    statsSizer->Add(achatText, 1, wxALIGN_CENTER | wxALL, 5);
    statsSizer->Add(piecesText, 1, wxALIGN_CENTER | wxALL, 5);


    statsPanel->SetSizer(statsSizer);


    //---------Left defausse panel-------//
    this->defaussePanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));


    leftSizer->Add(leftTopPanel, 0, wxEXPAND | wxLEFT | wxBOTTOM, 1);
    leftSizer->Add(leftMidPanel, 5, wxEXPAND | wxLEFT, 1);
    leftSizer->Add(statsPanel, 2, wxEXPAND | wxLEFT, 1);
    leftSizer->Add(defaussePanel, 2, wxEXPAND | wxLEFT, 1);




    //------------------CENTER---------------------------------//
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 40));
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    this->topText = new wxStaticText(topPanel, wxID_ANY, "Dominion", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    topText->SetFont(font);

    // Ajouter le texte avec un espace flexible pour le centrer verticalement
    topSizer->Add(topText, 1, wxEXPAND | wxALL, 5);

    topPanel->SetSizer(topSizer);


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
    this->rightPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition, wxSize(100, -1));
    rightPanel->SetBackgroundColour(wxColour(122, 148, 163));//red

    wxBoxSizer* rightPanelSizer = new wxBoxSizer(wxVERTICAL);
    wxFont comicFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Comic Sans MS");

    int nbHumans = m_modele->getNbHumans();
    for (int i = 0; i < this->m_modele->getNbJoueurs(); i++) {

      wxPanel* rectanglePanel = new wxPanel(rightPanel, wxID_ANY);
      rectanglePanel->SetBackgroundColour(PLAYER_COLOURS[i]);
      rectanglePanel->SetOwnBackgroundColour(PLAYER_COLOURS[i]);
      rectanglePanel->SetOwnForegroundColour(wxColour(202, 227, 215));
      rectanglePanel->SetWindowStyle(wxBORDER_SIMPLE);
      wxStaticText* text = new wxStaticText(rectanglePanel, wxID_ANY, "Player "+std::to_string(i+1));
      if(i >= nbHumans){
        text->SetLabel("Bot "+std::to_string(i+1-nbHumans));
      }
      text->SetFont(comicFont);
      wxBoxSizer* rectangleSizer = new wxBoxSizer(wxVERTICAL);
      rectangleSizer->Add(text, 0, wxALIGN_CENTER | wxALL, 5); // Padding around the text
      rectanglePanel->SetSizer(rectangleSizer);
      rightPanelSizer->Add(rectanglePanel, 0, wxALIGN_CENTER | wxTOP, 40);
    }
    rightPanel->SetSizer(rightPanelSizer);


    wxPanel* rightBottomPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, -1));
    wxSizer* rightBottomSizer = new wxBoxSizer(wxVERTICAL);

    tourBtn = new wxButton(rightBottomPanel, wxID_ANY, "END ACTION PHASE", wxDefaultPosition, wxSize(100, 30));
    tourBtn->Bind(wxEVT_BUTTON, &PlayPanel::OnTourButtonClicked, this);

    wxButton* endBtn = new wxButton(rightBottomPanel, wxID_ANY, "END GAME NOW", wxDefaultPosition, wxSize(100, 30));
    endBtn->Bind(wxEVT_BUTTON, &PlayPanel::OnEndButtonClicked, this);

    rightBottomSizer->Add(tourBtn, 0, wxEXPAND | wxALL , 5);
    rightBottomSizer->Add(endBtn, 0, wxEXPAND | wxALL , 5);

    rightBottomPanel->SetSizer(rightBottomSizer);

    rightBottomPanel->SetBackgroundColour(wxColour(122, 148, 163));//blue
    rightSizer->Add(rightPanel, 4, wxEXPAND | wxRIGHT | wxBOTTOM, 1);
    rightSizer->Add(rightBottomPanel, 1, wxEXPAND | wxRIGHT, 1);

    //---------------------------------------------------------------------//
    // Add the panels to their respective sizers
    mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL, 2);
    mainSizer->Add(verticalSizer, 5, wxEXPAND | wxALL, 2);
    mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL, 2);
    mainPanel->SetSizer(mainSizer);

    //info panel
    this->informationPanel = new InfoPanel(this);
    //voleur panel
    this->voleurPanel = new VoleurPanel(this);

    this->endGamePanel=new EndGame(this);

    sizer->Add(mainPanel, 1, wxEXPAND | wxALL, 0);
    sizer->Add(informationPanel, 1, wxEXPAND | wxALL, 0);
    sizer->Add(voleurPanel, 1, wxEXPAND | wxALL, 0);
    sizer->Add(endGamePanel, 1, wxEXPAND | wxALL, 0);
    endGamePanel->Hide();
    informationPanel->Hide();
    voleurPanel->Hide();
    mainPanel->SetFocus();
    this->SetSizer(sizer);
    this->Layout();


    Bind(wxEVT_COMMAND_RIGHT_CLICK, &PlayPanel::onCardInfo, this);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &PlayPanel::onCardInfoReturn, this);
    Bind(wxEVT_COMMAND_LEFT_CLICK, &PlayPanel::onLeftClicked, this);


    update();
    refreshPlayer();
}



PlayPanel::~PlayPanel(){}



void PlayPanel::OnQuit(wxCommandEvent& event) {
    // empecher le joueur de toucher a l'interface si c'est un bot
    if(m_modele->isBotPlaying()){
        return;
    }
    wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
    notifyEvent.SetString("Quit");  // Include button name in the event
    wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
}

void PlayPanel::OnSave(wxCommandEvent& event) {
    // empecher le joueur de toucher a l'interface si c'est un bot
    if(m_modele->isBotPlaying()){
        return;
    }
    //todo
}

void PlayPanel::OnResign(wxCommandEvent& event) {
    // empecher le joueur de toucher a l'interface si c'est un bot
    if(m_modele->isBotPlaying()){
        return;
    }
  //todo
}

void PlayPanel::onCardInfo(wxCommandEvent& event) {
    std::string stlstring = std::string(event.GetString().mb_str());
    if(stlstring.empty() || !this->mainPanel->IsShown()) return;
    this->informationPanel->updateImage(stlstring);
    this->mainPanel->Hide();
    this->informationPanel->Show();
    this->informationPanel->SetFocus();
    Layout();
}

void PlayPanel::onCardInfoReturn(wxCommandEvent& event) {
    if(event.GetString()=="Switch"){
      this->informationPanel->Hide();
      this->voleurPanel->Hide();
      this->mainPanel->Show();
      this->mainPanel->SetFocus();
      Layout();
    }
}


void PlayPanel::refreshPlayer(){
  int i =  m_modele->getJoueurActif();
  this->handPanel->SetBackgroundColour(PLAYER_COLOURS[i]);
  this->rightPanel->SetBackgroundColour(PLAYER_COLOURS[i]);
  this->voleurPanel->SetBackgroundColour(PLAYER_COLOURS[i]);
  Layout();
  Refresh();
}

void PlayPanel::OnTourButtonClicked(wxCommandEvent& event) {
    // empecher le joueur de jouer si c'est un bot
    if(m_modele->isBotPlaying()){
        return;
    }
    m_modele->endPhase();
}

void PlayPanel::OnEndButtonClicked(wxCommandEvent& event) {
    // empecher le joueur de jouer si c'est un bot
    if(m_modele->isBotPlaying()){
        return;
    }
    m_modele->endGame();
}

void PlayPanel::onLeftClicked(wxCommandEvent& event) {
    // empecher le joueur de jouer si c'est un bot
    if(m_modele->isBotPlaying()){
        return;
    }

    std::pair <Carte*, wxWindow*>* data = static_cast< std::pair <Carte*, wxWindow*>* >(event.GetClientData());
    if (data) {
        Carte* clickedCard = data->first;
        wxWindow* parent = data->second;

        // si on veut acheter une carte
        if (parent == centerPanel){
            m_modele->acheterCarteAvecVerif(clickedCard);
        }
        // si on veut jouer une carte
        else if (parent == handPanel){
            m_modele->jouerCarte(clickedCard);
        }
    }

    delete data;
}






// FONCTION DE MISE A JOUR DE L'AFFICHAGE

// Met a jour tout l'affichage
void PlayPanel::update() {
    // Met a jour l'affichage de la reserve
    updateReserve();

    // Met a jour l'affichage des cartes en main
    updateMain();

    // Met a jour l'affichage des cartes jouees
    updatePlayedCards();

    // Met a jour le texte en haut de la fenetre
    updateShownText();

    // update la defausse
    updateDefausse();

    // update les stats
    updateStats();
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
        wxCard* card = new wxCard(centerPanel, carte, quantite, 100, 160, 100, 160, wxColour(0, 0, 0));
        reserveSizer1->Add(card, 0, wxALL, 5);
    }

    // Ajoute les cartes dans le 2eme sizer
    for (size_t i = half; i < reserve.size(); i++, it++) {
        Carte* carte = it->first;
        int quantite = it->second;

        // cree une carte graphique pour chaque carte
        wxCard* card = new wxCard(centerPanel, carte, quantite, 100, 160, 100, 160, wxColour(0, 0, 0));
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


// Met a jour l'affichage d'un panel avec une liste de cartes donne
void PlayPanel::updatePanel(wxPanel* pan, std::vector< std::pair<Carte*, int> > cartes) {
    // Efface les enfants existants dans pan pour les mettre à jour
    pan->DestroyChildren();

    // Création d'un sizer horizontal pour afficher la main sur une seule ligne
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* panSizer = new wxBoxSizer(wxHORIZONTAL);

    // Parcours chaque carte de la main
    for (auto& carte : cartes) {
        Carte* c = carte.first;
        int quantite = carte.second;

        // Ccarte graphique pour chaque carte
        wxCard* card = new wxCard(pan, c, quantite, 100, 160, 100, 160, wxColour(0, 0, 0));

        // Ajouter la carte au sizer
        panSizer->Add(card, 0, wxALL, 5);
    }

    // Ajoute le sizer des cartes en main au sizer principal
    mainSizer->Add(panSizer, 0, wxALIGN_CENTER);

    // Applique le sizer à pan pour afficher les cartes
    pan->SetSizer(mainSizer);
    pan->Layout(); // rafraichit l'affichage
}


// rafrachit l'affichage des cartes en main
void PlayPanel::updateMain() {
    // Recupere les cartes en main dans le modele
    auto main = m_modele->getMain();
    // Ajoute les cartes dans le sizer
    updatePanel(handPanel, main);
}

// rafrachit l'affichage des cartes jouees
void PlayPanel::updatePlayedCards() {
    // Recupere les cartes jouees dans le modele
    auto played = m_modele->getPlayedCards();

    // Ajoute les cartes dans le sizer
    updatePanel(playedPanel, played);
}

// update la carte afficher dans la defausse
void PlayPanel::updateDefausse(){
    // Efface les enfants existants dans defaussePanel pour les mettre à jour
    defaussePanel->DestroyChildren();

    // Recupere la defausse dans le modele
    auto defausse = m_modele->getDefausse();

    if(defausse.empty()) return;


    // Création d'un sizer horizontal pour afficher la defausse sur une seule ligne
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Carte graphique pour la derniere carte
    wxCard* card = new wxCard(defaussePanel, defausse.back(), defausse.size(), 100, 160, 100, 160, wxColour(0, 0, 0));

    // Ajouter la carte au sizer
    mainSizer->Add(card, 0, wxALIGN_CENTER | wxALL, 5);

    // Applique le sizer à defaussePanel pour afficher les cartes
    defaussePanel->SetSizer(mainSizer);
    defaussePanel->Layout(); // rafraichit l'affichage

}

// affiche le texte en haut de la fenetre
void PlayPanel::updateShownText() {
    // Met a jour le texte
    int tourAction = m_modele->getTourAction();
    if(tourAction){
        tourBtn->SetLabel("END ACTION PHASE");
        refreshPlayer();
    }else{
        tourBtn->SetLabel("END BUY PHASE");
    }

    if(m_modele->getAchatSuiteAction()){
        topText->SetLabel("You can buy a card of a cost up to " + std::to_string(m_modele->getCoutMax()) );
    }
    else {
        if(m_modele->getIsTrashAction()){
            topText->SetLabel("You can trash up to a total of " + std::to_string(m_modele->getNbMaxEcarter()) + " cards");
        }
        else{
            if (m_modele->getTourAction()){
                topText->SetLabel("ACTION PHASE");
            }
            else{
                topText->SetLabel("BUY PHASE");
            }
        }
    }
    
}

void PlayPanel::updateStats(){
    // Met a jour les labels d'action et de pieces
    std::string txtActions = "Remaining actions: " + std::to_string(m_modele->getNbActions());
    this->actionsText->SetLabel(txtActions);

    std::string txtAchat = "Remaining purchases: " + std::to_string(m_modele->getNbAchat());
    this->achatText->SetLabel(txtAchat);

    std::string txtPieces = "Remaining coins: " + std::to_string(m_modele->getNbPieces());
    this->piecesText->SetLabel(txtPieces);

    this->Layout();
}

void PlayPanel::updateAndPause(int ms) {

    refreshPlayer();
    
    update();

    // Force le rafraîchissement de l'interface
    wxYield();

    // Attends pendant ms milisecondes
    wxMilliSleep(ms);
}

void PlayPanel::showVoleur(std::vector<std::vector<Carte*>>& cartes, std::vector<int>& players){
  mainPanel->Hide();
  informationPanel->Hide();
  voleurPanel->setUpPanel(cartes,players);
  voleurPanel->Show();
  voleurPanel->SetFocus();
  this->Layout();
  this->Refresh();
}




void PlayPanel::showEndGame(std::vector<int> points){
  this->endGamePanel->setUpPanel(points);
  mainPanel->Hide();
  informationPanel->Hide();
  voleurPanel->Hide();
  this->endGamePanel->Show();
  this->endGamePanel->SetFocus();
  Layout();
  Refresh();
}
