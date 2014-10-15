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

#include <iostream>
#include <sstream>
#include <cstring>

#include "Definitions.h"
#include "OutputFileFITS.h"

namespace qlbase {


#define ERRMSGSIZ 81

OutputFileFITS::OutputFileFITS() : opened(false), infptr(0) {
}

OutputFileFITS::~OutputFileFITS() {
}

void OutputFileFITS::throwException(const char *msg, int status) {
	std::string errMsg(msg);

	if(status != 0)
	{
		char errDesc[ERRMSGSIZ];
		fits_read_errmsg(errDesc);
		errMsg += errDesc;
	}
	else
		errMsg += "Reading from a closed file.";

	throw IOException(msg, status);
}

void OutputFileFITS::create(const std::string &filename) {
	int status = 0;

	fits_create_file(&infptr, filename.c_str(), &status);

	if (status)
		throwException("Error in OutputFileFITS::create() ", status);

	opened = true;
}

void OutputFileFITS::open(const std::string &filename) {
	File::open(filename);
	int status = 0;

	fits_open_table(&infptr, filename.c_str(), READWRITE, &status);

	if (status)
		throwException("Error in OutputFileFITS::open() ", status);

	opened = true;
}

void OutputFileFITS::close() {
	int status = 0;
	fits_close_file(infptr, &status);

	if (status)
		throwException("Error in OutputFileFITS::close() ", status);

	opened = false;
}

void OutputFileFITS::moveToHeader(int number) {
	int status = 0;

	if(!isOpened())
		throwException("Error in OutputFileFITS::moveToHeader() ", status);

	fits_movabs_hdu(infptr, number+1, 0, &status);

	if (status)
		throwException("Error in OutputFileFITS::moveToHeader() ", status);
}

void OutputFileFITS::writeKeyword(const std::string& name, const std::string& value, const std::string& comment) {
	int status = 0;
	char card[FLEN_CARD];

	if(!isOpened())
		throwException("Error in OutputFileFITS::writeKeyword() ", status);

	// check if this is a protected keyword that must not be changed.
	fits_read_card(infptr, name.c_str(), card, &status);
	if(status != KEY_NO_EXIST) {
		if (*card && fits_get_keyclass(card) == TYP_STRUC_KEY)
			throwException("Error in OutputFileFITS::writeKeyword() protected ", status);
	}
	if (status != KEY_NO_EXIST && status != 0)
		throwException("Error in OutputFileFITS::writeKeyword() ", status);

	status = 0;
	std::string key = name + " = " + value + " / " + comment;
	int keytype;
	fits_parse_template((char*)key.c_str(), card, &keytype, &status);
	if (status)
		throwException("Error in OutputFileFITS::writeKeyword() ", status);

	fits_update_card(infptr, name.c_str(), card, &status);
	if (status)
		throwException("Error in OutputFileFITS::writeKeyword() ", status);
}

void OutputFileFITS::createTable(const std::string& name, const std::vector<field>& fields) {
	int status = 0;

	if(!isOpened())
		throwException("Error in OutputFileFITS::createTable() ", status);

	unsigned int nfields = fields.size();

	char** ttypes = new char*[nfields*sizeof(char*)];
	char** tform = new char*[nfields*sizeof(char*)];
	char** tunit = new char*[nfields*sizeof(char*)];

	for(unsigned int i=0; i<nfields; i++)
	{
		ttypes[i] = new char[10];
		std::string type = fields[i].name.c_str();
		std::memcpy(ttypes[i], type.c_str(), 10);

		tform[i] = new char[10];
		std::string form(_getFieldTypeString(fields[i].type, fields[i].vsize));
		std::memcpy(tform[i], form.c_str(), 10);

		tunit[i] = new char[10];
		std::string unit = fields[i].unit.c_str();
		std::memcpy(tunit[i], unit.c_str(), 10);
	}

	fits_create_tbl(infptr, BINARY_TBL, 0, nfields, ttypes, tform, tunit, name.c_str(), &status);

	for(unsigned int i=0; i<nfields; i++)
	{
		delete ttypes[i];
		delete tform[i];
		delete tunit[i];
	}

	delete ttypes;
	delete tform;
	delete tunit;

	if (status)
		throwException("Error in OutputFileFITS::createTable() ", status);

	for(unsigned int i=0; i<nfields; i++)
	{
		if(fields[i].type == STRING)
		{
			long tdim[] = {fields[i].vsize, 1};
			fits_write_tdim(infptr, i+1, 2, tdim, &status);
		}
	}
	if (status)
		throwException("Error in OutputFileFITS::createTable() ", status);
}


void OutputFileFITS::writeu8i(int ncol, std::vector<uint8_t>& buff, long frow, long lrow)
{
	_write(ncol, buff, TBYTE, frow, lrow);
}

void OutputFileFITS::write16i(int ncol, std::vector<int16_t>& buff, long frow, long lrow)
{
	_write(ncol, buff, TSHORT, frow, lrow);
}

void OutputFileFITS::write32i(int ncol, std::vector<int32_t>& buff, long frow, long lrow)
{
	_write(ncol, buff, TINT, frow, lrow);
}

void OutputFileFITS::write64i(int ncol, std::vector<int64_t>& buff, long frow, long lrow)
{
	_write(ncol, buff, TLONG, frow, lrow);
}

void OutputFileFITS::write32f(int ncol, std::vector<float>& buff, long frow, long lrow)
{
	_write(ncol, buff, TFLOAT, frow, lrow);
}

void OutputFileFITS::write64f(int ncol, std::vector<double>& buff, long frow, long lrow)
{
	_write(ncol, buff, TDOUBLE, frow, lrow);
}

void OutputFileFITS::writeu8iv(int ncol, std::vector< std::vector<uint8_t> >& buff, long frow, long lrow)
{
	_writev(ncol, buff, TBYTE, frow, lrow);
}

void OutputFileFITS::write16iv(int ncol, std::vector< std::vector<int16_t> >& buff, long frow, long lrow)
{
	_writev(ncol, buff, TSHORT, frow, lrow);
}

void OutputFileFITS::write32iv(int ncol, std::vector< std::vector<int32_t> >& buff, long frow, long lrow)
{
	_writev(ncol, buff, TINT, frow, lrow);
}

void OutputFileFITS::write64iv(int ncol, std::vector< std::vector<int64_t> >& buff, long frow, long lrow)
{
	_writev(ncol, buff, TLONG, frow, lrow);
}

void OutputFileFITS::write32fv(int ncol, std::vector< std::vector<float> >& buff, long frow, long lrow)
{
	_writev(ncol, buff, TFLOAT, frow, lrow);
}

void OutputFileFITS::write64fv(int ncol, std::vector< std::vector<double> >& buff, long frow, long lrow)
{
	_writev(ncol, buff, TDOUBLE, frow, lrow);
}

void OutputFileFITS::writeString(int ncol, std::vector< std::vector<char> >& buff, long frow, long lrow)
{
	int status = 0;
	if(!isOpened())
		throwException("Error in OutputFileFITS::writeString() ", status);

	long nelem = lrow - frow + 1;
	unsigned int size = buff[0].size();
	char** buffptrs = new char*[nelem];
	for(unsigned int row=frow; row<lrow+1; row++)
	{
		buffptrs[row] = new char[buff[0].size()];
		memcpy(buffptrs[row], &buff[row][0], buff[0].size());
	}

	fits_write_col(infptr, TSTRING, ncol+1, frow+1, 1, nelem, buffptrs, &status);

	for(unsigned int row=frow; row<lrow+1; row++)
		delete buffptrs[row];
	delete[] buffptrs;

	if(status)
		throwException("Error in OutputFileFITS::writeString() ", status);
}

template<class T>
void OutputFileFITS::_write(int ncol, std::vector<T>& buff, int type, long frow, long lrow) {
	int status = 0;
	if(!isOpened())
		throwException("Error in OutputFileFITS::_write() ", status);

	long nelem = lrow - frow + 1;

	std::vector<T> buffptr = buff;
	fits_write_col(infptr, type, ncol+1, frow+1, 1, nelem, &buffptr[0], &status);

	if(status)
		throwException("Error in OutputFileFITS::_write() ", status);
}

template<class T>
void OutputFileFITS::_writev(int ncol, std::vector< std::vector<T> >& buff, int type, long frow, long lrow) {
	int status = 0;
	if(!isOpened())
		throwException("Error in OutputFileFITS::_writev() ", status);

	long nelem = lrow - frow + 1;
	unsigned int size = buff[0].size();
	T* buffptr = new T[nelem*size];
	for(unsigned int row=frow; row<lrow+1; row++)
	{
		for(unsigned int i=0; i<size; i++)
		{
			buffptr[row*size + i] = buff[row][i];
		}
	}

	fits_write_col(infptr, type, ncol+1, frow+1, 1, nelem*size, buffptr, &status);

	delete[] buffptr;

	if(status)
		throwException("Error in OutputFileFITS::_writev() ", status);
}

const std::string OutputFileFITS::_getFieldTypeString(fieldType type, int vsize) {
	std::ostringstream ist;
	ist << vsize;
	switch(type)
	{
		case UNSIGNED_INT8:
			ist << "B";
			break;
		case INT16:
			ist << "I";
			break;
		case INT32:
			ist << "J";
			break;
		case INT64:
			ist << "K";
			break;
		case FLOAT:
			ist << "E";
			break;
		case DOUBLE:
			ist << "D";
			break;
		case STRING:
			ist << "A";
			break;
		default:
			throw IOException("Error in OutputFileFITS::_getFieldTypeString() ", 0);
	}
	return ist.str();
}

}
