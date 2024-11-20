#include <wx/wx.h>
#include <wx/slider.h>
#include <set>
#include"wxcard.hpp"


class SettingsPanel : public wxScrolledWindow {
  public:

    SettingsPanel(wxWindow* parent);
    ~SettingsPanel();

  private:
    wxSlider* m_totalPlayersSlider;
    wxSlider* m_humanPlayersSlider;
    wxSlider* m_soundSlider;
    wxStaticText* m_cardsLabel;

    std::vector<wxCard*> m_gridCards;
    std::set<std::string> m_chosenCards;
    int m_cardsSelected;
    int m_totalPlayers;
    int m_humanPlayers;
    int m_sound;


    void OnTotalPlayersChanged(wxCommandEvent& event);
    void OnHumanPlayersChanged(wxCommandEvent& event);
    void OnSoundChange(wxCommandEvent& event);
    void OnBackButtonClicked(wxCommandEvent& event);
    void OnResetButtonClicked(wxCommandEvent& event);
    void OnCardEvent(wxCommandEvent& event);
    void OnCardClick(wxCommandEvent& event);
};
