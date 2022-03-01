/*************************************************************************
                           LogManager  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <LogManager> (fichier LogManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "LogManager.h"
#include "LogStream.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
LogManager::LogManager (const vector<string> &path_arr, const set<int> &time, const int &top, const bool &exclude, const vector<string> &graph)
{
#ifdef MAP
	cerr << "Appel au constructeur de <LogManager>" << endl;
#endif
	top_url = nullptr;
	topCurrentSize=0;
	this->heures=time;
	for ( string path : path_arr )\
	{
		fileRead(path, top, exclude, graph);
	}
}

LogManager::~LogManager ( )
{
#ifdef MAP
    cerr << "Appel au destructeur de <LogManager>" << endl;
#endif
	delete [] top_url;
}

const unordered_map<pair<string,string>,int> & LogManager::GetGraph() const
{
	return graphMap;
}

const unordered_map<string,pair<int,int>> & LogManager::GetCount_url() const
{
	return count_url;
}

const unordered_map<string,pair<int,int>>::iterator * LogManager::GetTop_url() const
{
	return top_url;
}

const int & LogManager::GetTopSize() const
{
	return topCurrentSize;
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
int LogManager::fileRead(const string & path, const int &top, const bool &exclude, const vector<string> &graph_path)
// Algorithme: 
// L’algorithme commence par ouvrir le fichier cible et ESTIMER la quantité d' objets qui seront 
// lues afin de dimensionner notre structure de données dynamique: Une table de hachage 
// (unordered_map). Ensuite pour chaque ligne du fichier il traduit les informations vers un 
// objet “Log” et met à jour l’url ciblé (<STRING,pair<int,int>>) dans notre structure de 
// données. Si c'est la première fois qu'elle apparaît l’url est ajoutée. Cas contraire, un 
// compteur comptabilise cette apparition(<string,pair< INT ,int>>). 

// Pour réaliser le top, une 
// nouvelle structure de données est réalisée, cependant cette fois-ci, un tableau statique 
// d’itérateurs. à chaque insertion dans la liste de urls visitées, ce tableau peut être mis à jour. 
// Deux cas sont analysés: L’apparition dans le top et le changement de place. Afin d’optimiser 
// notre code un nouveau paramètre est ajouté à la structure de données(<string,pair<int, INT >>). Ceci 
// garde référence à la position de l’url dans le top, ce qui optimise le 
// temps d'exécution de notre algorithme.
// 
// Pour la construction du graph rien de nouveau, juste l’insertion ou la mise à jour de l’arc 
// dans la structure de données.
{
	LogStream logS;
	logS.open(path.c_str());
	if(!logS.is_open())
	{
		cerr << "LogManager:fileRead:Error: It was not possible to open this file" << endl;
		return 1; 
	}

	logS.seekg(0, ios_base::end);
	int reserveHash = logS.tellg()/100; // En supposant qu'il y en a 100 caracteres par ligne.

	graphMap.reserve(reserveHash);
	count_url.reserve(reserveHash);

	logS.seekg(0,ios_base::beg);
	
	if(top==-1)
	{
		top_url=nullptr;
	}
	else
	{
		top_url = new unordered_map<string,pair<int,int>>::iterator[top];
		for (int i=0;i<top;i++)
		{
			top_url[i]=count_url.end();
		}
	}

	const Log * currentLog = logS.GetNextLine();
	int topMinValue = 0;
	string url;
	unordered_map<string,pair<int,int>>::iterator currentCountMap;
	unordered_map<pair<string,string>,int>::iterator currentGraph;
	while(currentLog != nullptr)
	{
		if(
				(heures.size() == 0 || heures.count(currentLog -> GetHour()) == 1) &&
				(!exclude || (
					currentLog -> GetTargetExt()!="jpg" &&
					currentLog -> GetTargetExt()!="gif" &&
					currentLog -> GetTargetExt()!="png" &&
					currentLog -> GetTargetExt()!="ico" &&
					currentLog -> GetTargetExt()!="bmp" &&

					currentLog -> GetTargetExt()!="css" &&
					currentLog -> GetTargetExt()!="js" )))
		{
			url= currentLog -> GetHostTarget() + currentLog -> GetTarget();
			url=url.substr(0,url.find("?"));
			if(top!=-1)
			{
				currentCountMap=count_url.find(url);
				if(currentCountMap!=count_url.end())
				{
					// Add one to the number of visitors
					currentCountMap->second.first+=1;
					int n=currentCountMap->second.second;// url number in top

					//Check to see if the url is in the top and if it cout is superior of the minimum value of the top.
					if(n == -1 && currentCountMap->second.first > topMinValue)
					{
						n = topCurrentSize-1;
					}

					while( n>0 &&
					     (currentCountMap->second.first) > (top_url[n-1]->second.first))
					{
						--n;
					}
					if(n!=currentCountMap->second.second)
					{
						//perform a swap between element end element at new position
						top_url[n]->second.second=currentCountMap->second.second;
						if(currentCountMap->second.second != -1)
						{
							top_url[currentCountMap->second.second]=top_url[n];
						}

						currentCountMap->second.second=n;
						top_url[n]=currentCountMap;
						topMinValue = top_url[topCurrentSize-1]->second.first;
					}
				}
				else
				{
					//Adding visitors.
					currentCountMap = count_url.insert(pair<string,pair<int,int>>(url,pair<int,int>(1,-1))).first;
					if(topCurrentSize<top)
					{
						top_url[topCurrentSize] = currentCountMap;
						currentCountMap->second.second = topCurrentSize;
						topMinValue = currentCountMap->second.first;
						topCurrentSize++;
					}
				}
			}
			else if(graph_path.size()!=0 && count_url.count(url)==0)
			{// graph_path need at least a list of url
				count_url.insert(pair<string,pair<int,int>>(url,pair<int,int>(0,0)));
			}
			if(graph_path.size()!=0)
			{
				pair<string,string> association=pair<string,string>(currentLog -> GetHostReferer() + currentLog->GetReferer(),url);
				currentGraph=graphMap.find(association);
				if(currentGraph==graphMap.end())
				{
					// Adding the association
					graphMap.insert(pair<pair<string,string>,int>(association,1));
				}
				else
				{
					// incrementing number of people using association
					currentGraph->second+=1;
				}
			}
		}
		delete currentLog;
		currentLog = logS.GetNextLine();
	} // End of while loop
	logS.close();
	return 0;
}