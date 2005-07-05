// ini_authenticator.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include <iostream>

using std::endl ;

#include "DODSInitList.h"
#include "DODSInitOrder.h"
#include "DODSMySQLAuthenticate.h"
#include "DODSTestAuthenticate.h"
#include "TheDODSAuthenticator.h"
#include "TheDODSLog.h"
#include "TheDODSKeys.h"

DODSAuthenticate *TheDODSAuthenticator = 0;

static bool
TheDODSAuthenticatorInit(int, char**) {
    string authType ;
    bool found = false ;

    authType = TheDODSKeys->get_key( "DODS.Authenticate", found ) ;
    if( found == false )
	authType = "none" ;

    if( authType == "mysql" || authType == "MYSQL" || authType == "MySQL" )
    {
	TheDODSAuthenticator = new DODSMySQLAuthenticate ;
    }
    else
    {
	authType = "none" ;
	TheDODSAuthenticator = new DODSTestAuthenticate ;
    }

    if( TheDODSLog->is_verbose() )
	(*TheDODSLog) << "Using Authentication: " << authType << endl;

    return true;
}

static bool
TheDODSAuthenticatorTerm(void) {
    if( TheDODSAuthenticator ) 
    {
	if( TheDODSLog->is_verbose() )
	    (*TheDODSLog) << "Cleaning up Authentication" << endl;
	delete TheDODSAuthenticator ;
    }
    TheDODSAuthenticator = 0 ;
    return true ;
}

FUNINITQUIT( TheDODSAuthenticatorInit, TheDODSAuthenticatorTerm, THEDODSAUTHENTICATOR_INIT ) ;

// $Log: ini_authenticator.cc,v $
// Revision 1.1  2004/12/15 17:39:03  pwest
// Added doxygen comments
//