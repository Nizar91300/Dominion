# Variables
CXX = g++                               # Le compilateur à utiliser
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -g  # Options de compilation
SOURCES = Modele/Carte/Victoire/Domaine.cpp \
          Modele/Carte/Victoire/Duche.cpp \
          Modele/Carte/Victoire/Province.cpp \
          Modele/Carte/Victoire/Malediction.cpp \
          Modele/Carte/Victoire/Jardin.cpp \
          Modele/Carte/Action/Atelier.cpp \
          Modele/Carte/Action/Bucheron.cpp \
          Modele/Carte/Action/Reaction/Douve.cpp \
          Modele/Carte/Action/Chapelle.cpp \
          Modele/Carte/Action/Laboratoire.cpp \
          Modele/Carte/Action/Attaque/Sorciere.cpp \
          Modele/Carte/Action/Village.cpp \
          Modele/Carte/Action/Attaque/Voleur.cpp \
          Modele/Carte/Action/Festin.cpp \
          Modele/Carte/Tresor/Cuivre.cpp \
          Modele/Carte/Tresor/Argent.cpp \
          Modele/Carte/Tresor/Or.cpp \
          Modele/Joueur/DeckManager.cpp \
          Modele/Joueur/Joueur.cpp \
          Modele/Modele.cpp \
          main.cpp
OBJECTS = $(SOURCES:.cpp=.o)              # Remplacer .cpp par .o
TARGET = dominion                     # Nom de l'exécutable

# Règle par défaut
all: $(TARGET)

# Règle pour construire l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle pour compiler les fichiers .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers temporaires
clean:
	rm -f $(OBJECTS) $(TARGET)

