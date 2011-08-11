/* 
   search.h - image search routines

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

#ifndef SEARCH_H
#define	SEARCH_H 

#include <vector>
#include <string>
#include <map>
#include <pHash.h>

/*
  cr_imglist()
 
 Generates list of image files located in a given path if
 the path given is a directory or single image file.
 
 Parameters:
              path -
 
 Returns a vector of string objects containing file paths.
*/

std::vector<std::string> cr_imglist(const char* path);


/* 
  hash_imglist()
 
 Given a list of images, generates hashes of them.
 
 Parameters:
              list -
                
              htype -
 
 Returns
 
 NOTE: DPs are managed with ph_malloc_dp() and ph_free_dp(); however,
       these do not free the (dynamically-allocated) hash and id members
       of that struct. Further, they use the malloc() and free() functions
       from C, which are not compatible with C++'s new and free keywords;
       keep that in mind.
 
*/

std::vector<DP*> hash_imglist(std::vector<std::string> list, int htype);


/*
 hash_image()
 
 Given a single image, generate a hash of it.
 
*/

DP* hash_image(const char* path, int htype);


/*
 find_similar()
 
 Given a list of data points (hashes + file names), generate a list of files
 which have a similarity to the criteria hash within the range 
 (dependent on hash function used) specified.
 
 Parameters:
              criteria - pointer to a 'datapoint' (struct defined in pHash.h)
                         that everything will be compared against.
 
              list     - a vector containing datapoints that will be checked
                         against the criteria given.
              
              range    - a float which gives the threshold similarity for the
                         different hashes:
                         
               discrete cosine transform - hamming distance (default 26)
               radial / radish           - PCC              (default 0.85) (0-1)
               Marr                      - hamming distance (default 0.40)
 
 Returns a vector containing the filenames which were within the specified
 range.
 
*/

std::vector<string> find_similar(DP* criteria, 
                                 std::vector<DP*> list, 
                                 float range);

#endif	/* SEARCH_H */

