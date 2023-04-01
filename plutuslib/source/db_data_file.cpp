//! \file db_data_file.cpp
//! \author Joe Turner <joe.turner@io-industrial.com>
//!
//! \copyright
//! Copyright (c) 2023 Joe Turner.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, version 3.
//!
//! This program is distributed in the hope that it will be useful, but
//! WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//! General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see <http://www.gnu.org/licenses/>.
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "db/db_data_file.h"

void DataFile::create(const char *filename, int record_length)
{
    // If the file exists, it won't anymore.
    remove(filename);

    struct DATA_FILE_HEADER hdr;
    hdr.init(record_length);

    int fd = ::open(filename, O_RDWR | O_CREAT );
    if (fd)
    {
        write(fd, &hdr, sizeof(hdr));
    }
    ::close(fd);
}

void DataFile::read_header()
{
    read(_fd, &_fhdr, sizeof(_fhdr));
}

void DataFile::write_header()
{
    write(_fd, &_fhdr, sizeof(_fhdr));
}

int DataFile::open(const char *filename)
{
    close();
    _fd = ::open(filename, O_RDWR);
    read_header();
    return _fd;
}

void DataFile::close()
{
    if (_fd > 0)
    {
        ::close(_fd);
        _fd = -1;
    }
}

RPTR DataFile::new_record(void *bf)
{
    RPTR record_number;
    struct DATA_FILE_RECORD_HEADER *phdr;

    if (_fhdr.recinfo.first_record)
    {
        // overwrite deleted record
        record_number = _fhdr.recinfo.first_record;
        phdr = (struct DATA_FILE_RECORD_HEADER *)(new char[_fhdr.record_length]);
        get_record(record_number, phdr);
        _fhdr.recinfo.first_record = phdr->next_record;
        delete[] phdr;
    }
    else
    {
        record_number = _fhdr.recinfo.next_record++;
    }

    put_record(record_number, bf);
    return record_number;
}

void DataFile::seek(RPTR record_number)
{
    lseek(_fd, _fhdr.locate_record(record_number), SEEK_SET);
}

int DataFile::get_record(RPTR record_number, void *bf)
{
    if (record_number >= _fhdr.recinfo.next_record)
    {
        return false;
    }
    
    seek(record_number);
    read(_fd, bf, _fhdr.record_length);
    return true;
}

int DataFile::put_record(RPTR record_number, void *bf)
{
    if (record_number > _fhdr.recinfo.next_record)
    {
        return false;
    }

    seek(record_number);
    write(_fd, bf, _fhdr.record_length);
    return true;
}

int DataFile::delete_record(RPTR record_number)
{
    char *bf;
    if (record_number > _fhdr.recinfo.next_record)
    {
        return false;
    }

    bf = new char[_fhdr.record_length];
    memset(bf, '\0', _fhdr.record_length);

    struct DATA_FILE_RECORD_HEADER *phdr = (struct DATA_FILE_RECORD_HEADER *)bf;
    phdr->next_record = _fhdr.recinfo.first_record;
    phdr->first_record = -1;
    _fhdr.recinfo.first_record = record_number;

    put_record(record_number, bf);
    delete[] bf;
    return true;
}