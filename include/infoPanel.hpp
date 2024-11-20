#ifndef INFO_PANEL_HPP
#define INFO_PANEL_HPP


class InfoPanel : public wxPanel {

  public:

    InfoPanel(wxWindow* parent);
    ~InfoPanel();
    void OnQuit(wxEvent& event);
    void updateImage();
    void updateText();
};
#endif
