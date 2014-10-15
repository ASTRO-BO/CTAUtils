/***************************************************************************
    begin                : Nov 29 2001
    copyright            : (C) 2001 Andrea Bulgarelli
                               2013 Andrea Zoli
    email                : bulgarelli@iasfbo.inaf.it
                           zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/

#ifndef QL_IO_FILE_H
#define QL_IO_FILE_H

#include <string>
#include <stdexcept>

namespace qlbase {

class IOException : public std::runtime_error {

    int _errorCode;

	public:

	IOException(const std::string &msg, int errorCode = 0) : std::runtime_error(msg), _errorCode(errorCode) {}

	int getErrorCode() {
		return _errorCode;
	}
};

/// The interface for a FITS-like file divided into different headers.
class File {

public:

	File() : _filename("") {}
	virtual ~File() {}

	virtual void open(const std::string &filename) {
		_filename = filename;
	}
	virtual void close() = 0;
	virtual bool isOpened() = 0;

	virtual std::string getFileName() { return _filename; };

	virtual void moveToHeader(int number) = 0;

protected:

	std::string _filename;
};

}

#endif
