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

#ifndef QL_IO_OUTPUTFILE_H
#define QL_IO_OUTPUTFILE_H

#include <string>
#include <stdint.h>
#include <vector>
#include "File.h"

namespace qlbase {

enum fieldType
{
	UNSIGNED_INT8,
	INT16,
	INT32,
	INT64,
	FLOAT,
	DOUBLE,
	STRING
};

struct field
{
	std::string name;
	fieldType type;
	int vsize;
	std::string unit;
};

/// The interface for reading from a generic file divided into chunks.
/// It specialize File adding functions for reading tables and images.
class OutputFile : public File {

public:

	OutputFile() {}

	virtual ~OutputFile() {}

	virtual void createTable(const std::string& name, const std::vector<field>& fields) = 0;
	virtual void writeu8i(int ncol, std::vector<uint8_t>& buff, long frow, long lrow) = 0;
	virtual void write16i(int ncol, std::vector<int16_t>& buff, long frow, long lrow) = 0;
	virtual void write32i(int ncol, std::vector<int32_t>& buff, long frow, long lrow) = 0;
	virtual void write64i(int ncol, std::vector<int64_t>& buff, long frow, long lrow) = 0;
	virtual void write32f(int ncol, std::vector<float>& buff, long frow, long lrow) = 0;
	virtual void write64f(int ncol, std::vector<double>& buff, long frow, long lrow) = 0;

	virtual void writeu8iv(int ncol, std::vector< std::vector<uint8_t> >& buff, long frow, long lrow) = 0;
	virtual void write16iv(int ncol, std::vector< std::vector<int16_t> >& buff, long frow, long lrow) = 0;
	virtual void write32iv(int ncol, std::vector< std::vector<int32_t> >& buff, long frow, long lrow) = 0;
	virtual void write64iv(int ncol, std::vector< std::vector<int64_t> >& buff, long frow, long lrow) = 0;
	virtual void write32fv(int ncol, std::vector< std::vector<float> >& buff, long frow, long lrow) = 0;
	virtual void write64fv(int ncol, std::vector< std::vector<double> >& buff, long frow, long lrow) = 0;
	virtual void writeString(int ncol, std::vector< std::vector<char> >& buff, long frow, long lrow) = 0;
};


}

#endif
