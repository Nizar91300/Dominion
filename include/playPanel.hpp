#ifndef PLAY_PANEL_HPP
#define PLAY_PANEL_HPP

class PlayPanel : public wxPanel {
  public:
    wxFrame* parentFrame;
    void OnButtonClicked(wxCommandEvent& event);
    PlayPanel(wxFrame* parent);
    ~PlayPanel();
};
#endif
