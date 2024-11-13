#ifndef MY_FRAME_HPP
#define MY_FRAME_HPP
#include <wx/wx.h>
#include <string>

class Modele;

class MyFrame : public wxFrame{
public:
    MyFrame(Modele* model);
    virtual ~MyFrame ();
    wxPanel* currentpanel = NULL;
private:
    Modele* m_modele;
    std::string currentpanelName;
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButtonClicked(wxCommandEvent& event);
};


#endif
