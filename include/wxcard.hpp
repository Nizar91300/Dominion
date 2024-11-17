#ifndef WX_CARD_HPP
#define WX_CARD_HPP

#include<string>
#include<vector>

class Carte;



class wxCard : public wxPanel {
  private:
  wxPanel* m_parentPan;
  Carte* m_carte;
  wxWindow* m_parent;

  public:
    static std::vector<std::string> ActionCards;
    static std::vector<std::string> OtherCards;
    std::string m_name;
    int m_occurrences;
    wxPanel* countPanel;
    wxStaticText* countText;

    // constructeur avec une carte
    wxCard(wxWindow* parent, wxPanel* parentPan, Carte* card, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor);
    
    // constructeur sans carte
    wxCard(wxWindow* parent, wxPanel* parentPanel, const std::string& imageName, int occurrences,int paneWidth,int paneHeight,int imageWidth, int imageHeight,wxColour backgroundColor);
    wxCard(wxWindow* parent,wxPanel* parentPanel,const std::string& imageName, int occurrences);
    ~wxCard();
    void UpdateOccurrences(int occurrences);
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);
    void OnMouseClick(wxMouseEvent& event);
    void OnRightClick(wxMouseEvent& event);
};
#endif
