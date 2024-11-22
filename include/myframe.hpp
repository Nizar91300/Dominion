#ifndef MY_FRAME_HPP
#define MY_FRAME_HPP
#include <wx/wx.h>
#include <string>

class Modele;

class MyFrame : public wxFrame{
public:
    MyFrame();
    virtual ~MyFrame ();
    wxPanel* currentpanel = NULL;
    void updateCurrentPanel();
    void updateAndPause();
private:
    Modele* m_modele;
    std::string currentpanelName;
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButtonClicked(wxCommandEvent& event);
};


#endif
