// BESServerHandler.h

// This file is part of bes, A C++ back-end server implementation framework
// for the OPeNDAP Data Access Protocol.

// Copyright (c) 2011 OPeNDAP
// Author: James Gallagher <jgallagher@opendap.org> Based on code by Partick
// West and Jose Garcia.
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
 
// (c) COPYRIGHT OPeNDAP
// Please read the full copyright statement in the file COPYING.

#ifndef DaemonCommandHandler_h
#define DaemonCommandHandler_h 1

#include <string>

using std::string ;

#include "ServerHandler.h"
#include "XMLWriter.h"

#define BESLISTENER_STOPPED 0
#define BESLISTENER_RUNNING 4	// 1,2 are abnormal term, restart is 3
#define BESLISTENER_RESTART SERVER_EXIT_RESTART

class Connection ;

class DaemonCommandHandler: public ServerHandler {
private:
    string d_config_file_name;
    string d_config_dir;
    string d_include_dir;

    void execute_command(const string &command, XMLWriter &writer);

public:
    DaemonCommandHandler(const string &config);
    virtual ~DaemonCommandHandler() { }

    string get_config_file() { return d_config_file_name; }
    void set_config_file(const string &config) { d_config_file_name = config; }

    virtual void handle(Connection *c);

    virtual void dump(ostream &strm) const;
};

#endif // DaemonCommandHandler_h

