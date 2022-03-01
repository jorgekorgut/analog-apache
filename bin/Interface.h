/*************************************************************************
                           Interface  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Interface> (fichier Xxx.h) ----------------
#if ! defined ( INTERFACE_H )
#define INTERFACE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include "LogManager.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Interface>
// Cette classe sert à transformer les données de sortie de la classe LogManager dans le format
// Attendu.
// Elle fait l’affichage du top, la construction du fichier graph.dot et le mannagement du flux 
// d’entrée de l’utilisateur
//------------------------------------------------------------------------

class Interface
{
//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques
    void Start(int argc,char * argv[]);
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Interface ( );

    virtual ~Interface ( );

//------------------------------------------------------------------ PRIVE
  protected:
//----------------------------------------------------- Méthodes protégées

		void show_help( bool error = false) const;

    void constructGraphFile(LogManager & lm) const;

    void printTop(const LogManager & lm) const;
//----------------------------------------------------- Attributs protégés

    set<int> time;

    int top;

    vector<string> graph;

    vector<string> path;

    bool exclude;
};
//-------------------------------- Autres définitions dépendantes de <Interface>

#endif // INTERFACE_H