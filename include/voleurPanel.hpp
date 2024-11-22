#ifndef VOLEUR_PANEL_HPP
#define VOLEUR_PANEL_HPP

#include <wx/wx.h>
#include <wx/sizer.h>
#include <vector>
#include "wxcard.hpp"

class VoleurPanel : public wxPanel {
  public:
    std::vector<std::vector<wxCard*>> cards;
    std::vector<wxPanel*> panels;
    std::vector<wxStaticText*> texts;


    VoleurPanel(wxWindow* parent);
    void setUpPanel(std::vector<std::vector<Carte*>>& cartes, std::vector<int>& players);
    void OnQuit(wxEvent& event);
};


#endif
