#include <wx/wx.h>
#include<string>
#include "wxcard.hpp"

#ifndef END_GAME_HPP
#define END_GAME_HPP


class EndGame : public wxPanel {
  private:
    wxBoxSizer* sizer;

  public:
    EndGame(wxWindow* parent);
    ~EndGame();
    void OnQuit(wxEvent& event);
    void setUpPanel(std::vector<int>& points);
};
#endif
