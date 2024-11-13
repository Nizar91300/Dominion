#include <wx/wx.h>
#include <wx/slider.h>

class SettingsPanel : public wxPanel {
  public:

    wxWindow* parentFrame;
    SettingsPanel(wxWindow* parent);

  private:
    wxSlider* totalPlayersSlider;
    wxSlider* humanPlayersSlider;
    wxSlider* soundSlider;

    void OnTotalPlayersChanged(wxCommandEvent& event);
    void OnHumanPlayersChanged(wxCommandEvent& event);
    void OnButtonClicked(wxCommandEvent& event);

};
