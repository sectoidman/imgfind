/* 
   search.cc - description

   Copyright (C) 2011 Joseph Woodruff

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 */

#include <pHash.h>
#include <boost/filesystem.hpp>
#include "search.h"

namespace fs = boost::filesystem;

/* 
  cr_imglist() - Searches a given directory and generates a list of image files 
                 Returns -1 on non-existent path.
                 Returns 0 otherwise.
*/

int cr_imglist(const char* path) 
{
    fs::path searchdir;
    
    if (fs::is_directory(searchdir)) {
        //search the directory and any subdirectory for image files
        return 0;      
    } else if (fs::exists(searchdir)) {     
        //check if file is valid image file and return path to it
        return 0;
    } else {   
        return -1;
    }
            
}

/* 
  hash_imglist() - Given a list of images, generates hashes of them
*/

int hash_imglist(const char* list) 
{
    return 0;
}