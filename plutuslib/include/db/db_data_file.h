//! \file db_data_file.h
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
//! along with this program. If not, see <http://www.gnu.org/licenses/>.d
#ifndef _DB_DATA_FILE_H_
#define _DB_DATA_FILE_H_
#include "db/db_file_header.h"
#include "db/db_record_pointer.h"

//! \brief Database data file
//!
//! Each database file has a corresponding disk file.  This file
//! consists of a header record, followed by a series of fixed-length
//! data records.
class DataFile
{

public:

    //! \brief Create a new data file
    //!
    //! This function is used to create a data file and is called
    //! from the data initialization function(s), when the files
    //! for the database are initialized.  The filename pointer points
    //! to the file name of the data file.  The record length integer
    //! is the record length. 
    //!
    //! If the data file already exists, it will be deleted and a new
    //! empty file will be created.
    //!
    //! \param filename file name to be created
    //! \param record_length length of the record in bytes
    //!
    void create(const char *filename, int record_length);

    //! \brief Open data file
    //!
    //! This function opens an existing data file, one that was 
    //! previously created by \see create.  It will return a 
    //! logical file handle that the class uses for subsequent 
    //! calls to data file functions.  If the file does not 
    //! exist, -1 is returned.
    //!
    //! \returns 
    //! This function returns -1 on error, or the file handle.
    int open(const char *filename);

    //! \brief Close data file
    //!
    //! This function closes the data file.
    void close();

    //! \brief Write a new record to the datafile
    //!
    //! This function adds a record to the data file, writing it to the next
    //! available record space in the file.  It will write the record
    //! either at the end of the file or, if records have been deleted from
    //! the file, into a record position that was formerly occupied by a since-
    //! deleted record.
    //!
    //! \param bf               pointer to the buffer from which the record 
    //!                         be read.
    //!
    //! \returns
    //! This function returns the logical record of the new record.
    RPTR new_record(void *bf);

    //! \brief Retrieve a record
    //!
    //! This function retrieves a record that was previously stored in the 
    //! data file.  
    //!
    //! \param record_number    logical record number, where the record is 
    //!                         known to be stored.
    //!
    //! \param bf               pointer to the buffer into which the record 
    //!                         be read.
    int get_record(RPTR record_number, void *bf);

    //! This function rewrites a record to the file and is used when the record
    //! has been changed.
    //!
    //! \param record_number    logical record number, where the record is 
    //!                         known to be stored.
    //!
    //! \param bf               pointer to the buffer from which the record 
    //!                         be written.
    int put_record(RPTR record_number, void *bf);

    //! This function deletes the record located at the logical record
    //! position.  The record space is placed into a linked list for the
    //! file so that a latter record addition can reuse the space.
    int delete_record(RPTR record_number);

protected:

    void seek(RPTR record_number);
    void read_header();
    void write_header();

private:

    //! file descriptor
    int _fd;
    struct DATA_FILE_HEADER _fhdr;
};

#endif
