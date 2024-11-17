#include "aboutPanel.hpp"
#include <wx/scrolwin.h>
#include "Modele.h"

AboutPanel::AboutPanel(wxFrame* parent): wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL){

        SetBackgroundColour(wxColour(50, 82, 89));// Set background color to black
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);// Create a vertical sizer for layout
        wxBoxSizer* navSizer = new wxBoxSizer(wxHORIZONTAL);// Create a horizontal sizer for the top navigation bar

        // Create a "Back" button with a left arrow label
        wxButton* backButton = new wxButton(this, wxID_ANY, "Back", wxDefaultPosition, wxSize(80, 30));
        backButton->Bind(wxEVT_BUTTON, &AboutPanel::OnBackButtonClicked, this);
        navSizer->Add(backButton, 0, wxLEFT | wxTOP, 10);// Add the back button to the navigation sizer
        mainSizer->Add(navSizer, 0, wxEXPAND);// Add the navigation bar to the main sizer

        // Create a multi-line, read-only text control for the about information
        wxTextCtrl* aboutText = new wxTextCtrl(this, wxID_ANY,
            "This is a game of building a deck of cards. The deck is your Dominion. It contains your resources, victory points, and the things you can do. It starts out a small sad collection of Estates and Coppers, but you hope by the end of the game it will be brimming with Gold, Provinces, and the inhabitants and structures of your castle and kingdom.\n"
            "The player with the most victory points in his Deck at game end wins.\n\n\n"
            "TREASURE CARDS: \nCopper, Silver, and Gold cards are the basic Treasure cards, and they are available in every game. After each player takes 7 Copper cards, place the remaining Copper cards and all of the Silver cards and Gold cards in face-up piles in the Supply.\n\n"
            "VICTORY CARDS: \nEstate, Duchy, and Province cards are the basic Victory cards, and they are available in every game. After each player takes 3 Estate cards, place 12 each of the Estate, Duchy, and Province cards in face-up piles in the Supply in a 3 or 4 player game. In a 2 player game, place only 8 of each of these Victory cards in the Supply. Place unused Victory cards back in the box.\n\n"
            "CURSE CARDS & TRASH CARD: \nPlace 10 Curse cards in the Supply for a 2 player game, 20 Curse cards for 3 players, and 30 Curse cards for 4 players. Return unused Curse cards to the box. Curse cards are used most often with specific Action cards (e.g. Witch). If a player buys a Curse card (0 cost), it goes in his own discard pile, like any other gained card. This, of course, will not often occur. The Trash card marks the place where players place cards trashed in the game.\n\n"
            "KINGDOM CARDS: \nIn addition to the Trash, Treasure, Victory, and Curse cards that are used in every game, the players also select 10 Kingdom cards and place 10 of each in face-up piles on the table.\n\n"
            "\n\n\n\n"
            "TURN OVERVIEW\n"
            "Each turn has three phases (A, B, and C) in the order shown:\n"
            "A) Action phase - the player may play an Action.\n"
            "B) Buy phase - the player may buy a card.\n"
            "C) Clean-up phase - the player must discard both played and unplayed cards and draws five new cards. After a player completes all three phases, his turn ends.\n"
            "\n\n\n\n"
            "The game ends at the end of any player's turn when either:\n"
            "1) the Supply pile of Province cards is empty or\n"
            "2) any 3 Supply piles are empty.\n"
            "\n\n\n\n"
            "Version: 1.0.0\n\n\n"
            "Copyright (C) 2024 Alaeddine & Nizar",
            wxDefaultPosition, wxDefaultSize,
            wxTE_MULTILINE | wxTE_READONLY  | wxBORDER_NONE | wxTE_NOHIDESEL);

        aboutText->SetBackgroundColour(wxColour(50, 82, 89));
        aboutText->SetForegroundColour(wxColour(243, 210, 161)); // Gold color for text
        mainSizer->Add(aboutText, 1, wxALL | wxEXPAND, 15);// Add the text control to the main sizer with expand option
        SetSizer(mainSizer);// Set the sizr for this panel and configure scrolling
        SetScrollRate(5, 5);
        FitInside(); // Ensure everything fits inside the scrolled window
    }



AboutPanel::~AboutPanel(){}


void AboutPanel::OnBackButtonClicked(wxCommandEvent& event){
  wxCommandEvent notifyEvent(wxEVT_COMMAND_BUTTON_CLICKED, event.GetId());
  notifyEvent.SetString("Back");  // Include button name in the event
  wxPostEvent(this->GetParent(), notifyEvent); // Send event to parent frame
}
