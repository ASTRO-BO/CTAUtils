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

#ifndef QL_IO_INPUTFILE_H
#define QL_IO_INPUTFILE_H

#include <string>
#include <stdint.h>
#include <vector>
#include "File.h"

namespace qlbase {

template<class T>
struct Image {
	std::vector<T> data;
	int32_t dim;
	std::vector<int64_t> sizes;
};

/// An abstraction for reading from a generic file divided into blocks.
/// Each block could be a table or an image.
class InputFile : public File {

	public:

		InputFile() {}

		virtual ~InputFile() {}

		/// Get the number of headers present in the file.
		/// \return The number of headers.
		virtual int getHeadersNum() = 0;

		/// Point to a specific block (alias header). A block could be related to a table or an image.
		/// /param[in] number Number of the block (starting from 0).
		virtual void moveToHeader(int number) = 0;

		/***** Table reading functions *****/
		/// Get the number of columns.
		virtual int getNCols() = 0;

		/// Get the number of rows.
		virtual long getNRows() = 0;

		/// Get column number from the name.
		virtual int getColNum(const std::string& columnName) = 0;

		/// Read a column of byte.
		/// \param[in] ncol Column number (starting from 0).
		/// \param[in] frow First row (starting from 0).
		/// \param[in] lrow Last row (starting from 0).
		/// \return The vector of bytes.
		virtual std::vector<uint8_t> readu8i(int ncol, long frow, long lrow) = 0;

		/// Read a column of 16 bit integers.
		virtual std::vector<int16_t> read16i(int ncol, long frow, long lrow) = 0;

		/// Read a column of 16 bit unsigned integers.
		virtual std::vector<uint16_t> read16u(int ncol, long frow, long lrow) = 0;

		/// Read a column of 32 bit integers.
		virtual std::vector<int32_t> read32i(int ncol, long frow, long lrow) = 0;

		/// Read a column of 64 bit integers.
		virtual std::vector<int64_t> read64i(int ncol, long frow, long lrow) = 0;

		/// Read a column of float.
		virtual std::vector<float> read32f(int ncol, long frow, long lrow) = 0;

		/// Read a column of double.
		virtual std::vector<double> read64f(int ncol, long frow, long lrow) = 0;

		/// Read a column of vector of bytes.
		virtual std::vector< std::vector<uint8_t> > readu8iv(int ncol, long frow, long lrow, int vsize) = 0;

		/// Read a column of vector of 16 bit integers.
		virtual std::vector< std::vector<int16_t> > read16iv(int ncol, long frow, long lrow, int vsize) = 0;

		/// Read a column of vector of 32 bit integers.
		virtual std::vector< std::vector<int32_t> > read32iv(int ncol, long frow, long lrow, int vsize) = 0;

		/// Read a column of vector of 64 bit integers.
		virtual std::vector< std::vector<int64_t> > read64iv(int ncol, long frow, long lrow, int vsize) = 0;

		/// Read a column of vector of float.
		virtual std::vector< std::vector<float> > read32fv(int ncol, long frow, long lrow, int vsize) = 0;

		/// Read a column of vector of double.
		virtual std::vector< std::vector<double> > read64fv(int ncol, long frow, long lrow, int vsize) = 0;

		/// Read a column of strings.
		virtual std::vector< std::vector<char> > readString(int ncol, long frow, long lrow, int vsize) = 0;

		/***** Image reading functions *****/
		/// Read a multidimensional image of bytes.
		virtual Image<uint8_t> readImageu8i() = 0;

		/// Read a multidimensional image of 16bit integers.
		virtual Image<int16_t> readImage16i() = 0;

		/// Read a multidimensional image of 32bit integers.
		virtual Image<int32_t> readImage32if() = 0;

		/// Read a multidimensional image of 64bit integers.
		virtual Image<int64_t> readImage64i() = 0;

		/// Read a multidimensional image of float.
		virtual Image<float> readImage32f() = 0;

		/// Read a multidimensional image of double.
		virtual Image<double> readImage64f() = 0;
};

}

#endif
