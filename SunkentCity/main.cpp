#include "Game.h"
#include "Menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sunken City");
    Menu menu;
    
    // On affiche le menu d'abord
    int choice = menu.show(window);
    
    if (choice == 1) {
        
        // Si l'utilisateur a appuyé sur 1, on lance le jeu
        Game game(window); 
        // Passe la fenêtre existante au jeu
        game.run();
    }
    
    return 0;
}