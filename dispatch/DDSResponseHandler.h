// DDSResponseHandler.h

// 2004 Copyright University Corporation for Atmospheric Research

#ifndef I_DDSResponseHandler_h
#define I_DDSResponseHandler_h 1

#include "DODSResponseHandler.h"

class DDSResponseHandler : public DODSResponseHandler {
public:
				DDSResponseHandler( string name ) ;
    virtual			~DDSResponseHandler( void ) ;

    virtual void		parse( DODSTokenizer &tokenizer,
                                       DODSDataHandlerInterface &dhi ) ;
    virtual void		execute( DODSDataHandlerInterface &dhi ) ;
    virtual void		transmit( DODSTransmitter *transmitter,
                                          DODSDataHandlerInterface &dhi ) ;

    static DODSResponseHandler *DDSResponseBuilder( string handler_name ) ;
};

#endif // I_DDSResponseHandler_h

// $Log: DDSResponseHandler.h,v $
// Revision 1.3  2005/02/01 17:48:17  pwest
//
// integration of ESG into opendap
//
// Revision 1.2  2004/09/09 17:17:12  pwest
// Added copywrite information
//
// Revision 1.1  2004/06/30 20:16:24  pwest
// dods dispatch code, can be used for apache modules or simple cgi script
// invocation or opendap daemon. Built during cedar server development.
//