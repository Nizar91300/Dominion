#include <wx/wx.h>
#include<string>
#include "wxcard.hpp"

#ifndef END_GAME_HPP
#define END_GAME_HPP


class EndGame : public wxPanel {

  public:
    wxBoxSizer* sizer;
    EndGame(wxWindow* parent);
    ~EndGame();
    void OnQuit(wxEvent& event);
    void setUpPanel(std::vector<int>& points);
};
#endif
