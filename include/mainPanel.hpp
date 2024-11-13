#ifndef MAIN_PANEL_HPP
#define MAIN_PANEL_HPP

#include <wx/wx.h>


class MainPanel : public wxPanel{
    wxImage* image;
    wxBitmap resized;
    int w, h;

public:
    wxFrame* parentFrame;
    MainPanel(wxFrame* parent);
    ~MainPanel();
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);
    void OnButtonClicked(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};


#endif
