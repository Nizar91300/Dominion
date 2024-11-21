#include<string>
#include "myframe.hpp"
#include "mainPanel.hpp"
#include "settingsPanel.hpp"
#include "aboutPanel.hpp"
#include "playPanel.hpp"
#include "Modele.h"


enum{ID_Hello = 1};


MyFrame::MyFrame(): wxFrame(NULL, wxID_ANY, "Dominion", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE),m_modele(new Modele()),currentpanelName("Main") {
    m_modele->setView(this);
    std::cout << "[MyFrame]constructor" << '\n';
    //top menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Dominion...\tCtrl-H","Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    //status bar at the bottom
    CreateStatusBar();
    SetStatusText("Welcome to Dominion!");
    //events
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnButtonClicked, this);

    this->currentpanel = new MainPanel(this, m_modele);

}


MyFrame::~MyFrame(){
  if(currentpanel!=NULL){this->currentpanel->Destroy();}
  delete m_modele;
  std::cout << "[MyFrame]delete" << '\n';
}


void MyFrame::OnExit(wxCommandEvent& event){Close(true);}

void MyFrame::OnAbout(wxCommandEvent& event){wxMessageBox("This project is mage by Alaeddine and Nizar from Polytech","About The Project", wxOK | wxICON_INFORMATION);}

void MyFrame::OnHello(wxCommandEvent& event){  wxLogMessage("This an implementation for the famous card Game Dominion in c++ GUI is made using wWidgets!");}


void MyFrame::OnButtonClicked(wxCommandEvent& event) {

  if(this->currentpanelName=="Main"){

    if(event.GetString()=="New Game"){

        m_modele->initNewGame();
        this->currentpanelName = "Play";
        this->currentpanel->Destroy();
        // Initialiser une nouvelle partie avec le meme nombre de joueurs
        this->currentpanel = new PlayPanel(this, m_modele);
        this->currentpanel->Show();
        Layout();

    }else if(event.GetString()=="Resume"){

        //this->currentpanelName = "Play";  //todo

    }else if(event.GetString()=="Settings"){

        this->currentpanelName = "Settings";
        this->currentpanel->Destroy();
        this->currentpanel = new SettingsPanel(this);
        this->currentpanel->Show();
        Layout();

    }else if(event.GetString()=="About"){

        this->currentpanelName = "About";
        this->currentpanel->Destroy();
        this->currentpanel = new AboutPanel(this);
        this->currentpanel->Show();
        Layout();

    }else if(event.GetString()=="Quit"){
      this->OnExit(event);
    }
    return;
  }


  if(event.GetString()=="Back" || event.GetString()=="Quit"){
        this->currentpanelName = "Main";
        this->currentpanel->Destroy();
        this->currentpanel = new MainPanel(this, m_modele);
        this->currentpanel->Show();
        Layout();
  }

}



// update the current panel
void MyFrame::updateCurrentPanel(){
  if(this->currentpanelName=="Play"){
    PlayPanel* p = static_cast<PlayPanel*>(this->currentpanel);
    p->update();
  }
}