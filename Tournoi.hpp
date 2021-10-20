/**
 * @brief   Tournoi - HEADER
 *
 * @author  Lounis BOULDJA
 * @date    oct 2021
 */

#ifndef TOURNOI_HPP
#define TOURNOI_HPP

#include <iostream>     // std::cout
#include <vector>       // std::vector

#include "Joueur.hpp"   // Joueur

class Tournoi
{

private:

    /**
     * @brief   vector des participants, le type des element est (Joueur *), car on
     *          veut mettre a jour meme les scores des joueurs en dehors de tournoi,
     *          (sinon on perd les changement faites dans un tournoi).
     *
     *          PS: c++11 (ou plus) on peut utiliser unr vector<reference_wrapper<T>>
     */
    std::vector<Joueur *> participants;

    /**
     * @brief   scores des participant dans le tournoi.
     *
     *          PS: on peut utiliser  direct une map ( exp : <Joueur, double>).
     *             (il faut def la fonction hachage & opr==).
     */
    std::vector<double> scores_participants;

    /* Fin inscription = debut de tournoi*/
    bool fin_inscription;

    /*Meilleur score de tournoi*/
    double meilleur_tournoi_score;

public:

    /**
     * @brief   Ctor, son rôle est  d'initialiser  un tournoi  créé en mettant
     *          les scores a zero
     */
    Tournoi();

    virtual ~Tournoi();

    /**
     * @brief   Inscrire un joueur à un tournoi tant que celui-ci n’a pas débuté.
     *          TEST ! si le joueur si il'a deja inscrit.
     * 
     * @param joueur    Le joueur pour l'inscrire
     */
    void inscription(Joueur &joueur);

    /**
     * @brief   Lancer un tournoi - jouer  les participants deux à deux.
     *          Lorsque le tournoi débute, les inscriptions sont closes.
     *          Elles doivent pouvoir réouvrir à la fin du tournoi
     */
    void lance_tournoi();

    /**
     * @brief   Désinscrire tous les participants
     */
    void vide_participants();

    /**
     * @brief   surcharge << operator
     * @param os        flux de sortie
     * @param tournoi   tournoi
     * @return          os stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Tournoi &tournoi);


/**
 * @brief   fonctions (privates) utiles pour découper le code et l' affichage
 *
 *          PS : la declaration des parameters des ces fonctions ne sont pas en const
 *          car le const-qualification des paramètres dans ces fonction n'a d'effet que
 *          dans les définitions de fonction
 */
private:

    /**
     * @brief       organiser une partie entre deux joueur.
     *
     * @param indice_joueur1    indice de premier joueur
     * @param indice_joueur2    indice de detriment joueur
     */
    void organiser_partie(size_t indice_joueur1, size_t indice_joueur2);

    /**
     * @brief       mise a jour (scores, meilleur score ...)
     *
     * @param gagnant           gagnant
     * @param nbcoups           nombre de coups joué
     * @param indice_joueur1    indice de premier joueur
     * @param indice_joueur2    indice de detriment joueur
     */
    void maj_tournoi(int gagnant, int nbcoups, size_t indice_joueur1, size_t indice_joueur2);



    /**
     * @brief afficher le gagnant
     */
    void afficher_gagnants() const;

    /**
     * @brief   afficher les scores d'un joueur
     * @param indice_joueur     indice de joueur.
     */
    void affiche_joueur_score_tournoi_total(size_t indice_joueur) const;

    /**
     * @brief   affichage
     * @param indice_gagnant  indice gagnant
     */
    void afficher_gagnant_partie(size_t indice_gagnant) const;

    /**
     * @brief afficher les info d'un joueur.
     * @param joueur1
     * @param joueur2
     */
    void afficher_infos_joueurs(size_t joueur1, size_t joueur2) const;
};

#endif /*TOURNOI_HPP*/