/***************************************************************************
    begin                : Jul 18 2013
    copyright            : (C) 2013 Andrea Zoli
    email                : zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef QL_IO_DEFINITION_H
#define QL_IO_DEFINITION_H

#include<iostream>

namespace qlbase
{

#define QL_DEBUG 1

#ifdef QL_DEBUG

#define DEBUG(msg) {std::cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": " << msg << std::endl;}
#else
#define DEBUG(msg)
#endif

#define ERR(msg) {std::cerr << msg << std::endl;}

enum FileError {
    kFileNoError = 0,
    kFileNoRead,
    kEndFile,
    kErrorMoveHeader,
    kFileStopped,
    kFileDataError,
    kReadFileDisabled,
    kFileErrorRowsTerminated = 307
};

}

#endif
