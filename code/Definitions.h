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

#ifndef CTAUTILS_DEFINITION_H
#define CTAUTILS_DEFINITION_H

#include <iostream>

namespace CTAUtils
{

#define DEBUG(msg) {std::cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": " << msg << std::endl;}
#define ERR(msg) {std::cerr << msg << std::endl;}

}

#endif
