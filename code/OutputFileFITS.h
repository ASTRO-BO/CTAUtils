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

#ifndef QL_IO_OUTPUTFILEFITS_H
#define QL_IO_OUTPUTFILEFITS_H

#include <stdint.h>
#include <fitsio.h>
#include <string>
#include <stdexcept>
#include "OutputFile.h"

namespace qlbase {



class OutputFileFITS : public OutputFile {

public:

	OutputFileFITS();
	virtual ~OutputFileFITS();

	virtual void create(const std::string &filename);
	virtual void open(const std::string &filename);
	virtual void close();
	virtual bool isOpened() { return opened; }

	virtual void moveToHeader(int number);

	void writeKeyword(const std::string& name, const std::string& value, const std::string& comment);

	virtual void createTable(const std::string& name, const std::vector<field>& fields);
	virtual void writeu8i(int ncol, std::vector<uint8_t>& buff, long frow, long lrow);
	virtual void write16i(int ncol, std::vector<int16_t>& buff, long frow, long lrow);
	virtual void write32i(int ncol, std::vector<int32_t>& buff, long frow, long lrow);
	virtual void write64i(int ncol, std::vector<int64_t>& buff, long frow, long lrow);
	virtual void write32f(int ncol, std::vector<float>& buff, long frow, long lrow);
	virtual void write64f(int ncol, std::vector<double>& buff, long frow, long lrow);

	virtual void writeu8iv(int ncol, std::vector< std::vector<uint8_t> >& buff, long frow, long lrow);
	virtual void write16iv(int ncol, std::vector< std::vector<int16_t> >& buff, long frow, long lrow);
	virtual void write32iv(int ncol, std::vector< std::vector<int32_t> >& buff, long frow, long lrow);
	virtual void write64iv(int ncol, std::vector< std::vector<int64_t> >& buff, long frow, long lrow);
	virtual void write32fv(int ncol, std::vector< std::vector<float> >& buff, long frow, long lrow);
	virtual void write64fv(int ncol, std::vector< std::vector<double> >& buff, long frow, long lrow);
	virtual void writeString(int ncol, std::vector< std::vector<char> >& buff, long frow, long lrow);

private:

	bool opened;

	void throwException(const char *msg, int status);

	template<class T>
	void _write(int ncol, std::vector<T>& buff, int type, long frow, long lrow);

	template<class T>
	void _writev(int ncol, std::vector< std::vector<T> >& buff, int type, long frow, long lrow);

	const std::string _getFieldTypeString(fieldType type, int vsize);

protected:

	fitsfile *infptr;
};

}

#endif
