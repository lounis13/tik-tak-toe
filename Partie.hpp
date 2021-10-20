/**
 * @brief   Partie - HEADER
 *
 * @author      Lounis BOULDJA
 * @date        oct 2021
 */
#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <vector>       // std::vector
#include <ostream>      // std::ostream

#include "Joueur.hpp"   // Joueur

class Partie
{

private:

    /**
     * @brief   La grille de jeu est un vector de taille 9 (3 * 3).
     *          On peut faire aussi vectord'un vector (vector<vector<int>>).
     *
     *          PS: raison de choisir cette presentation (sizeof (vector) < size (vector<vector>))
     *              &  temp d'accés a la case [i*3+j] < [i] [j].
     *              pour récupérer/modifier les valeur de la grille on utilise get/set.
     *
     * @see Tournoi::set(int i, int j), Tournoi::get (int i, int g);
     */
    std::vector<int> grille;

    /**
     * @brief  les deux joueurs <<readOnly>> on  les utlise  juste dans l'afichage.
     *         PS: la mise à jour  du score se fait dans le toutnoi (pour faciliter  
     *         le calcul des score dans chque tournoi).
     *         TYPE :
     *         const Joueur * const interdire la modification de (*joueur et joueur).
     */
    const Joueur *const joueur1;
    const Joueur *const joueur2;

    /*nombre de coups joué*/
    int nbcoups;

    /* 0 - pas de gagnant
     * 1 - joueur 1
     * 2 - joueur 2
     */
    int gagnant;

public:
    /**
     * @brief       ctor pour créer une partie. son role est initialiser les deux joueur
     *              & les attributs nbcoups et gangland a zero
     *
     * @param joueur1   joueur 1
     * @param joueur2   joueur 2
     */
    Partie(const Joueur &joueur1, const Joueur &joueur2);

    /**
     * @brief dtor
     */
    virtual ~Partie();

    /**
     * @brief   lancer une partie entre deux joueur.
     *          ICI la boucle principle de jeu.
     */
    void lancer_partie();

    /**
     * @brief   nombre de coups jouer
     * @return  nbcoups
     */
    const int get_nbcoups() const;

    /**
     * @brief   le gagnant
     * @return  0 -> pas de gagnant
     *          1 -> joueur 1
     *          2 -> joueur 2
     */
    const int get_gagnant() const;

    /**
     * @brief   Surcharger l'operateur << - pour afficher les info d'une partie
     *          Le role de friend (amitié) pour accéder aux champs private d'une partie
     * @param os        flux de sortie
     * @param partie    une partie
     * @return os stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Partie &partie);

    /**
     * @brief   quelques fonctions utiles pour bien découper le code et l'affichage.
     *
     *          PS : la declaration des parameters des ces fonctions ne sont pas en const
     *          car le const-qualification des paramètres dans ces fonction n'a d'effet que
     *          dans les définitions de fonction
     */
private:

    /**
     * @brief   Get  la valuer (i, j) de la grille
     *          [i][j] -> [i * 3 + J]
     * @param i     ligne
     * @param j     colonne
     * @return      grille [i * 3 + J]
     */
    int get(size_t i, size_t j) const;

    /**
     * @brief   Set  la valuer (i, j) de la grille
     *          grille[i * 3 + j]
     * @param i      i
     * @param j      j
     * @param joueur joueur (1, 0)
     */
    void set(size_t i, size_t j, int joueur);

    /**
     * @brief  Demander à l'utilisateur de choisir une case pour joueur
     *
     * @param  joueur   joueur (1, 0).
     */
    void jouer(int joueur);

    /**
     * @brief   Tester s'il y a un gagnant.
     *
     * @param i     int indice i
     * @param j     int indice j
     *
     * @return      0 - pas de gagnant
     *              1 - joueur 1
     *              2 - joueur 2
     */
    int gagner(int i, int j) const;

    /**
     * @brief   affichage de la grille.
     *
     * @param ligne    la ligne
     * @param col       la colonne
     */
    void affiche_grille(size_t ligne, size_t col) const;

    /**
     * @brief affichage sur la console.
     */
    void afficher_entete() const;

};

/**
 * @brief       une saisi ("un peu sécurisé") des entiers en cpp
 *
 * @param min   minimum
 * @param max   maximum
 *
 * @return      une valeur valide entre (min et max).
 */
int saisir_entier(int min, int max);

#endif /*PARTIE_HPP*/