/* 
   dct_imagehash_w.cc - discrete cosine transform hash thread/worker class
                        implementation.

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

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "workers.h"

using namespace std;

dct_imagehash_w::dct_imagehash_w(const vector<string>& input_imglist, 
                                 const vector<DP*>& input_dplist)
{
    imglist    = input_imglist;
    dplist     = input_dplist;
    imglist_sz = imglist.size();
    idx        = 0;
}


void dct_imagehash_w::process() 
{
    ulong64 hash;
    uint    i;
    DP*     datapoint;
    
    idx_lock.lock();
    i = idx;
    idx++;
    idx_lock.unlock();
      
    while (i < imglist_sz) {
        
        if (ph_dct_imagehash(imglist[i].c_str(), hash) == -1) {
            
            //couldn't hash this file, so go on to the next one
            idx_lock.lock();
            i = idx;
            idx++;
            idx_lock.unlock();
            
            continue;
        } else {
           
            datapoint                   = new DP;
            datapoint->hash_length      = 1;
            datapoint->hash_type        = UINT64ARRAY;
            datapoint->hash             = (void*) new ulong64;
            *(ulong64*) datapoint->hash = hash;
            datapoint->id               = new char [imglist[i].length() + 1];
            
            strcpy(datapoint->id, imglist[i].c_str());
            
            dplist_lock.lock();
            dplist.push_back(datapoint);
            dplist_lock.unlock();
              
            idx_lock.lock();
            i = idx;
            idx++;
            idx_lock.unlock();
        }
    }
    return;
}

void dct_imagehash_w::start(uint num_threads)
{
    if (num_threads == 0)
        threads.create_thread(boost::bind(&dct_imagehash_w::process, this));
    
    for (uint i = 0; i < num_threads; i++)
        threads.create_thread(boost::bind(&dct_imagehash_w::process, this));
}

void dct_imagehash_w::join()
{
    threads.join_all();
}

vector<DP*> dct_imagehash_w::return_dplist()
{
    threads.join_all();
    return dplist;
}

dct_imagehash_w::~dct_imagehash_w() 
{
    
}

