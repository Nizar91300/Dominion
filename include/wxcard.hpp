#ifndef WX_CARD_HPP
#define WX_CARD_HPP

#include<string>
#include<vector>

class Carte;



class wxCard : public wxPanel {

  public:
    static std::vector<std::string> ActionCards;
    static std::vector<std::string> OtherCards;
    int m_occurrences;
    wxPanel* countPanel;
    wxStaticText* countText;
    wxStaticBitmap* imageCtrl;
    std::string m_name;
    Carte* m_carte;

    wxCard(wxWindow* parent, Carte* card, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor);
    wxCard(wxWindow* parent, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor);
    ~wxCard();
    void UpdateOccurrences(int occurrences);

    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);
    void OnLeftClick(wxMouseEvent& event);
    void OnRightClick(wxMouseEvent& event);
    void updateImage(std::string imageName,int w, int h);
};
#endif
