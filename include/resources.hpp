#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <wx/wx.h>
#include <wx/image.h>
#include <map>
#include <string>
#include <vector>

class Resources {
  public:

    static Resources* getInstance();
    static void deleteInstance();

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    void loadImages(std::vector<std::string> imageNames);
    void loadMenuImages();
    void loadGameImages();
    //void deleteMenuImages();   //todo
    //void freeGameImages();    //todo
    wxImage* getImage(const std::string& name) const;
    bool hasImage(const std::string& name) const;


    void getSettings(int& nPlayers,int& nHumans,int& nSound,std::set<std::string>&cards);
    void setSettings(int nPlayers,int nHumans,int nSound,std::set<std::string>cards);
    bool readSettings();
    bool writeSettings();





private:
    // Private constructor and destructor and attributes
    static Resources* instance;
    std::map<std::string, wxImage*> *images;

    //parameters
    std::set<std::string> m_chosenCards;
    int m_totalPlayers;
    int m_humanPlayers;
    int m_sound;



    Resources():images(new std::map<std::string, wxImage*>){};
    ~Resources();

};

#endif
