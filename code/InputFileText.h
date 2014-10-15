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

#ifndef QL_IO_INPUTFILETEXT_H
#define QL_IO_INPUTFILETEXT_H

#include <fstream>
#include <stdint.h>
#include <vector>
#include "InputFile.h"

namespace qlbase {

class InputFileText : public InputFile {

	public:

		InputFileText(const std::string &separator = std::string(" "));

		virtual ~InputFileText();

		virtual void open(const std::string &filename);
		virtual void close();
		virtual bool isOpened(){ return opened; }

		virtual int getHeadersNum(){ return 1; }

		void moveToHeader(int number) {}

		virtual int getNCols(){ return ncols; }
		virtual long getNRows(){ return nrows; }

		virtual int getColNum(const std::string& columnName)
		{
			throw IOException("getColNum not supported", 0);
		}

		virtual std::vector<uint8_t> readu8i(int ncol, long frow, long lrow);
		virtual std::vector<int16_t> read16i(int ncol, long frow, long lrow);
		virtual std::vector<uint16_t> read16u(int ncol, long frow, long lrow);
		virtual std::vector<int32_t> read32i(int ncol, long frow, long lrow);
		virtual std::vector<int64_t> read64i(int ncol, long frow, long lrow);
		virtual std::vector<float> read32f(int ncol, long frow, long lrow);
		virtual std::vector<double> read64f(int ncol, long frow, long lrow);

		virtual std::vector< std::vector<uint8_t> > readu8iv(int ncol, long frow, long lrow, int vsize)
		{
			throw IOException("readu8iv not supported", 0);
		}
		virtual std::vector< std::vector<int16_t> > read16iv(int ncol, long frow, long lrow, int vsize)
		{
			throw IOException("read16iv not supported", 0);
		}
		virtual std::vector< std::vector<int32_t> > read32iv(int ncol, long frow, long lrow, int vsize)
		{
			throw IOException("read32iv not supported", 0);
		}
		virtual std::vector< std::vector<int64_t> > read64iv(int ncol, long frow, long lrow, int vsize)
		{
			throw IOException("read64iv not supported", 0);
		}
		virtual std::vector< std::vector<float> > read32fv(int ncol, long frow, long lrow, int vsize)
		{
			throw IOException("readu32fv not supported", 0);
		}
		virtual std::vector< std::vector<double> > read64fv(int ncol, long frow, long lrow, int vsize)
		{
			throw IOException("readu64fv not supported", 0);
		}
		virtual std::vector< std::vector<char> > readString(int ncol, long frow, long lrow, int vsize)
		{
			throw IOException("readString not supported", 0);
		}

		virtual Image<uint8_t> readImageu8i(){ throw IOException("readImageu8i not supported", 0); }
		virtual Image<int16_t> readImage16i(){ throw IOException("readImageu8i not supported", 0); }
		virtual Image<int32_t> readImage32if(){ throw IOException("readImageu8i not supported", 0); }
		virtual Image<int64_t> readImage64i(){ throw IOException("readImageu8i not supported", 0); }
		virtual Image<float> readImage32f(){ throw IOException("readImageu8i not supported", 0); }
		virtual Image<double> readImage64f(){ throw IOException("readImageu8i not supported", 0); }

	private:
		bool opened;

		std::ifstream fileStream;
		std::string separator;

		void pointTo(int line);
		bool findField(std::string& line, int& first, int& last, int pos = 0);
		bool reopen();
		bool test(int ncol, long frow, long& lrow);

		int ncols;
		long nrows;

		template<class T>
		void readData(std::vector<T> &buff, int ncol, long frow, long lrow);

		void _printState();
};

}

#endif
