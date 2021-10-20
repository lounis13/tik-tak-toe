/**
 * @brief   Joueur - HEADER
 *
 * @author  Lounis BOULDJA
 * @date    oct 2021
 */
#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>   // std::string
#include <ostream>  // std::ostream

class Joueur
{

private:
    /**
     * @brief   identifiant : nom de joueur
     *          PS: on peut mettre id en public vu qu'il est constant (readOnly).
     */
    const std::string id;

    /* Score totale*/
    double score;

public:

    /**
     * @brief   Ctor, son rôle est  d'initialiser  les joueurs  créés en mettant
     *          leur score à ZERO.
     *
     *          PS : constructeurs à argument unique c'est mieux de le  marqués comme `explicit`
     *          pour éviter les conversions implicites involontaires.
     *          @see http://www.cplusplus.com/forum/general/168292/
     *
     * @param id    identifiant d'un joueur.
     */
    explicit Joueur(const std::string &id);

    /**
     * @brief   get le id d'un joueur.
     * 
     * @return const std::string&   le nom de fichier.
     */
    const std::string &getId() const;

    /**
     * @brief dtor
     */
    virtual ~Joueur();

    /**
     * @brief   get le score d'un jouer
     * 
     * @return double   le score 
     */
    const double getScore() const;

    /**
     * @brief   Mise  à  jour de  score,  le   score  du  gagnant  s'augmente  de  
     *          9 / (nbcoups+nbcoups%2). Le score du joueur ne fait  qu’augmenter
     *          au  cours  du tournoi et est conservé entre  deux  tournois. Donc 
     *          plus un joueur  participe à des tournois, plus son score augmente.
     * 
     * @param nbcoups   Correspond aux nombre de coups joués lors de la partie.
     */
    void maj_score(const int nbcoups);

    /**
     * @brief   Surcharge l'operateur == (equal)
     *
     * @param joueur    joueur
     *
     * @return     true  - les deux joueur sont égaux
     *             false - sinon
     */
    bool operator==(const Joueur &joueur) const;

    /**
    * @brief   Surcharge l'operateur != (!equal)
    *
    * @param joueur    joueur
    *
    * @return     true   - les deux joueur sont different
    *             false - sinon
    */
    bool operator!=(const Joueur &joueur) const;

    /**
     * @brief   Surcharger l'operateur << - pour afficher un joueur
     *          Le role de friend (amitié) pour accéder aux champs private d'un Joueur
     *
     * @param   os        flux de sortie
     * @param   joueur    Le joueur
     *
     * @return std::ostream&    out put stream (char) apres la surcharge.
     */
    friend std::ostream &operator<<(std::ostream &os, const Joueur &joueur);
};


/**
 * @brief  COLORS   pour affichage
 *         PS : c'est mieux d' utiliser constexpr std::string_view (c++ 14 et plus)
 */
#if __linux__ || __APPLE__
const std::string BOLD("\033[1m");
const std::string GREEN("\033[32m");
const std::string ENDER("\033[4m");
const std::string B_BACK("\033[44m");
const std::string BLANK("\033[0m");
const std::string YELL("\033[33m");
const std::string BLUE("\033[34m");
const std::string RED("\033[31m");
const std::string LIGHT("\033[2m");

// window, other os ...
#else
const std::string BOLD("");
const std::string GREEN("");
const std::string ENDER("");
const std::string B_BACK("");
const std::string BLANK("");
const std::string BLUE("");
const std::string YELL("");
const std::string RED("");
const std::string LIGHT("");
#endif /*OS*/

#endif /*JOUEUR_HPP*/