#ifndef ABOUT_PANEL_HPP
#define ABOUT_PANEL_HPP

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>

class AboutPanel : public wxScrolledWindow{

public:
    wxFrame* parentFrame;
    void OnButtonClicked(wxCommandEvent& event);
    AboutPanel(wxFrame* parent);
    ~AboutPanel();
};

#endif
