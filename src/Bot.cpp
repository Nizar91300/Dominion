#include "Bot.h"
#include "Modele.h"
#include "Carte.h"
#include "DeckManager.h"
#include "Action.h"

// joue toutes les actions possibles
void Bot::playActionPhase() {
    m_modele->refreshAndPauseView(700);        // refresh et pauser pour voir les actions du bot

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
                    m_modele->refreshAndPauseView(1100);             // refresh et pauser pour voir les actions du bot
                }

            }else{
                if(bestActionCard->getNom() == "chapel"){
                    // jeter des copper s'il y en a jusqu'a 4
                    auto main = m_deckManager->getMain();
                    int i = 0;
                    for (auto& carte : main) {
                        if(i == 4){
                            break;
                        }
                        if (carte->getNom() == "copper") {
                            m_modele->jouerCarte(carte);
                            m_modele->refreshAndPauseView(800);         // refresh et pauser pour voir les actions du bot
                            i++;
                        }
                        
                    }
                }
            }

            m_modele->refreshAndPauseView(700);     // refresh et pauser pour voir les actions du bot

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
            m_modele->refreshAndPauseView(1500);         // refresh et pauser pour voir les actions du bot
        } else {
            break; // Plus d'achats possibles
        }
    }
}

// retourne la carte d'action la plus interessante
Carte* Bot::findBestActionCard() {
    auto main = m_deckManager->getMain();
    Carte* bestCard = nullptr;
    int bestScore = -1;

    for (auto& carte : main) {
        if (carte->getType() == TypeCarte::ACTION) {
            Action* action = static_cast<Action*>(carte);
            int score = carte->getPriorite();

            // Modifie le score selon le contexte
            if (m_modele->getNbActions() == 1 && action->getNbActions() > 0) score += 5;
            if (m_deckManager->getMain().size() < 3 && action->getNbPioche() > 0) score += 5;

            // Compare avec la meilleure carte actuelle
            if (score > bestScore) {
                bestScore = score;
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
    int bestScore = -1;

    auto deck = m_deckManager->getAllCards();

    for (auto& cartePair : reserve) {
        // si la carte est epuise ou si c'est une carte Curse on la passe
        if (cartePair.second == 0 || cartePair.first->getNom() == "curse" || cartePair.first->getNom() == "copper") {
            continue;
        }

        Carte* carte = cartePair.first;
        int cost = carte->getCout();

        // si la carte est achetable
        if (cost <= coutMax) {
            int score = carte->getPriorite();

            // compter le nombre de fois que la carte est dans le deck
            int countInDeck = std::count_if(deck.begin(), deck.end(), [&](Carte* c) {
                return c->getNom() == carte->getNom();  // Comparer les noms des cartes
            });

            if (countInDeck > 0) {
                score -= countInDeck * 3;  // reduire le score pour empecher d'acheter des cartes en double
            }

            // on prefere une carte qui n'est pas encore dans le deck ou qui est plus utile
            if (!bestCard || score > bestScore) {
                bestScore = score;
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
            m_modele->refreshAndPauseView(500);        // refresh et pauser pour voir les actions du bot
        }
    }
}