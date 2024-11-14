#ifndef PLAY_PANEL_HPP
#define PLAY_PANEL_HPP

class Modele;

class Carte;

class PlayPanel : public wxPanel {
  private:
    Modele* m_modele;
    wxPanel* topPanel;
    wxPanel* centerPanel;
    wxPanel* playedPanel; // panel des cartes jouees
    wxPanel* handPanel; // panel des cartes en main

  public:
    wxFrame* parentFrame;
    void OnButtonClicked(wxCommandEvent& event);
    PlayPanel(wxFrame* parent, Modele* model);
    ~PlayPanel();

    void updateReserve(); // afficher les cartes de la reserve
    void updatePanel(wxPanel* pan, std::vector< std::pair<Carte*, int>  > cartes); // afficher les cartes jouees dans le panel en parametre
    void updateMain(); // afficher les cartes en main
    void updatePlayedCards(); // afficher les cartes jouees

};
#endif
