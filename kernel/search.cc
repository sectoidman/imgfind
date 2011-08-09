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
#include <boost/regex.hpp>
#include "search.h"

namespace fs = boost::filesystem;

/* 
  cr_imglist()
 
 Searches a given directory and generates a list of image files
 by checking file extensions.
 
 TODO: Add more robust detection code using libmagic or portable equivalent.

*/

int cr_imglist(const char* path) 
{
    fs::path search_dir(path);
    boost::regex search_criteria("\.(gif|jpg|jpeg|png|bmp)$", 
                                 boost::regex::perl|boost::regex::icase);
    
    if (fs::is_directory(search_dir)) {
        fs::recursive_directory_iterator itr(search_dir);
        fs::recursive_directory_iterator end;
        
        for (/* itr */; itr != end; ++itr) {
            
            if (boost::regex_search(itr->leaf(), search_criteria)) {
                printf("%s\n", itr->string().c_str());
            }
        }
        
        return 0;      
    } else if (fs::exists(search_dir)) {
        //check if file is valid image file and return path to it
        
        return 0;
    } else {   
        return -1;
    }
            
}

/* 
  hash_imglist()
 
 Given a list of images, generates hashes of them.
 
*/

int hash_imglist(const char* list) 
{
    return 0;
}