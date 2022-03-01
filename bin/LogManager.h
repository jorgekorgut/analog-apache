/*************************************************************************
                           LogManager  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <LogManager> (fichier LogManager.h) ----------------
#if ! defined ( LOGMANAGER_H )
#define LOGMANAGER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
// Specialisation de la fonction hash afin de prendre en compte des cles sur la forme de pair<string,string>
namespace std
{
	template<>
	struct hash<pair<string,string>>
	{
		size_t operator()(const pair<string,string> & target) const
		{
			hash<string> hashStr;
			return hashStr(target.first+target.second);
		}
	};
}
//------------------------------------------------------------------------
// Rôle de la classe <LogManager>
// Cette classe sert à lire et interpréter le fichier log. à la fin de son exécution des structures de 
// données bien formées donnent un aperçu global du fichier log apache.
//------------------------------------------------------------------------

class LogManager
{
//----------------------------------------------------------------- PUBLIC

	public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    	LogManager (const vector<string> & path, const set<int> &time=set<int>(), const int &top=-1, const bool &exclude=false, const vector<string> &graph=vector<string>());

		virtual ~LogManager ( );

		const unordered_map<pair<string,string>,int> & GetGraph() const;

		const unordered_map<string,pair<int,int>> & GetCount_url() const;

		const unordered_map<string,pair<int,int>>::iterator* GetTop_url() const;

		const int & GetTopSize() const;
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
		int fileRead(const string & path,const int &top, const bool &exclude, const vector<string> &graph_path);
//----------------------------------------------------- Attributs protégés
		set<int> heures;

		int topCurrentSize;

		unordered_map<pair<string,string>,int> graphMap;

		unordered_map<string,pair<int,int>> count_url;

		unordered_map<string,pair<int,int>>::iterator* top_url;
};
//-------------------------------- Autres définitions dépendantes de <LogManager>

#endif // LOGMANAGER_H
