#include <wx/wx.h>
#include <wx/slider.h>

class Modele;

class SettingsPanel : public wxPanel {
  public:

    wxWindow* parentFrame;
    SettingsPanel(wxWindow* parent, Modele* model);
    ~SettingsPanel();

  private:
    wxSlider* totalPlayersSlider;
    wxSlider* humanPlayersSlider;
    wxSlider* soundSlider;
    Modele* m_modele;

    void OnTotalPlayersChanged(wxCommandEvent& event);
    void OnHumanPlayersChanged(wxCommandEvent& event);
    void OnButtonClicked(wxCommandEvent& event);

};
