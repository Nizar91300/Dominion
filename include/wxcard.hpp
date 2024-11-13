#ifndef WX_CARD_HPP
#define WX_CARD_HPP

#include<string>
#include<vector>


class wxCard : public wxPanel {
  public:
  
    wxCard(wxWindow* parent, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor);
    wxCard(wxWindow* parent,const std::string& imageName, int occurrences);
    ~wxCard();
    void UpdateOccurrences(int occurrences);
};
#endif
