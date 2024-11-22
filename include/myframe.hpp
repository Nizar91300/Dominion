#ifndef MY_FRAME_HPP
#define MY_FRAME_HPP
#include <wx/wx.h>
#include <string>

class Modele;
class Carte;

class MyFrame : public wxFrame{
public:
    MyFrame();
    virtual ~MyFrame ();
    wxPanel* currentpanel = NULL;
    void updateCurrentPanel();
    void updateAndPause(int ms);
    void showEndGame(std::vector<int> points);
    void showVoleur(std::vector<std::vector<Carte*>>& cartes, std::vector<int>& players);
private:
    Modele* m_modele;
    std::string currentpanelName;
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButtonClicked(wxCommandEvent& event);
};


#endif
