// DefineResponseHandler.cc

// 2004 Copyright University Corporation for Atmospheric Research

#include "DefineResponseHandler.h"
#include "DODSTextInfo.h"
#include "DODSParserException.h"
#include "DODSTokenizer.h"
#include "ThePersistenceList.h"
#include "DODSDefine.h"
#include "TheDefineList.h"

DefineResponseHandler::DefineResponseHandler( string name )
    : DODSResponseHandler( name )
{
}

DefineResponseHandler::~DefineResponseHandler( )
{
}

void
DefineResponseHandler::parse( DODSTokenizer &tokenizer,
                           DODSDataHandlerInterface &dhi )
{
    /*
     * define name as sym1,sym2,...,symn with ... aggregate by ...
     * 
     * no return as
     */
    dhi.action = _response_name ;

    bool with_aggregation = false ;

    _def_name = tokenizer.get_next_token() ;

    string my_token = tokenizer.get_next_token() ;
    if( my_token != "as" )
    {
	tokenizer.parse_error( my_token + " not expected, expecting \"as\"" ) ;
    }
    else
    {
	my_token = tokenizer.get_next_token() ;
	bool expecting_comma = false ;
	bool with_proyection = false ;
	if( my_token == ";" )
	    tokenizer.parse_error( my_token + " not expected, expecting list of symbolic names\n" ) ;
	while( ( my_token != "with" ) && ( my_token!=";" ) )
	{
	    if( ( my_token == "," ) && ( !expecting_comma ) )
		tokenizer.parse_error( my_token + " not expected\n" ) ;
	    else if( ( my_token == "," ) && ( expecting_comma ) )
		expecting_comma = false ;
	    else if( ( my_token != "," ) && ( expecting_comma ) )
		tokenizer.parse_error( my_token + " not expected\n" ) ;
	    else
	    {
		DODSContainer d( my_token ) ;
		ThePersistenceList->look_for( d ) ;
		dhi.containers.push_back( d ) ;
		expecting_comma = true ;
	    }
	    my_token = tokenizer.get_next_token() ;
	    if( my_token == "with" )
		with_proyection = true ;
	}
	if( !expecting_comma )
	    tokenizer.parse_error( my_token + " not expected\n" ) ;
	else
	    expecting_comma = false ;
	if( with_proyection )
	{
	    my_token = tokenizer.get_next_token() ;
	    if( my_token == ";" )
		tokenizer.parse_error( my_token + " not expected\n" ) ;
	    else
	    {
		int rat = 0 ;
		bool need_constraint = false ;
		int where_in_list = 0 ;
		bool found = false ;
		unsigned int my_type = 0 ;
		while( my_token != "aggregate" && my_token != ";" )
		{
		    if( ( my_token == "," ) && ( !expecting_comma ) )
			tokenizer.parse_error( my_token + " not expected\n" ) ;
		    else if( ( my_token == "," ) && ( expecting_comma ) )
			expecting_comma = false ;
		    else if( ( my_token != "," ) && ( expecting_comma ) )
			tokenizer.parse_error( my_token + " not expected\n" ) ;
		    else
		    {
			rat++ ;
			switch( rat )
			{
			    case 1:
			    {
				my_type = 0 ;
				string ds = tokenizer.parse_container_name( my_token, my_type ) ;
				found = false ;
				dhi.first_container() ;
				where_in_list = 0 ;
				while( dhi.container && !found )
				{ 
				    if( ds == dhi.container->get_symbolic_name() )
				    {
					found = true ;
				    }
				    dhi.next_container() ;
				    where_in_list++ ;
				}
				if( !found )
				    tokenizer.parse_error( "Container " + ds + " is in the proyection but is not in the selection." ) ;
				need_constraint = true ;
				break ;
			    }
			    case 2:
			    {
				expecting_comma = true ;
				rat = 0 ;
				need_constraint = false ;
				dhi.first_container() ;
				for( int w = 0; w < where_in_list-1 ; w++ )
				{
				    dhi.next_container() ;
				}
				if( my_type == 1 )
				{
				    dhi.container->set_constraint( tokenizer.remove_quotes( my_token ) ) ;
				}
				else if( my_type == 2 )
				{
				    dhi.container->set_attributes( tokenizer.remove_quotes( my_token ) ) ;
				}
				else
				{
				    tokenizer.parse_error( "Unknown property type for container" + dhi.container->get_symbolic_name() ) ;
				}
				break;
			    }
			}
		    }
		    my_token = tokenizer.get_next_token() ;
		    if( my_token == "aggregate" )
			with_aggregation = true ;
		}
		if( need_constraint )
		    tokenizer.parse_error( "; not expected" ) ;
	    }
	}
	if( with_aggregation == true )
	{
	    my_token = tokenizer.get_next_token() ;
	    if( my_token != "by" )
		tokenizer.parse_error( my_token + " not expected" ) ;
	    else
	    {
		my_token = tokenizer.get_next_token() ;
		if( my_token == ";" )
		    tokenizer.parse_error( my_token + " not expected" ) ;
		else
		{
		    dhi.aggregation_command = tokenizer.remove_quotes( my_token ) ;
		}
	    }
	    my_token = tokenizer.get_next_token() ;
	}
	if( my_token != ";" )
	{
	    tokenizer.parse_error( my_token + " not expected" ) ;
	}
    }
}

void
DefineResponseHandler::execute( DODSDataHandlerInterface &dhi )
{
    DODSTextInfo *info = new DODSTextInfo( dhi.transmit_protocol == "HTTP" ) ;
    _response = info ;
    
    string def_type = "added" ;
    bool deleted = TheDefineList->remove_def( _def_name ) ;
    if( deleted == true )
    {
	def_type = "replaced" ;
    }

    DODSDefine *dd = new DODSDefine ;
    dhi.first_container() ;
    while( dhi.container )
    {
	dd->containers.push_back( *dhi.container ) ;
	dhi.next_container() ;
    }
    dd->aggregation_command = dhi.aggregation_command ;
    dhi.aggregation_command = "" ;

    TheDefineList->add_def( _def_name, dd ) ;
    string ret = (string)"Successfully " + def_type + " definition "
		 + _def_name + "\n" ;
    info->add_data( ret ) ;
}

void
DefineResponseHandler::transmit( DODSTransmitter *transmitter,
                                  DODSDataHandlerInterface &dhi )
{
    if( _response )
    {
	DODSTextInfo *ti = dynamic_cast<DODSTextInfo *>(_response) ;
	transmitter->send_text( *ti, dhi ) ;
    }
}

DODSResponseHandler *
DefineResponseHandler::DefineResponseBuilder( string handler_name )
{
    return new DefineResponseHandler( handler_name ) ;
}

// $Log: DefineResponseHandler.cc,v $
// Revision 1.5  2005/03/26 00:33:33  pwest
// fixed aggregation server invoke problems. Other commands use the aggregation command but no aggregation is needed, so set aggregation to empty string when done
//
// Revision 1.4  2005/03/17 19:25:29  pwest
// string parameters changed to const references. remove_def now deletes the definition and returns true if removed or false otherwise. Added method remove_defs to remove all definitions
//
// Revision 1.3  2005/03/15 19:58:35  pwest
// using DODSTokenizer to get first and next tokens
//
// Revision 1.2  2005/02/02 00:03:13  pwest
// ability to replace containers and definitions
//
// Revision 1.1  2005/02/01 17:48:17  pwest
//
// integration of ESG into opendap
//