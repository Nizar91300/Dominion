#ifndef PLAY_PANEL_HPP
#define PLAY_PANEL_HPP
#include"infoPanel.hpp"

class Modele;

class Carte;

class PlayPanel : public wxPanel {
  private:
    Modele* m_modele;
    wxPanel* mainPanel;
    InfoPanel* informationPanel;


    wxPanel* centerPanel;
    wxPanel* playedPanel; // panel des cartes jouees
    wxPanel* handPanel; // panel des cartes en main
    wxButton* tourBtn; // bouton pour passer au tour suivant

  public:

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



    void updateReserve(); // afficher les cartes de la reserve
    void updatePanel(wxPanel* pan, std::vector< std::pair<Carte*, int>  > cartes); // afficher les cartes jouees dans le panel en parametre
    void updateMain(); // afficher les cartes en main
    void updatePlayedCards(); // afficher les cartes jouees

};
#endif
