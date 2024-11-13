#ifndef PLAY_PANEL_HPP
#define PLAY_PANEL_HPP

class Modele;

class PlayPanel : public wxPanel {
private:
  Modele* m_modele;

  public:
    wxFrame* parentFrame;
    void OnButtonClicked(wxCommandEvent& event);
    PlayPanel(wxFrame* parent, Modele* model);
    ~PlayPanel();
};
#endif
