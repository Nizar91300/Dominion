#include "Bot.h"
#include "Modele.h"
#include "Carte.h"
#include "DeckManager.h"

// joue toutes les actions possibles
void Bot::playActionPhase() {
    m_modele->refreshAndPauseView();        // refresh et pauser pour voir les actions du bot

    while (m_modele->getNbActions() > 0) {
        Carte* bestActionCard = findBestActionCard();
        if (bestActionCard) {
            m_modele->jouerCarte(bestActionCard);

            // gestion des cartes speciales
            if(bestActionCard->getNom() == "workshop" || bestActionCard->getNom() == "feast"){
                // si la carte est workshop ou feast on achete la carte la plus chere possible
                int coutMax = m_modele->getCoutMax();

                Carte* bestBuyCard = findBestBuyCard(coutMax);
                
                if(bestBuyCard){
                    m_modele->acheterCarteAvecVerif(bestBuyCard);
                    m_modele->refreshAndPauseView();             // refresh et pauser pour voir les actions du bot
                }

            }

        } else {
            break; // Aucune action possible
        }
    }
}

// joue tous les achats possibles
void Bot::playBuyPhase() {
    playAllTreasures();     // Joue tous les tresors possibles
    while (m_modele->getNbAchat() > 0) {
        Carte* bestBuyCard = findBestBuyCard(m_modele->getNbPieces());
        if (bestBuyCard) {
            m_modele->acheterCarteAvecVerif(bestBuyCard);
            m_modele->refreshAndPauseView();         // refresh et pauser pour voir les actions du bot
        } else {
            break; // Plus d'achats possibles
        }
    }
}

// retourne la carte d'action avec le cout le plus eleve que le bot peut jouer
Carte* Bot::findBestActionCard() {
    auto main = m_deckManager->getMain();
    Carte* bestCard = nullptr;

    for (auto& carte : main) {
        if (carte->getType() == TypeCarte::ACTION) {
            if (!bestCard || carte->getCout() > bestCard->getCout()) {
                bestCard = carte;
            }
        }
    }
    return bestCard;
}

// retourne la carte avec le cout le plus elevee achetable selon le cout max
Carte* Bot::findBestBuyCard(int coutMax) {
    auto reserve = m_modele->getReserve();
    Carte* bestCard = nullptr;

    for (auto& cartePair : reserve) {
        if(cartePair.second == 0) {
            continue;
        }

        Carte* carte = cartePair.first;
        int cost = carte->getCout();
        if (cost <= coutMax) {
            if (!bestCard || cost >= bestCard->getCout()) {
                bestCard = carte;
            }
        }
    }
    return bestCard;
}

// joue tous les tresors possibles
void Bot::playAllTreasures() {
    auto main = m_deckManager->getMain();
    for (auto& carte : main) {
        if (carte->getType() == TypeCarte::TRESOR) {
            m_modele->jouerCarte(carte);
            m_modele->refreshAndPauseView();        // refresh et pauser pour voir les actions du bot
        }
    }
}