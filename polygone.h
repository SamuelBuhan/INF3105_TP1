/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2019 | TP1 | polygone.h 
*/

#if !defined(__POLYGONE_H__)
#define __POLYGONE_H__
#include <iostream>
#include "point.h"
#include "tableau.h"


class Polygone {
  public:
    Polygone();
    Polygone(std::string str);
    Polygone(int capacite_);
    ~Polygone();
    Polygone& operator = (const Polygone& autre);
    void affiche_nom();
    void ajouter(const Point& point);
    void redimensionner(int nv_capacite);
    double distance(const Polygone& poly2) const;
    double distance_segment(const Polygone& poly2) const;
    double distance_segment_point( const Point& point) const;
    double aire() const;

  private:
    // Représentation : à compléter.
    Point * P;
    int nb_points;
    int capacite;
    std::string nom;


  friend std::ostream& operator << (std::ostream&, const Polygone&);
  friend std::istream& operator >> (std::istream&, Polygone&);
};

#endif

