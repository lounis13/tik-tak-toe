/**
 * @brief   Tournoi - SOURCE
 *
 * @author  Lounis BOULDJA
 * @date    oct 2021
 */

#include <iomanip>       // std::setw
#include "Tournoi.hpp"
#include "Partie.hpp"

Tournoi::Tournoi() : scores_participants(0), fin_inscription(false), meilleur_tournoi_score(0.0) {}

void Tournoi::inscription(Joueur &joueur)
{
    /* Le tournoi n'est pas encore commencer */
    if (!fin_inscription)
    {
        for (const auto &participant: participants)
            /* Joueur deja inscrit → on sort de la fonction */
            if (participant == &joueur || *participant == *&joueur)
            {
                std::cout << "  [ERROR] Le joueur est deja inscrit " << std::endl;
                return;
            }

        /* ICI le joueur nest pas inscrit → ajouter le dans la liste des participants */
        participants.push_back(&joueur);
        /* Initialiser le score de participant dans CE TOURNOI à zero */
        scores_participants.push_back(0);
    }

}

void Tournoi::lance_tournoi()
{
    /* Fermer les indcriptions */
    fin_inscription = true;

    /* Les participants jouent une fois exactement avec chaque autre participant.*/
    for (size_t i = 0; i < participants.size(); ++i)
        for (size_t j = i + 1; j < participants.size(); ++j)
            organiser_partie(i, j);

    /* Afficher les joeeurs gagnants */
    afficher_gagnants();

    /* Afficher les information d'un tournoir */
    std::cout << *this << std::endl;

    /* Reouvrir les inscriptions*/
    fin_inscription = false;
    meilleur_tournoi_score = 0;
}

void Tournoi::vide_participants()
{
    /* Vider la liste des participants */
    participants.clear();

    /* Vider la liste des scores */
    scores_participants.clear();

    meilleur_tournoi_score = 0;
    fin_inscription = 0;
}

std::ostream &operator<<(std::ostream &os, const Tournoi &tournoi)
{
    os << BOLD << "Scores totaux des participants : " << BLANK;
    for (size_t i = 0; i < tournoi.participants.size(); ++i)    
    {
        os  << "\n ┌────────────────────────────────────────────────────────────────────┐" << std::endl
            << " │  [JOUEUR] " << BOLD << std::setw(10) << std::left << tournoi.participants[i]->getId()
            << BLANK << " score tournoi : " << BLUE << BOLD << tournoi.scores_participants[i] << "\t" 
            << BLANK << "Score Total : " << BOLD << GREEN << std::setw(7) << std::left << tournoi.participants[i]->getScore() << BLANK
            << " │\n" << " └────────────────────────────────────────────────────────────────────┘" << BLANK;
    }

    return os;
}


void Tournoi::organiser_partie(const size_t indice_joueur1, const size_t indice_joueur2)
{
    /* Creation d'une partie */
    Partie partie(*participants[indice_joueur1], *participants[indice_joueur2]);
    partie.lancer_partie();
    /* MAJ les scores */
    maj_tournoi(partie.get_gagnant(), partie.get_nbcoups(), indice_joueur1, indice_joueur2);
    afficher_infos_joueurs(indice_joueur1, indice_joueur2);
}

void
Tournoi::maj_tournoi(const int gagnant, const int nbcoups, const size_t indice_joueur1, const size_t indice_joueur2)
{
    if (gagnant)
    {
        /* le joueur gagnant */
        size_t indice_gagnant = (gagnant == 1) ? indice_joueur1 : indice_joueur2;

        /* MAJ des scores */
        participants[indice_gagnant]->maj_score(nbcoups);
        scores_participants[indice_gagnant] += 9.0 / (nbcoups + (nbcoups % 2));

        afficher_gagnant_partie(indice_gagnant);

        /* Meilleur score */
        if (scores_participants[indice_gagnant] > meilleur_tournoi_score)
            meilleur_tournoi_score = scores_participants[indice_gagnant];
    } else
        std::cout << BOLD  << "Partie nulle " << BLANK ;
}


/****************************************/
/**     méthodes pour l' affichage    **/
/***************************************/


void Tournoi::afficher_gagnant_partie(const size_t indice_gagnant) const
{
    std::cout << BOLD
              << " ┌───────────────────────────────────────────────────┐" << std::endl
              << " │  [FIN]: ✨ Bravo " << std::setw(10) << std::left << participants[indice_gagnant]->getId() + " ✨"
              << " vous avez gagné " << "       │" << std::endl
              << " └───────────────────────────────────────────────────┘" << BLANK << std::endl;
}

void Tournoi::afficher_gagnants() const
{
    std::cout << "     ┌──────────────────────────┐    " << std::endl
              << "┌────┤" << B_BACK << BOLD << "        FIN TOURNOI       " << BLANK << "├────┐" << std::endl
              << "│    └──────────────────────────┘    │" << std::endl
              << "│                                    │" << std::endl
              << "│   Meilleur score :                 │" << std::endl
              << "│                 " << BOLD << GREEN << std::setw(19) << std::left
              << meilleur_tournoi_score << BLANK << "│" << std::endl
              << "│   Les gagnants :                   │" << std::endl;

    for (size_t i = 0; i < participants.size(); ++i)
        if (scores_participants[i] == meilleur_tournoi_score)
            std::cout << "│ \t\t  " << std::setw(22) << std::left << YELL + participants[i]->getId() << BLANK
                      << std::setw(5)
                      << std::right << "│" << std::endl;

    std::cout << "│                                    │" << std::endl
              << "└────────────────────────────────────┘" << std::endl; 

}

void Tournoi::afficher_infos_joueurs(const size_t joueur1, const size_t joueur2) const
{
    std::cout << YELL << "│ - Score actuel des deux joueurs" << BLANK << std::endl
              << LIGHT << " \t\t     ┌──────────────────────┬────────────────────┐" << std::endl
              << " \t\t     │     Score tournoi    │     Score total    │" << std::endl
              << " ┌───────────────────┼──────────────────────┼────────────────────┤" << std::endl;
    affiche_joueur_score_tournoi_total(joueur1);
    affiche_joueur_score_tournoi_total(joueur2);
    std::cout << " └───────────────────┴──────────────────────┴────────────────────┘ " << BLANK << std::endl;
}

void Tournoi::affiche_joueur_score_tournoi_total(const size_t indice_joueur) const
{
    std::cout << " │       " << std::setw(10) << std::left << participants[indice_joueur]->getId() << "  │         "
              << BLANK << BOLD << std::setw(7) << std::left << scores_participants[indice_joueur] << LIGHT
              << "      │       "
              << BLANK << BOLD << std::setw(7) << std::left << participants[indice_joueur]->getScore() << BLANK << LIGHT
              << "      │"
              << std::endl
              << " ├───────────────────┼──────────────────────┼────────────────────┤" << std::endl;

}

Tournoi::~Tournoi() = default;