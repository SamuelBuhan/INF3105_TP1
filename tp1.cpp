/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2019 | TP1 | tp1.cpp
*/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include "polygone.h"
#include "tableau.h"

using namespace std;

void nb_region(Tableau <Polygone>& ,int * iterateurs, int nb_for, int nb_regions, int aire_empire);
void increment_iterateurs(int* iterateurs, int nb_iterateurs, int nv_iterateur);

void increment_iterateurs(int* iterateurs, int nb_iterateurs, int nv_ite, int nv_iterateur)
{
    nb_iterateurs++;
    int temp[nb_iterateurs];
    for(int i = 0; i < nb_iterateurs - 1; i++)
    {
        temp[i] = iterateurs[i];
    }
}
void nb_region(Tableau <Polygone>& list ,int * iterateurs, int nb_for, int nb_regions, int aire_empire)
{
    int i;
    for(int i=0;i<list.taille();i++)
    {

        if(nb_for == nb_regions)
        {
            if(iterateurs_dif && distance_verif)
            {
                if(aire_totale()>aire_empire)
                {
                    aire_empire=aire_totale();
                }
            }
        }
        else
        {
            nb_region(list ,iterateurs,nb_for + 1,nb_regions,aire_empire);
        }
        
    }

}

int main(int argc, const char** argv){
    if(argc<3){
        cout << "./tp1 carte.txt nbRegions [distMax]" << endl;
        return 1;
    }
    
    const char* fichiercarte = argv[1];
    int nbRegions = atoi(argv[2]);
    double DM = argc>=4 ? atof(argv[3]) : numeric_limits<double>::infinity();
    assert(DM>=0);
    
    ifstream in(fichiercarte);
    if(in.fail()){
        cout << "Imposible de lire le fichier " << fichiercarte << endl;
        return 2;
    }
    Tableau <Polygone> list= Tableau <Polygone>();
    while(!in.eof()){
        string nom;
        char deuxpoints;
        in >> nom >> deuxpoints;
        Polygone polygone(nom);
        assert(deuxpoints==':');
        in >> polygone >> std::ws;
        //cout<<polygone<<endl;
        list.ajouter(polygone);
    }
    //cout<<list[0]<<list[1]<<list[2]<<endl;
    //cout<<list[0].distance_segment_point(Point(2,3))<<endl;
    switch(nbRegions){
        case 1:
        {
            int aire_max=list[0].aire();
            int index=0;
            for(int i=1;i<list.taille();i++)
            {
                if(list[i].aire()>aire_max)
                {
                    aire_max=list[i].aire();
                    index=i;
                }
            }

            cout << round(aire_max) << endl;
            list[index].affiche_nom();
            break;
        }
        case 2:
        {
            //cout<<list[0].distance(list[1]) <<endl;
            //cout << list[0] << endl;
            int aire_empire=0;
            string choix="";
            for(int i=0;i<list.taille();i++)
            {
                for(int j=0;j<list.taille();j++)
                {
                    //cout<<list[i].distance(list[j])<<"<DM="<<DM<<endl;
                    //cout<<(list[i].distance(list[j])<=DM)<<endl;
                     if(i!=j && list[i].distance(list[j])<=DM)
                    {
                        //cout<<"----------here---------"<<endl;
                        if(list[i].aire()+list[j].aire()>aire_empire)
                        {
                            aire_empire=list[i].aire()+list[j].aire();
                            choix=to_string(i)+"\n"+to_string(j)+"\n";
                        }
                    } 
                }
            }
            // ajouter le cas avec max des regions si aire_empire=0;
            cout<<"aire empire:"<<aire_empire<<endl;
            cout<<choix<<endl; 
            break;
        }
        case 3:
        {
            int aire_empire=0;
            string choix="";
            for(int i=0;i<list.taille();i++)
            {
                for(int j=0;j<list.taille();j++)
                {
                    //cout<<list[i].distance(list[j])<<"<DM="<<DM<<endl;
                    //cout<<(list[i].distance(list[j])<=DM)<<endl;
                    for(int k=0;k<list.taille();k++)
                    {
                        if(i!=j && k!=j && k!=i && list[i].distance(list[j])<=DM && list[j].distance(list[k])<=DM)
                        {
                            //cout<<"----------here---------"<<endl;
                            if(list[i].aire()+list[j].aire()+list[k].aire()>aire_empire)
                            {
                                aire_empire=list[i].aire()+list[j].aire()+list[k].aire();
                                choix=to_string(i)+"\n"+to_string(j)+"\n"+to_string(k)+"\n";
                            }
                        } 
                    }
                     
                }
            }
            cout<<"aire empire:"<<aire_empire<<endl;
            cout<<choix<<endl; 
        }
        break;
        default:

            cout << "Ce programme ne supporte pas 4 régions ou plus!" << endl;
            break;
    }

    return 0;
}
