#
#  CMakeLists.cmake - cross-platform makefile
#
#  Copyright (C) 2011 Joseph Woodruff
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3, or (at your option)
#  any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
#

#  Possible build configurations:
#  
#  debug:  
#           Generates un-optimized (-O0) code with debugging symbols.
# 
#  release:
#           Enables reasonable compiler optimizations and 
#           strips the generated binary of symbols to reduce size.
#
#           This is the default option.
#            
#           reldbg enables optimizations and includes debugging
#           symbols.
#
#  hiperf:
#           Enables most/all available compiler optimizations, 
#           regardless of safety or standards compliance.
#
#           hiperfd enables these optimizations and includes debugging
#           symbols (though they may not be useful for much except 
#           profiling).


cmake_minimum_required (VERSION 2.6)
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project (imgfind)
set ( imgfind_VERSION_MAJOR 0 )
set ( imgfind_VERSION_MINOR 0 )
set ( imgfind_VERSION_PATCH 1 )

set ( SOURCES imgfind.cc kernel/search.cc )

set ( CMAKE_CXX_FLAGS "-Wall" )
set ( CMAKE_CXX_FLAGS_DEBUG "-O0 -g" )
set ( CMAKE_CXX_FLAGS_RELDBG "-O2 -g" )
set ( CMAKE_CXX_FLAGS_RELEASE "-O2 -s" )
set ( CMAKE_CXX_FLAGS_HIPERF "-O3 -s -ffast-math" )
set ( CMAKE_CXX_FLAGS_HIPERFD "-O3 -g -ffast-math" )
set ( CMAKE_CXX_FLAGS_DEFAULT ${CMAKE_CXX_FLAGS_RELEASE} )

find_package ( pHash REQUIRED )
find_package ( Boost REQUIRED )

add_executable( imgfind ${SOURCES} )
target_link_libraries (imgfind pHash boost_system boost_filesystem boost_regex)

