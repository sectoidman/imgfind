/* 
   worker.h - class description for multi-threading worker classes

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

#ifndef WORKER_H
#define	WORKER_H

#include <pHash.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

class dct_imagehash_w {
    
public:
    dct_imagehash_w(const std::vector<string>& input_imglist, 
                    const std::vector<DP*>& input_dplist);
    
    void start(uint num_threads = boost::thread::hardware_concurrency());
    
    void join();
    
    std::vector<DP*> return_dplist();
    
    virtual ~dct_imagehash_w();
    
private:
    void process();
    
    uint                  imglist_sz;
    uint                  idx;
    std::vector<string>   imglist;
    std::vector<DP*>      dplist;
    boost::thread_group   threads;
    boost::mutex          idx_lock;
    boost::mutex          dplist_lock;

};

#endif	/* WORKER_H */

