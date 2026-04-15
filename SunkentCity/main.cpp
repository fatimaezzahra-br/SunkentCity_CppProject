#include "Game.h"
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sunken City Escape");
    window.setFramerateLimit(60); // Important pour ne pas consommer 100% du CPU

    Menu menu;

    while (window.isOpen()) {
        // 1. On affiche le menu (cette fonction est bloquante)
        int choice = menu.show(window); 

        // 2. Si l'utilisateur choisit de jouer
        if (choice == 1) { 
            Game game(window);
          
            
            // On appelle UNIQUEMENT run(). 
            // C'est la classe Game qui doit gérer sa propre boucle, 
            // son horloge (clock) et ses événements.
            game.run(); 

            // Une fois que game.run() se termine (mort ou Echap), 
            // le programme revient ici et relance la boucle du menu.
        } 
        // 3. Si l'utilisateur choisit de quitter (Num 3) ou ferme la fenêtre
        else {
            window.close();
        }
    }

    return 0;
}