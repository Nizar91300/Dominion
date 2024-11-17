#ifndef PLAY_PANEL_HPP
#define PLAY_PANEL_HPP

class Modele;

class Carte;

class PlayPanel : public wxPanel {
  private:
    Modele* m_modele;
    wxPanel* mainPanel;
    wxPanel* informationPanel;
    wxFrame* parentFrame;


    wxPanel* centerPanel;
    wxPanel* playedPanel; // panel des cartes jouees
    wxPanel* handPanel; // panel des cartes en main
    wxButton* tourBtn; // bouton pour passer au tour suivant

  public:

    PlayPanel(wxFrame* parent, Modele* model);
    ~PlayPanel();

    
    void OnButtonClicked(wxCommandEvent& event);
    void OnTourButtonClicked(wxCommandEvent& event);
    void OnEndButtonClicked(wxCommandEvent& event);
    void onLeftClicked(wxCommandEvent& event);

    void update();    // met a jour tout l'affichage

    void onKeyPress(wxKeyEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnResign(wxCommandEvent& event);

    void updateReserve(); // afficher les cartes de la reserve
    void updatePanel(wxPanel* pan, std::vector< std::pair<Carte*, int>  > cartes); // afficher les cartes jouees dans le panel en parametre
    void updateMain(); // afficher les cartes en main
    void updatePlayedCards(); // afficher les cartes jouees

};
#endif
