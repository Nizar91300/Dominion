#include "resources.hpp"
#include "wxcard.hpp"
#include <wx/filename.h>


Resources* Resources::instance = NULL;

//destructor
Resources::~Resources(){
  for (auto& pair : *(this->images)) {
      delete pair.second; // Delete allocated Image object
  }
  delete images;
}


//return the single instance or create it if it does not exist
Resources* Resources::getInstance(){
    if (Resources::instance==NULL) {
      std::cout << "[Resources]getInstance (allocating)" << '\n';
      Resources::instance = new Resources();
    }
    return Resources::instance;
}

void Resources::deleteInstance(){
    if (Resources::instance!=NULL) {
      std::cout << "[Resources]deleting" << '\n';
      delete Resources::instance;
      Resources::instance = NULL;
    }
}

void Resources::loadImages(std::vector<std::string> imageNames){
  const std::string directory = "./resources";
  for (const auto& name : imageNames) {
      if(this->hasImage(name)){continue;}
      wxString filePath = wxString::Format("%s/%s.png", directory, name);

      if (wxFileName::FileExists(filePath)) {
          wxImage image;
          if (image.LoadFile(filePath, wxBITMAP_TYPE_PNG)) {
              (*images)[name] = new wxImage(image);
          } else {
              wxLogError("Failed to load image: %s", filePath);
          }
      } else {
          wxLogError("Image file not found: %s", filePath);
      }
  }
}

void Resources::loadMenuImages(){
  std::cout << "[Resources]loading menu images ...." << '\n';
  this->loadImages({"error-img","background-img"});
}

void Resources::loadGameImages(){
  std::cout << "[Resources]loading game images ...." << '\n';
  this->loadImages(wxCard::cards);
}

wxImage* Resources::getImage(const std::string& name) const {
    auto it = images->find(name);
    if (it != images->end()) {return it->second;}

    wxLogError("Image '%s' not found in resources.", name);
    //return custom error image
    it = images->find("error-img");
    if (it != images->end()) {return it->second;}

    wxLogError("custom error image also not found in resources.");
    //if custom error image not found (there s a big problem)
    return NULL;
}

bool Resources::hasImage(const std::string& name) const {
    return images->find(name) != images->end();
}
