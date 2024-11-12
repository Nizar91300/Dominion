# Dominion

## Pré-requis

Pour les 2 méthodes il faut d'abord installer la librarie GTK version 2. Pour l'installer : 

#### Sur Ubuntu/Debian

```console
sudo apt update
sudo apt install libgtk2.0-dev
```

#### Sur Fedora :
```console
sudo dnf install gtk2-devel
```



### 1ère Méthode : Utilisation de la librairie graphique pré-build
- Télécharger le fichier de la librairie wxWidgets déjà pré-build ici : https://drive.google.com/file/d/1fvEoq4Gm7lCj5rW328qhgv6omsgy7HNy/view?usp=sharing.

- Extraire le contenu de sorte qu'il soit à la racine du dossier ./Dominion. On doit avoir un chemin de la sorte ./Dominion/wxWidgets-3.2.6/

- Vérifier que le dossier ./wxWidgets-3.2.6 contient bien directement les fichiers de la librairie (le premier sous-dossier étant 3rdparty) et surtout que le dossier situé à ./Dominion/wxWidgets-3.2.6/wx-build soit présent

- Ouvrir le fichier ./Dominion/wxWidgets-3.2.6/wx-build/wx-config

- A la ligne 28 et 32 du fichier, spécifier le chemin absolue vers le dossier wx-build, exemple "/home/user/Downloads/Dominion/wxWidgets-3.2.6/wx-build/.."

Après avoir fait cela on peut directement passer à la compilation / exécution du jeu.

Si vous rencontrez des problèmes à utiliser la méthode 1 essayez la méthode 2.

### 2ème Méthode : Build de la librarie graphique

- Télécharger la librarie wxWidgets à l'adresse : https://github.com/wxWidgets/wxWidgets?tab=readme-ov-file

- Extraire le contenu de sorte qu'il soit à la racine du dossier ./Dominion. On doit avoir un chemin de la sorte ./Dominion/wxWidgets-3.2.6/

- Vérifier que le dossier ./wxWidgets-3.2.6 contient bien directement les fichiers de la librairie (le premier sous-dossier étant 3rdparty)

- Exécuter les commandes suivantes :

```console
cd wxWidgets-3.2.6
mkdir wx-build
cd wx-build
../configure --enable-debug
make
```

La commande make prend entre 15-20 min pour compiler tous les fichiers de la librarie

Après avoir fait ces commandes le dossier wx-build doit contenir les fichiers objets de compilation. Maintenant on peut passer à la compilation / exécution du jeu.

## Compilation

Pour recompiler le jeu. Faire d'abord : 

```console
make clean
```
Cela permet de supprimer les fichiers .o déjà compilés.

Ensuite on peut compiler les fichiers en faisant : 

```console
make all
```

Ne pas tenir compte des warning lors de la compilation de chaque fichier.

Cependant si la compilation échoue ou si cela indique que le dossier /wsWidgets-3.2.6 n'est pas trouvé vérifiez la bonne installation de la librairie graphique

## Exécution

Pour éxécuter le jeu on fait simplement : 

```console
make run
```


