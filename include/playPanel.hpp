#ifndef PLAY_PANEL_HPP
#define PLAY_PANEL_HPP

class Modele;

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
    void updateMain(); // afficher les cartes en main
};
#endif
