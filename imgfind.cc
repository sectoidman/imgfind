/* 
   imgfind - Searches for similar image files.

   Copyright (C) 2011 Joseph Woodruff

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  

*/

#include "kernel/search.h"
#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

int main (int argc, char **argv)
{
  /* do the work */
    DP* search_criteria;
    vector<DP*> dplist;
    vector<string> temp_path_list;
    vector<string> full_path_list;
    vector<string> matches;
    
    //try to open directories / or if none given try to open cwd. also usage.
    if ( argc < 2 ) {
        cout << "Usage: imgfind [dir...] search_criteria" << endl 
             << endl
             << "dir is a directory/list of directories to be searched"
             << "; defaults to current directory." << endl
             << "search_criteria is a path to a valid image file "
             << "(jpeg gif png bmp); no default, is required" << endl << endl;
    } else if ( argc < 3 ) {
        
        try { 
            full_path_list = cr_imglist(fs::current_path().string().c_str());
        } catch (fs::filesystem_error ex) {         
            cout << "imgfind: " << ex.what() << endl;
        }
        
    } else {
        
       for (int i = 1; i < argc-1; i++) {
           try {    
               temp_path_list = cr_imglist(argv[i]);
           } catch (fs::filesystem_error ex) {
               cout << "imgfind: " << ex.what() << endl;
               continue;
           }
           
           if (temp_path_list.empty()) {
               cout << "imgfind: No image files found in " << argv[i] << endl;
           } else {
           //non-obvious append operation.
           full_path_list.insert(full_path_list.end(),
                                 temp_path_list.begin(),
                                 temp_path_list.end());
           }
        }
    }
    
    if (full_path_list.empty()) {
        return 0;
    }
    
    
    // try to open and hash the criteria image
    try { 
        search_criteria = hash_image(argv[argc-1], 0); 
    } catch (fs::filesystem_error ex) {
        cout << "imgfind: " << ex.what() << endl;
        return -1;
    }
    
    if (search_criteria == NULL) {
        cout << "imgfind: Criteria invalid or not accessible." << endl;
        return 0;
    }
    
    
    dplist = hash_imglist(full_path_list, 0);
    
    if (dplist.empty()) {
        //no datapoints? something must be wrong.
        return -1;
    }
  
    // test criteria against hashlist; print path to matching files if found
    matches = find_similar(search_criteria, dplist, 20);
    
    if (matches.empty()) {
        //no matches
        return 0;
    }
    
    for (uint i = 0; i < matches.size(); i++)
        cout << matches[i] << std::endl;
    
    return 0;
}

