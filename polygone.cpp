/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2019 | TP1 | polygone.cpp
*/

#include <cmath>
#include <limits>
#include "polygone.h"

 Polygone::Polygone()
 {
     capacite=3;
     P=new Point[capacite];
     nb_points=0;
     nom="";
 }

 Polygone::Polygone(std::string str)
 {
     capacite=3;
     P=new Point[capacite];
     nb_points=0;
     nom=str;
 }
 
 /*
 Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre){
    if(this==&autre) return *this;

    nbElements = autre.nbElements;
    if(capacite<autre.nbElements || autre.nbElements*2<capacite)
    {
        delete[] elements;
        capacite = autre.capacite;
        elements = new T[capacite];
    }
    for(int i=0;i<nbElements;i++)
        elements[i] = autre.elements[i];  
    return *this;
}
 */
Polygone& Polygone::operator = (const Polygone& autre){
    if(this==&autre) return *this;

    nb_points = autre.nb_points;
    if(capacite<autre.nb_points || autre.nb_points*2<capacite)
    {
        delete[] P;
        capacite = autre.capacite;
        P = new Point[capacite];
    }
    for(int i=0;i<nb_points;i++)
        P[i] = autre.P[i];  
    nom=autre.nom;
    return *this;
}

 Polygone::Polygone(int capacite_)
 {
     capacite=capacite_;
     P=new Point[capacite];
     nb_points=0;
     nom="";
 }
 

Polygone::~Polygone()
{
    delete[] P;
    P=NULL;
}
double Polygone::distance(const Polygone& poly2) const
{
    //int a = std::numeric_limits<int>::max();
    //float a = float a = std::numeric_limits<float>::infinity();
    double DM = std::numeric_limits<float>::infinity();
    double d;
    for(int i=0;i<nb_points;i++)
    {
        Polygone a_b("segment");
        if(i==nb_points-1)
        {
            a_b.ajouter(P[i]);//coté AB
            a_b.ajouter(P[0]); 
        }
        else
        {
            a_b.ajouter(P[i]);
            a_b.ajouter(P[i+1]);
        }
        for(int j=0;j<poly2.nb_points;j++)
        {
            Polygone c_d("segment");
            if(j==poly2.nb_points-1)
            {
                c_d.ajouter(poly2.P[j]);
                c_d.ajouter(poly2.P[0]);
            }
            else
            {
                c_d.ajouter(poly2.P[j]);
                c_d.ajouter(poly2.P[j+1]);
            }
            
            //distance (A,CD)
            d=c_d.distance_segment_point(a_b.P[0]);
            DM=d<DM ? d:DM;
            //distance (B,CD)
            d=c_d.distance_segment_point(a_b.P[1]);
            DM=d<DM ? d:DM;
            //distance (C,AB)
            d=a_b.distance_segment_point(c_d.P[0]);
            DM=d<DM ? d:DM;
            //distance (D,AB)
            d=a_b.distance_segment_point(c_d.P[1]);
            DM=d<DM ? d:DM;      

        }

    }
    return DM;
}

/*double Polygone::distance_segment( const Polygone& poly2) const
{
    double x_ca=P[0].x-poly2.P[0].x;
    double y_ca=P[0].y-poly2.P[0].y;
    Point CA(x_ca,y_ca);
    double x_cd=poly2.P[0].x-poly2.P[1].x;
    double y_cd=poly2.P[0].y-poly2.P[1].y;
    Point CD(x_cd,y_cd);
    double temp=(CA.distance(CD))/(CD.distance(CD));
    Point result(temp*x_cd,temp*y_cd);
    std::cout<<"P"<<this<<std::endl;
    std::cout<<"Poly2"<<poly2<<std::endl;
    std::cout<<"CA"<<CA<<std::endl;
    std::cout<<"CD"<<CD<<std::endl;
    return 0;
}*/

double Polygone::distance_segment_point( const Point& point) const
{
    double d_x=P[1].x-P[0].x;
    double d_y=P[1].y-P[0].y;
    Point vecteur_CD(d_x,d_y);// vecteur CD
    Point vecteur_CA(point.x-P[0].x,point.y-P[0].y);
    //std::cout<<"CA:"<<vecteur_CA<<std::endl;
    //std::cout<<"CD:"<<vecteur_CD<<std::endl;
    double ratio=(vecteur_CA.distance(vecteur_CD))/(vecteur_CD.distance(vecteur_CD));
    if(ratio>1)
    {
        ratio=1;
    }
    else
    {
        if(ratio<0)
        {
            ratio=0;
        }
    }
    //std::cout<<"ratio:"<<ratio*d_x<<std::endl;
    Point V(ratio*d_x,ratio*d_y);
    //std::cout<<V<<std::endl;
    Point T(P[0].x+V.x,P[0].y+V.y);
    //std::cout<<T<<std::endl;
    double dist_TA=sqrt(((T.x-point.x)*(T.x-point.x))+((T.y-point.y)*(T.y-point.y)));
    //std::cout<<"d="<<dist_TA<<std::endl;
    return dist_TA;
}

void Polygone::affiche_nom()
{
    std::cout<<nom<<std::endl;
}
double Polygone::aire() const{
    int aire=0;
    int j=nb_points-1;
    for(int i=0;i<nb_points;i++)
    {
        aire= aire + (P[i].x+P[j].x)*(P[j].y-P[i].y);
        j=i;
    }
    return fabs(aire/2);
}

std::ostream& operator << (std::ostream& os, const Polygone& polygone){
    // À compléter.
    os << polygone.nom<<" : ";
    for(int i=0;i<polygone.nb_points;i++)
    {
        os<< polygone.P[i];
        (i!=polygone.nb_points-1)? os<<"," : os<<";";
    }
    //os << "A : (0,0), (0,1), (1,1) ;";
    return os;
}
void Polygone::redimensionner(int nv_capacite)
{
   Point * temp=new Point[nv_capacite];
    for(int i=0;i<capacite;i++)
    {
        temp[i]=P[i];
    }
    delete []P;
    capacite=nv_capacite;
    P=temp;
}

void Polygone::ajouter(const Point& point)
{
    if(nb_points>=capacite)
    {
        redimensionner(capacite*2);
    }
    P[nb_points]=point;
    nb_points++;
}

std::istream& operator >> (std::istream& in, Polygone& polygone){
    // À compléter­.
    char c;
    do{
        Point p;
        in >> p >> c >> std::ws;
        polygone.ajouter(p);
    }while(c==',');
    assert(c==';');
    return in;
}

/*
ae ← 0; // aire de l'empire
choix ← ?
pour r1 = 0 .. regions.taille() - 1
|   pour r2 = 0 .. regions.taille() -1
|   |   si r1≠r2 et distance(regions[r1], regions[r2]) ≤ DM alors :
|   |   |   si(aire(regions[r1]) + aire(regions[r2]) > ae) alors :
|   |   |   |  ae ← aire(regions[r1]) + aire(regions[r2])
|   |   |   |  choix ← r1 "\n" r2 "\n"
afficher ae "\n"
afficher choix
    */
