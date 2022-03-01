/*************************************************************************
                           Interface  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Interface> (fichier Interface.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream> 
//------------------------------------------------------ Include personnel
#include "Interface.h"

//------------------------------------------------------------- Constantes
#define DEFAULT_TOP 10

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Interface::Start (int argc, char * argv[])
{
	top=DEFAULT_TOP;
	time=set<int>();
	graph=vector<string>();
	path=vector<string>();
	exclude=false;

	bool is_top_set=false;
	char option=' ';
	for(int i=1;i<argc;i++)
	{
		switch (option)
		{
			case ' ':
				if(strlen(argv[i])==0)
				{
					cerr<<"warning:argument "<<i<<" vide"<<endl;
					break;
				}
				if(argv[i][0]!='-')
				{
					path.push_back(argv[i]);
					break;
				}
				if(strlen(argv[i])<2)
				{
					cerr<<"argument invalide \""<<argv[i]<<"\"["<<i<<"]"<<endl;
					show_help(true);
					return;
				}
				if(strlen(argv[i])!=2)
				{
					cerr << "option invalide \""<<argv[i]+1<<"\"["<<i<<"]"<<endl;
					show_help(true);
					return;
				}
				switch(argv[i][1])
				{
					case 'b':case 'g':case 't':
						option=argv[i][1];
						break;
					case 'h':
						show_help();
						return;
					case 'e':
						option=' ';
						exclude=true;
						break;
					default:
						cerr << "option inconnus \""<<argv[i]+1<<"\"["<<i<<"]"<<endl;
						show_help(true);
						return;
				}
			break;
			case 'b':
				if(is_top_set)
				{
					cerr << "deux top différent on été demandé, il faut choisir" << endl;
					show_help(true);
					return;
				}
				is_top_set=true;
				if(
					(strlen(argv[i])==2 && argv[i][0]=='-' && !isdigit(argv[i][1])) || // it's an other option
					(argv[i][0]!='-' && !isdigit(argv[i][0]))) // it's a log path
				{
					top = DEFAULT_TOP;
					i--; // the loop will analyse this part again
				}
				else	// it's suposed to be a number
				{ 
					for( char * c = argv[i]; strlen(c)!=0; c++ ) // loop all chars
					{
						if(!isdigit(*c) && !(c==argv[i] || *c=='-'))
						{
							cerr << "\""<<argv[i]<<"\"["<<i<<"] n'est pas un nombre" <<endl;
							show_help(true);
							return;
						}
					}
					top = atoi(argv[i]);
				}
				if(top<0)
				{
					cerr << "ce nombre doit être positif"<<endl;
					show_help(true);
					return;
				}
				option=' ';
			break;
			case 'g':
				if(!is_top_set)
				{
					top=-1;
				}
				graph.push_back(string(argv[i]));
				option=' ';
			break;
			case 't':
				if(!is_top_set)
				{
					top=10;
				}
				for( char * c = argv[i]; strlen(c)!=0; c++ ) // loop all chars
				{
					if(!isdigit(*c) && !(c==argv[i] || *c=='-'))
					{
						cerr << "\""<<argv[i]<<"\"["<<i<<"] n'est pas un nombre" <<endl;
						show_help(true);
						return;
					}
				}
				int timeElem=atoi(argv[i]);
				if(timeElem < 0 )
				{
					cerr << "heure doit être positif ou null"<<endl;
					show_help(true);
					return;
				}
				if(timeElem > 23 )
				{
					cerr << "il n'y a que 24 heures dans une journé, pas "<< timeElem +1<<endl;
					show_help(true);
					return;
				}
				time.insert(timeElem);
				option=' ';
			break;
		}
	}
	if(path.size()==0)
	{
		cerr << "il n'y a pas de fichier de log" << endl;
		show_help(true);
		return;
	}

	LogManager lm = LogManager(path,time,top,exclude,graph);
	if(graph.size()!=0)
	{
			constructGraphFile(lm);
	}
	printTop(lm);
}

void Interface::constructGraphFile(LogManager & lm) const
// Algorithme: La construction du graph se fait en premier par la récupération des structures de données 
// représentant les connexions entre les liens et la totalité d'accès de chaque lien. Ensuite il génère 
// une valeur unique entière pour chaque url visitée. Après ceci, avec cet identifiant, l’algorithme
// cherche à reconstruire les liens.
{
	vector<ofstream> graph_files;
	for(size_t i=0; i< graph.size();i++ )
	{
		graph_files.push_back(ofstream());
		graph_files[i].open(graph[i].c_str());
		if(!graph_files[i].is_open())
		{
			cerr << "le fichier \"" << graph[i] << "\"  n'est pas ouvrable en lecture" << endl;
			//closing all opened files
			for (size_t j=0;j<i;j++)
			{
				graph_files[j].close();
			}
			return;
		}
	}
	const unordered_map<pair<string,string>,int> tmp_graph=lm.GetGraph();
	unordered_map<string,pair<int,int>> tmp_urls=lm.GetCount_url();
	int topSize = lm.GetTopSize();

	ostringstream graphBuffer;
	graphBuffer << "digraph {" << endl;

	if(topSize == 0)
	{
		unordered_map<string,pair<int,int>>::iterator itNodes;
		int i=0;
		for( itNodes=tmp_urls.begin();itNodes!=tmp_urls.end(); ++itNodes,++i)
		{
			graphBuffer<<"node"<<i<<" [label=\"" << itNodes->first << "\"];"<<endl;
			itNodes->second.first=i;
		}

		unordered_map<pair<string,string>,int>::const_iterator itTransition;
		for(itTransition=tmp_graph.begin();itTransition!=tmp_graph.end();++itTransition)
		{
			graphBuffer << "node" << tmp_urls[itTransition->first.first].first << " -> node" << tmp_urls[itTransition->first.second].first;
			graphBuffer << " [label=\""<<itTransition->second<<"\"];"<<endl;
		}
	}
	else
	{
		unordered_map<string,pair<int,int>>::iterator itNodes;
		int i=0;
		for( itNodes=tmp_urls.begin();itNodes!=tmp_urls.end(); ++itNodes++,++i)
		{
			graphBuffer<<"node"<<i<<" [label=\"" << itNodes->first << "\"];"<<endl;
			itNodes->second.first=i;
		}
	}

	graphBuffer << "}";

	for ( size_t i=0; i<graph_files.size(); i++ )
	{
		graph_files[i]<< graphBuffer.str();
		graph_files[i].close();
	}
}

void Interface::printTop(const LogManager & lm) const
{
	int topCurrentSize = lm.GetTopSize();
	const unordered_map<string,pair<int,int>>::iterator* top_url = lm.GetTop_url();

	for(int i=0;i<topCurrentSize;i++)
	{
		printf("%3i:",i+1);
		cout<<top_url[i]->first<<" ("<<top_url[i]->second.first<<")"<<endl;
	}
}

void Interface::show_help( bool error ) const
{
	ostream & os=(error?cerr:cout);
	os << "usage : anaLog [OPTION] file" <<endl;
	os << "analyse de log apache"<<endl;
	os << "  -b <number=10>    top des <number> site(s) les plus visité" << endl;
	os << "  -g <nomfichier>   fichier de sortie au format graphviz (.dot)"<<endl;
	os << "  -e                exclu tout les image, css, js (.jpg,.gif,.png,.css,.js,.ico,.bmp)"<<endl;
	os << "  -t <heure>        seulement pendant l'heure <heure>"<<endl;
	os << "  -h                montre cette aide et ferme"<<endl;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Interface::Interface ( )
{
#ifdef MAP
    cerr << "Appel au constructeur de <Interface>" << endl;
#endif
} //----- Fin de Interface

Interface::~Interface ( )
{
#ifdef MAP
    cerr << "Appel au destructeur de <Interface>" << endl;
#endif
} //----- Fin de ~Interface


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
