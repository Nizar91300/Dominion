#ifndef ABOUT_PANEL_HPP
#define ABOUT_PANEL_HPP

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>

class Modele;

class AboutPanel : public wxScrolledWindow{
private:
    Modele* m_modele;

public:
    wxFrame* parentFrame;
    void OnButtonClicked(wxCommandEvent& event);
    AboutPanel(wxFrame* parent, Modele* model);
    ~AboutPanel();
};

#endif
