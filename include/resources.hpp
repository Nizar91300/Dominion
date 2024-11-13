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

    Resources(const Resources&) = delete; // Delete copy constructor
    Resources& operator=(const Resources&) = delete; // delete assignment operator to enforce Singleton pattern

    void loadImages(std::vector<std::string> imageNames);
    void loadMenuImages();
    void loadGameImages();
    //void deleteMenuImages();   //todo
    //void freeGameImages();    //todo
    wxImage* getImage(const std::string& name) const;
    bool hasImage(const std::string& name) const;

private:
    // Private constructor and destructor and attributes
    static Resources* instance;
    std::map<std::string, wxImage*> *images;

    Resources():images(new std::map<std::string, wxImage*>){};
    ~Resources();

};

#endif
