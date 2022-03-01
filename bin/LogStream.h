/*************************************************************************
                           LogStream  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <LogStream> (fichier LogStream.h) ----------------
#if ! defined ( LOGSTREAM_H )
#define LOGSTREAM_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <fstream>
#include "Log.h"
//------------------------------------------------------------- Constantes
const int MAX_CHARACTERS_INFO = 10000;
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogStream>
// Cette classe est responsable pour la transformation d’un flux de données apache dans un objet Log.
//------------------------------------------------------------------------

class LogStream : public std::ifstream
{
//----------------------------------------------------------------- PUBLIC
    public:
//----------------------------------------------------- Méthodes publiques
    
        const Log * GetNextLine();
        // Mode d'emploi :
        // Cette méthode lit une ligne dans le fichier Log Apache et la transforme dans un objet avec des attributs.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    	LogStream (const char* filename, ios_base::openmode mode = ios_base::in );

	    LogStream();
    	
	    virtual ~LogStream ( );
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <LogStream>

#endif // LOGSTREAM_H