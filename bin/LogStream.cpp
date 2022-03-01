/*************************************************************************
                           LogStream  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <LogStream> (fichier LogStream.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "LogStream.h"

//------------------------------------------------------------- Constantes
const string LOCAL_HOST_DOMAIN = "intranet-if.insa-lyon.fr";
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

const Log * LogStream::GetNextLine()
{
	char currentInfo[MAX_CHARACTERS_INFO];
	
	if(!getline(currentInfo, MAX_CHARACTERS_INFO, ' '))
	{
		return nullptr;
	}
	
	string ip(currentInfo);

	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	string userLogname(currentInfo);

	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	string userAuthenticated(currentInfo);
	
	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	struct tm date;
	strptime(currentInfo,"[%d/%b/%Y:%T ",&date);

	getline(currentInfo, MAX_CHARACTERS_INFO, '"');
	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	string http_command(currentInfo);
	
	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	string http_target(currentInfo);
	size_t cookiePos = http_target.find(";");
	string cookie(http_target.substr(cookiePos+1));
	http_target=http_target.substr(0,cookiePos);


	getline(currentInfo, MAX_CHARACTERS_INFO, '"');
	string http_version(currentInfo);
	
	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	int http_code = -1 ;
	if(currentInfo[0] != '-')
	{
		http_code = atoi(currentInfo);
	}

	getline(currentInfo, MAX_CHARACTERS_INFO, ' ');
	int http_buffer_size = -1;
	if(currentInfo[0] != '-')
	{
		http_buffer_size = atoi(currentInfo);
	}

	getline(currentInfo, MAX_CHARACTERS_INFO, '"');

	getline(currentInfo, MAX_CHARACTERS_INFO, '"');
	string buffer(currentInfo);
	string protocol;
	string host;
	string hostTarget;
	string referer;
	size_t bufferLength = buffer.length();
	if(bufferLength != 1)
	{
		size_t protocolPos = buffer.find(":");
		protocol = buffer.substr(0,protocolPos);
		size_t hostPos = buffer.find("/",protocolPos+3);
		
		if(hostPos>bufferLength)
		{
			hostPos = bufferLength;
			referer = "/";
		}
		else
		{
			host = buffer.substr(protocolPos+3,(hostPos)-(protocolPos+3));
			referer = buffer.substr(hostPos,(bufferLength)-hostPos);
		}
	}
	else
	{	
		protocol = string("");
		host = string("");
		referer = string("");
	}
	//Find host
	hostTarget = LOCAL_HOST_DOMAIN;

	getline(currentInfo, MAX_CHARACTERS_INFO, '"');
	getline(currentInfo, MAX_CHARACTERS_INFO, '"');
	string user_agent(currentInfo);
	getline(currentInfo, MAX_CHARACTERS_INFO, '\n');
	
	return new Log(ip, userLogname, userAuthenticated, date, http_command, hostTarget, http_target, cookie, http_version, http_code, http_buffer_size, protocol, host, referer, user_agent);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

LogStream::LogStream (const char* filename, ios_base::openmode mode):ifstream(filename, mode)
// Algorithme :
//
{
#ifdef MAP
    cerr << "Appel au constructeur de <LogStream>" << endl;
#endif
} //----- Fin de LogStream

LogStream::LogStream():ifstream()
{
#ifdef MAP
    cerr << "Appel au constructeur de <LogStream>" << endl;
#endif
} //----- Fin de LogStream

LogStream::~LogStream ( )
// Algorithme :
//
{
#ifdef MAP
    cerr << "Appel au destructeur de <LogStream>" << endl;
#endif
} //----- Fin de ~LogStream

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
