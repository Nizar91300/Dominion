#include<set>
#include<string>
#include <iostream>
#include <fstream>
#include <wx/filename.h>
#include "resources.hpp"
#include "wxcard.hpp"

Resources* Resources::instance = NULL;

//destructor
Resources::~Resources(){
  for (auto& pair : *(this->images)) {
      delete pair.second; // Delete allocated Image object
  }
  delete images;
  this->writeSettings();
}


//return the single instance or create it if it does not exist
Resources* Resources::getInstance(){
    if (Resources::instance==NULL) {
      std::cout << "[Resources]getInstance (allocating)" << '\n';
      Resources::instance = new Resources();
      if(!Resources::instance->readSettings()){
        Resources::instance->resetSettings();
        Resources::instance->writeSettings();
      }
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
  this->loadImages(wxCard::ActionCards);
  this->loadImages(wxCard::OtherCards);
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


//settings

void Resources::getSettings(int& nPlayers,int& nHumans,int& nSound,std::set<std::string>&cards) {
  nPlayers = this->m_totalPlayers;
  nHumans = this->m_humanPlayers;
  nSound = this->m_sound;
  cards = this->m_chosenCards;
}

void Resources::setSettings(int nPlayers,int nHumans,int nSound,std::set<std::string>cards) {
    if(cards.size()==10){
      this->m_totalPlayers = nPlayers;
      this->m_humanPlayers = nHumans;
      this->m_sound = nSound;
      this->m_chosenCards = cards;
    }
}

bool Resources::readSettings() {

    std::ifstream file("./resources/settings");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the ./resources/settings file.\n";
        return false;
    }

    // Read first 3 numbers
    if (!(file >> this->m_totalPlayers >> this->m_humanPlayers >> this->m_sound)) {
        std::cerr << "Error: File does not contain valid numbers.\n";
        file.close();
        return false;
    }

    std::string word;
    std::set<std::string> words;
    for (int i = 0; i < 10; ++i) {
        if (!(file >> word)) {
            std::cerr << "Error: File does not contain enough valid words.\n";
            file.close();
            return false;
        }
        words.insert(word);
    }


    if(words.size()!=10){
      std::cerr << "Error: File contains duplicate cards.\n";
      file.close();
      return false;
    }

    this->m_chosenCards=words;

    file.close();
    return true;
}

bool Resources::writeSettings() {

    std::ofstream file("./resources/settings", std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the ./resources/settings file.\n";
        return false;
    }

    file << this->m_totalPlayers << "\n" << this->m_humanPlayers << "\n" << this->m_sound << "\n";
    for (const auto& word : this->m_chosenCards) {file << word << "\n";}

    file.close();
    return true;
}


void Resources::resetSettings() {
  this->m_totalPlayers = 5;
  this->m_humanPlayers = 1;
  this->m_sound  = 50;
  this->m_chosenCards = {"cellar", "market", "militia", "mine", "moat", "remodel", "smithy", "village", "woodcutter",  "workshop"};
}
