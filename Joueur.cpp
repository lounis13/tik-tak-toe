/**
 * @brief   Joueur - SOURCE
 *
 * @author  Lounis BOULDJA
 */

#include <iomanip>      // std::setw

#include "Joueur.hpp"

Joueur::Joueur(const std::string &id) : id(id), score(0) {}

const std::string &Joueur::getId() const
{
    return id;
}

const double Joueur::getScore() const
{
    return score;
}

void Joueur::maj_score(const int nbcoups)
{
    score += 9.0 / (nbcoups + (nbcoups % 2));
}

bool Joueur::operator==(const Joueur &joueur) const
{
    return id == joueur.id && score == joueur.score;
}

bool Joueur::operator!=(const Joueur &joueur) const
{
    return !(joueur == *this);
}

std::ostream &operator<<(std::ostream &os, const Joueur &joueur)
{
    os << " ┌───────────────────────────────────────────┐" << std::endl;
    os << " │  [JOUEUR] " << BOLD << std::setw(10) << std::left << joueur.getId()
              << BLANK << "Score Total : " << BOLD << GREEN << std::setw(7) << std::left << joueur.getScore() << BLANK
              << " │\n";
    os << " └───────────────────────────────────────────┘" << BLANK;
    return os;
}

Joueur::~Joueur()= default;
