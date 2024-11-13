// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "myframe.hpp"
#include "resources.hpp"
#include "Modele.h"


class MyApp : public wxApp{
  public:
    virtual ~MyApp ();
    virtual bool OnInit();
};



//app init
bool MyApp::OnInit(){
    // make sure to call this first, image handler. necessary for images
    wxInitAllImageHandlers();
    std::cout << "[MyApp]OnInit" << '\n';
    //load ressources
    Resources::getInstance()->loadMenuImages();
    Resources::getInstance()->loadGameImages();

    //main frame
    Modele* modele = new Modele();

    MyFrame* frame = new MyFrame(modele);

    modele->setView(frame);

    frame->Show(true);
    return true;
}

MyApp::~MyApp(){
  Resources::deleteInstance();
  std::cout << "[MyApp]delete" << '\n';
}

wxIMPLEMENT_APP(MyApp);
