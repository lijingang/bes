// BESStatusReturn.h

// This file is part of bes, A C++ back-end server implementation framework
// for the OPeNDAP Data Access Protocol.

// Copyright (c) 2004,2005 University Corporation for Atmospheric Research
// Author: Patrick West <pwest@ucar.edu> and Jose Garcia <jgarcia@ucar.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact University Corporation for Atmospheric Research at
// 3080 Center Green Drive, Boulder, CO 80301
 
// (c) COPYRIGHT University Corporation for Atmostpheric Research 2004-2005
// Please read the full copyright statement in the file COPYRIGHT_UCAR.
//
// Authors:
//      pwest       Patrick West <pwest@ucar.edu>
//      jgarcia     Jose Garcia <jgarcia@ucar.edu>

#ifndef BESStatusReturn_h_
#define BESStatusReturn_h_ 1

#define BES_EXECUTED_OK 0
#define BES_TERMINATE_IMMEDIATE 1
#define BES_REQUEST_INCORRECT 2
#define BES_MEMORY_EXCEPTION 3
#define BES_DATABASE_FAILURE 4
#define BES_CONTAINER_PERSISTENCE_ERROR 5
#define BES_INITIALIZATION_FILE_PROBLEM 6
#define BES_LOG_FILE_PROBLEM 7
#define BES_DATA_HANDLER_FAILURE 8
#define BES_AGGREGATION_EXCEPTION 9
#define BES_FAILED_TO_EXECUTE_COMMIT_COMMAND 10
#define BES_DATA_HANDLER_PROBLEM 11

#endif // BESStatusReturn_h_
