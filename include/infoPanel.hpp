#include <wx/wx.h>
#include<string>
#include "wxcard.hpp"

#ifndef INFO_PANEL_HPP
#define INFO_PANEL_HPP


class InfoPanel : public wxPanel {

  public:
    wxCard* informationCard;
    InfoPanel(wxWindow* parent);
    ~InfoPanel();
    void OnQuit(wxEvent& event);
    void updateImage(std::string imageName);
};
#endif
