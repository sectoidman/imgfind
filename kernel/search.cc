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

using namespace std;
namespace fs = boost::filesystem;

/* 
  cr_imglist()
 
 Searches a given directory recursively and generates a list of image files
 by checking file extensions.
 
 TODO: Add more robust detection code using libmagic or portable equivalent.

*/

vector<string> cr_imglist(const char* path) 
{
    vector<string> imglist;
    fs::path search_dir(path);
    boost::regex search_criteria("\.(gif|jpg|jpeg|png|bmp)$", 
                                 boost::regex::perl|boost::regex::icase);
    
    if (fs::is_directory(search_dir)) {
        fs::recursive_directory_iterator itr(search_dir);
        fs::recursive_directory_iterator end;
        
        for (/* itr */; itr != end; ++itr) {
            
            if (boost::regex_search(itr->leaf(), search_criteria)) {
                imglist.push_back(itr->string());
            }
        }
        
        return imglist;      
    } else if (fs::exists(search_dir)) {
        
        if (boost::regex_search(search_dir.leaf(), search_criteria))
            imglist.push_back(search_dir.string());
        
        return imglist;
    } else {   
        return imglist;
    }
}

/* 
  hash_imglist()
 
 Given a list of images, generates hashes of them.
 
 TODO: Implement hash-type checking.
 
*/

vector<DP*> hash_imglist(vector<string> imglist, int htype) 
{
    uint imglist_sz = imglist.size();
    ulong64* hash;
    DP* datapoint;
    vector<DP*> dplist;
    
    for (uint i = 0; i < imglist_sz; i++) {
        
        hash = new ulong64;
        
        if (ph_dct_imagehash(imglist[i].c_str(), *hash) == -1) {
            
            delete hash;
            continue;
            
        } else {
            
            datapoint = ph_malloc_datapoint(UINT64ARRAY);
            datapoint->hash_length = 1;
            datapoint->hash = (void*) hash;
            datapoint->id = new char [imglist[i].length() + 1];
            strcpy(datapoint->id, imglist[i].c_str());
            
            dplist.push_back(datapoint);
        }
    }
    
    return dplist;
        
}


/*
 hash_image()
 
 Given a single image generate a hash of it
 
 TODO: Implement hash-type checking.
 
*/

DP* hash_image(const char* path, int htype)
{
    fs::path imgpath(path);
    boost::regex search_criteria("\.(gif|jpg|jpeg|png|bmp)$", 
                                 boost::regex::perl|boost::regex::icase);
    ulong64* hash;
    DP* datapoint;
    
    if (fs::exists(imgpath) && 
        boost::regex_search(imgpath.leaf(), search_criteria)) {
        
        hash = new ulong64;  
        if (ph_dct_imagehash(path, *hash) == -1) {
            delete hash;
            return NULL;
        }
        
        datapoint = ph_malloc_datapoint(UINT64ARRAY);
        datapoint->hash_length = 1;
        datapoint->hash = (void*) hash;
        datapoint->id = new char [imgpath.string().length() + 1];
        strcpy(datapoint->id, imgpath.string().c_str());
        
        return datapoint;
        
    } else {
        return NULL;
    }
    
}


/*
 find_similar()
 
 Given a list of data points (hashes + file names), generate a list of files
 which have a similarity to the criteria hash within the range 
 (dependent on hash function used) specified.
 
 TODO: Implement hash-type checking and hashes other than dct.
 
*/

vector<string> find_similar(DP* criteria, 
                            vector<DP*> hashlist, 
                            float range)
{
    uint hashlist_sz = hashlist.size();
    int match_distance = (int) range;
    string match_path;
    vector<string> similar_list;
    
    for (uint i = 0; i < hashlist_sz; i++) {
        if (ph_hamming_distance(*(ulong64*) hashlist[i]->hash, 
                                *(ulong64*) criteria->hash) 
            < match_distance) {
            
            match_path.assign(hashlist[i]->id);
            similar_list.push_back(match_path);
        }
    }
    
    return similar_list;
}