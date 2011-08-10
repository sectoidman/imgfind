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
 
 Returns a vector of string objects containing file paths.
*/

std::vector<std::string> cr_imglist(const char* path);

/* 
  hash_imglist()
 
 Given a list of images, generates hashes of them.
 
*/

std::map<std::string, DP> hash_imglist(std::vector<std::string> list);

#endif	/* SEARCH_H */

