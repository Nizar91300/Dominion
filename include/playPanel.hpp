#ifndef PLAY_PANEL_HPP
#define PLAY_PANEL_HPP
#include"infoPanel.hpp"
#include"voleurPanel.hpp"
#include"endGame.hpp"

class Modele;

class Carte;

class PlayPanel : public wxPanel {
  private:
    Modele* m_modele;
    wxPanel* mainPanel;
    InfoPanel* informationPanel;
    VoleurPanel* voleurPanel;
    EndGame* endGamePanel;


    wxPanel* centerPanel;
    wxPanel* rightPanel;
    wxPanel* playedPanel; // panel des cartes jouees
    wxPanel* handPanel; // panel des cartes en main
    wxButton* tourBtn; // bouton pour passer au tour suivant
    wxPanel* defaussePanel; // panel de la defausse
    wxStaticText* topText; // text en haut de la fenetre
    wxStaticText* actionsText; // text pour le nombre d'actions
    wxStaticText* piecesText; // text pour le nombre de pieces
    wxStaticText* achatText; // text pour le nombre d'achats

  public:
    static std::vector<wxColour> PLAYER_COLOURS;

    PlayPanel(wxFrame* parent, Modele* model);
    ~PlayPanel();

    //quit, save, resign
    void OnQuit(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnResign(wxCommandEvent& event);

    //card info functions
    void onCardInfo(wxCommandEvent& event);
    void onCardInfoReturn(wxCommandEvent& event);

    //tpours
    void OnTourButtonClicked(wxCommandEvent& event);
    void OnEndButtonClicked(wxCommandEvent& event);
    void onLeftClicked(wxCommandEvent& event);



    void update();    // met a jour tout l'affichage

    void refreshPlayer();
    void showVoleur(std::vector<std::vector<Carte*>>& cartes, std::vector<int>& players);
    void showEndGame(std::vector<int> points);

    void updateReserve(); // afficher les cartes de la reserve
    void updatePanel(wxPanel* pan, std::vector< std::pair<Carte*, int>  > cartes); // afficher les cartes jouees dans le panel en parametre
    void updateMain(); // afficher les cartes en main
    void updatePlayedCards(); // afficher les cartes jouees
    void updateDefausse(); // afficher la defausse
    void updateShownText(); // afficher le texte en haut de la fenetre
    void updateStats(); // afficher les stats
    void updateAndPause(); // met a jour l'affichage et pause le thread

};
#endif
