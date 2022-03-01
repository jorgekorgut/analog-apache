/*************************************************************************
                           Log  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Log> (fichier Log.h) ----------------
#if ! defined ( LOG_H )
#define LOG_H
//--------------------------------------------------- Interfaces utilisées
#include<ctime>
#include<string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Log>
// La classe Log sert à structurer les données du flux d’entrée du fichier Log Apache. 
// Bien entendu, les données n’étaient pas si nombreuses pour la réalisation de cette classe. 
// Ainsi, Celle-ci doit être vue comme une fondation pour l’évolution du code dans l’avenir.
//------------------------------------------------------------------------

class Log
{
//----------------------------------------------------------------- PUBLIC

	public:
//----------------------------------------------------- Méthodes publiques
    	const string & GetReferer() const;
	
		const string & GetHostReferer() const;
    	
		const string & GetHostTarget() const;

		const string & GetTarget() const;

    	const string GetTargetExt() const;

    	const int & GetHour() const;

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
		Log (const string & ip,
		const string & userLogname,
		const string & userAuthenticated,
		const struct tm & date,
		const string & http_command,
		const string & hostTarget,
		const string & target,
		const string & cookie,
		const string & version,
		const int & http_code,
		const int & buffer_size,
		const string & protocol,
		const string & host,
		const string & referer,
		const string & user_agent);

   		virtual ~Log ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	
//----------------------------------------------------- Attributs protégés
		string ip;

		string userLogname;

		string userAuthenticated;

		struct tm date;

		string cookie;

		string http_command;

		string hostTarget;

		string target;

		string version;

		int http_code;

		int buffer_size;

		string protocol;

		string host;

		string referer;

		string user_agent;
};

//-------------------------------- Autres définitions dépendantes de <Log>

#endif // LOG_H

