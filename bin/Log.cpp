/*************************************************************************
                           Log  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Log> (fichier Log.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Log.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

const string & Log::GetReferer() const
{
	return referer;
}

const string & Log::GetHostTarget() const
{
	return hostTarget;
}

const string & Log::GetTarget() const
{
	return target;
}

const string Log::GetTargetExt() const
{
	string ext;
	size_t lPos = target.find("?");
	if(lPos == string::npos)
	{
		lPos = target.length();
	}
	else
	{
		--lPos;
	}
	size_t fPos = target.rfind("/",lPos);
	size_t dotPos = target.rfind(".",lPos);
	if(dotPos == string::npos || dotPos < fPos)
	{
		return string("");
	}
	return target.substr(dotPos+1,lPos-dotPos);
}

const string & Log::GetHostReferer() const
{
	return host;	
}

const int & Log::GetHour() const
{
	return date.tm_hour;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Log::Log (const string & ip,
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
	const string & user_agent)
{
#ifdef MAP
    	cerr << "Appel au constructeur de <Log>" << endl;
#endif
	this->ip = ip;
    	this->userLogname = userLogname;
	this->userAuthenticated = userAuthenticated;
	this->date = date;
	this->cookie = cookie;
	this->http_command = http_command;
	this->hostTarget = hostTarget;
	this->target = target;
	this->version = version;
	this->http_code = http_code;
	this->buffer_size = buffer_size;
	this->protocol = protocol;
	this->host = host;
	this->referer = referer;
	this->user_agent = user_agent;
}

Log::~Log ( )
{
#ifdef MAP
    cerr << "Appel au destructeur de <Log>" << endl;
#endif
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées