#ifndef ABOUT_PANEL_HPP
#define ABOUT_PANEL_HPP

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>

class Modele;

class AboutPanel : public wxScrolledWindow{

public:
    void OnBackButtonClicked(wxCommandEvent& event);
    AboutPanel(wxFrame* parent);
    ~AboutPanel();
};

#endif
