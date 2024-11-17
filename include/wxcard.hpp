#ifndef WX_CARD_HPP
#define WX_CARD_HPP

#include<string>
#include<vector>




class wxCard : public wxPanel {
  public:
    static std::vector<std::string> ActionCards;
    static std::vector<std::string> OtherCards;
    std::string m_name;
    int m_occurrences;
    wxPanel* countPanel;
    wxStaticText* countText;

    wxCard(wxWindow* parent, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor);
    wxCard(wxWindow* parent,const std::string& imageName, int occurrences);
    ~wxCard();
    void UpdateOccurrences(int occurrences);
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);
    void OnMouseClick(wxMouseEvent& event);
};
#endif
