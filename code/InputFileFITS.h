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

#ifndef QL_IO_INPUTFILEFITS_H
#define QL_IO_INPUTFILEFITS_H

#include <stdint.h>
#include <fitsio.h>
#include "InputFile.h"

namespace qlbase {

/// FITS file reader (cfitsio wrapping class).
/// All methods except isOpened() throw qlbase::IOException on errors.
class InputFileFITS : public InputFile {

	public:

		InputFileFITS();

		virtual ~InputFileFITS();

		/// Open a fits file.
		virtual void open(const std::string &filename);

		/// Close a fits file.
		virtual void close();
		virtual bool isOpened() { return opened; }

		/// Get the number of headers present in the fits.
		virtual int getHeadersNum();

		/// Point to a specific header.
		/// /param[in] number Number of the header (starting from 0).
		virtual void moveToHeader(int number);

		/// Get the number of columns.
		virtual int getNCols();

		/// Get the number of rows.
		virtual long getNRows();

		/// Get column number from the name.
		virtual int getColNum(const std::string& columnName);

		/// Read a column of bytes (fits type 1B).
		/// \param[in] ncol Column number (starting from 0).
		/// \param[in] frow First row (starting from 0).
		/// \param[in] lrow Last row (starting from 0).
		/// \return The vector of byte.
		virtual std::vector<uint8_t> readu8i(int ncol, long frow, long lrow);

		/// Read a column of 16 bit integers (fits type 1I).
		virtual std::vector<int16_t> read16i(int ncol, long frow, long lrow);

		/// Read a column of 16 bit unsigned integers (fits type 1U).
		virtual std::vector<uint16_t> read16u(int ncol, long frow, long lrow);

		/// Read a column of 32 bit integers (fits type 1J).
		virtual std::vector<int32_t> read32i(int ncol, long frow, long lrow);

		/// Read a column of 64 bit integers (fits type 1K).
		virtual std::vector<int64_t> read64i(int ncol, long frow, long lrow);

		/// Read a column of float (fits type 1E).
		virtual std::vector<float> read32f(int ncol, long frow, long lrow);

		/// Read a column of double (fits type 1D).
		virtual std::vector<double> read64f(int ncol, long frow, long lrow);

		/// Return the number of keywords for the current header.
		virtual int getKeywordNum();

		/// Get a fits keyword through index (starting from 0).
		virtual std::string getKeyword(int index);

		/// Read a column of vector of bytes (fits type for es. 20B).
		/// \param[in] ncol Column number (starting from 0).
		/// \param[in] frow First row (starting from 0).
		/// \param[in] lrow Last row (starting from 0).
		/// \param[in] vsize Size of the the vector (this represent the size of a cell).
		/// \return The column of vector of bytes (vector of vector of bytes).
		virtual std::vector< std::vector<uint8_t> > readu8iv(int ncol, long frow, long lrow, int vsize);

		/// Read a column of vector of 16 bit integers (fits type for es. 20I).
		virtual std::vector< std::vector<int16_t> > read16iv(int ncol, long frow, long lrow, int vsize);

		/// Read a column of vector of 32 bit integers (fits type for es. 20J).
		virtual std::vector< std::vector<int32_t> > read32iv(int ncol, long frow, long lrow, int vsize);

		/// Read a column of vector of 64 bit integers (fits type for es. 20K).
		virtual std::vector< std::vector<int64_t> > read64iv(int ncol, long frow, long lrow, int vsize);

		/// Read a column of vector of float (fits type for es. 20E).
		virtual std::vector< std::vector<float> > read32fv(int ncol, long frow, long lrow, int vsize);

		/// Read a column of vector of double (fits type for es. 20D).
		virtual std::vector< std::vector<double> > read64fv(int ncol, long frow, long lrow, int vsize);

		/// Read a column of strings (fits type for es. 20A).
		virtual std::vector< std::vector<char> > readString(int ncol, long frow, long lrow, int vsize);

		/// Read a multidimensional image of bytes.
		/// \return The Image structure holding the image data, dimensions and its sizes.
		virtual Image<uint8_t> readImageu8i();

		/// Read a multidimensional image of 16bit integers.
		virtual Image<int16_t> readImage16i();

		/// Read a multidimensional image of 32bit integers.
		virtual Image<int32_t> readImage32if();

		/// Read a multidimensional image of 64bit integers.
		virtual Image<int64_t> readImage64i();

		/// Read a multidimensional image of 32bit float.
		virtual Image<float> readImage32f();

		/// Read a multidimensional image of 64bit double.
		virtual Image<double> readImage64f();

		/// Return the internal file descriptor
		virtual const fitsfile* GetFilePointer()
		{
			return infptr;
		}

	private:

	bool opened;

	void throwException(const char *msg, int status);

	template<class T>
	void _read(int ncol, std::vector<T>& buff, int type, long frow, long lrow);

	template<class T>
	void _readv(int ncol, std::vector< std::vector<T> >& buff, int type, long frow, long lrow, int vsize);

	template<class T>
	void _readImage(Image<T>& buff, int type);

	protected:

	fitsfile *infptr;
};

}

#endif
