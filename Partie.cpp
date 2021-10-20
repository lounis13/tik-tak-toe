/**
 * @brief   Partie - HEADER
 *
 * @author  Lounis BOULDJA
 */

#include <iostream>     // std::cout, std::cin
#include <iomanip>      // std::setw
#include <limits>

#include "Partie.hpp"

Partie::Partie(const Joueur &j1, const Joueur &j2) : grille(9), joueur1(&j1), joueur2(&j2), nbcoups(0), gagnant(0) {}

Partie::~Partie() = default;

void Partie::lancer_partie()
{
    afficher_entete();
    /*si nbcoups == 9 (Partie nulle)*/
    while (nbcoups != 9 && !gagnant)
        /* joueur 1 : le nbcoups est pair joueur 2 : sinon */
        jouer((nbcoups % 2) + 1);

}

void Partie::jouer(int joueur)
{
    int i, j;
    std::cout << "   [" << ((joueur == 1) ? joueur1->getId() : joueur2->getId()) + "] Entrez une case i j : ";
    i = ::saisir_entier(0, 2);
    j = ::saisir_entier(0, 2);

    /* case vide*/
    if (!get(i, j))
    {
        set(i, j, joueur);
        ++nbcoups;

        /* TEST si le coup est gagnant*/
        gagnant = gagner(i, j);
        affiche_grille(i, j);
    }
        /* case non vide*/
    else
        std::cout << RED << BOLD << "   [ERROR]" << BLANK << " Case non vide !" << std::endl;
}

int Partie::gagner(int i, int j) const
{
    return
            (
                    /* Ligne gagnante*/
                    ((get(i, j) == get(i, (j + 1) % 3)) && get(i, j) == get(i, (j + 2) % 3))

                    /* Colonne gagnant*/
                    || (get(i, j) == get((i + 1) % 3, j) && get(i, j) == get((i + 2) % 3, j))

                    /* diagonale */
                    || (i == j && get(i, j) == get((i + 1) % 3, (j + 1) % 3) && get(i, j) == get((i + 2) % 3, (j + 2) % 3))

                    /* dernière ligne ou colonne */
                    || (i + j == 2 && get(i, j) == get((i + 2) % 3, (j + 1) % 3) &&
                        get(i, j) == get((i + 1) % 3, (j + 2) % 3))

            )
            /* Joueur qu'a gagné (1 : joueur 1, 0 : joueur 2)*/
            ? get(i, j)
            /* Pas de gagnant*/
            : 0;
}

const int Partie::get_nbcoups() const
{
    return nbcoups;
}

const int Partie::get_gagnant() const
{
    return gagnant;
}

std::ostream &operator<<(std::ostream &os, const Partie &partie)
{
    for (size_t i = 0; i < partie.grille.size(); ++i)
    {
        os << partie.grille[i] << "\t";
        /* Saut à la ligne*/
        if (!((i + 1) % 3))
            os << "\n";
    }
    return os;
}


/*****************************************/
/**        Fonctions utiles             **/
/*****************************************/

int Partie::get(const size_t i, const size_t j) const
{
    return grille[i * 3 + j];
}

void Partie::set(const size_t i, size_t j, const int joueur)
{
    grille[i * 3 + j] = joueur;
}

void Partie::afficher_entete() const
{
    std::cout << "\n 🎮 ─────│" << B_BACK << BOLD << "Partie entre  🧑  " << joueur1->getId() << "  🎮  👨  "
              << joueur2->getId() << BLANK << "│───── 🎮\n" << std::endl;

}

void Partie::affiche_grille(const size_t ligne, const size_t col) const
{
    std::vector<std::string> str_grille(9, "");

    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (i == ligne && j == col)
                str_grille[i * 3 + j].append(BOLD).append(GREEN).append(ENDER).append(
                        std::to_string(get(i, j)).append(BLANK));
            else
                str_grille[i * 3 + j] += std::to_string(get(i, j));

        }
    }
    printf(" \n       ┌─────┬─────┬─────┐\n"
           "       │  %s  │  %s  │  %s  │\n"
           "       ├─────┼─────┼─────┤\n"
           "       │  %s  │  %s  │  %s  │\n"
           "       ├─────┼─────┼─────┤\n"
           "       │  %s  │  %s  │  %s  │\n"
           "       └─────┴─────┴─────┘\n", str_grille[0].c_str(), str_grille[1].c_str(), str_grille[2].c_str(),
           str_grille[3].c_str(), str_grille[4].c_str(), str_grille[5].c_str(),
           str_grille[6].c_str(), str_grille[7].c_str(), str_grille[8].c_str()
    );
}

int saisir_entier(int min, int max)
{
    int number = 0;
    std::cin >> number;
    while (true)
    {
        if (std::cin.fail())
        {
            /* vider les buffer */
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << RED << BOLD << "   [ERROR]" << BLANK << "Vous avez entré une mauvaise entrée !" << std::endl << "   Ressayez : ";
            std::cin >> number;
        }
        if (!std::cin.fail())
        {   /* entre min et max */
            if (number < min || number > max)
            {
                std::cerr << RED << BOLD << "[ERROR]" << BLANK  << "Vous avez entré un mauvais nombre (min, max) : " << min << ", " << max << std::endl;
                std::cin >> number;
            } else
                break;
        }
    }
    return number;
}