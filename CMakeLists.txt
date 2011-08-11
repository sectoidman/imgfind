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
#

cmake_minimum_required (VERSION 2.6)
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project (imgfind)
set ( imgfind_VERSION_MAJOR 0 )
set ( imgfind_VERSION_MINOR 0 )
set ( imgfind_VERSION_PATCH 1 )

set ( SOURCES imgfind.cc kernel/search.cc )

set ( CMAKE_CXX_FLAGS "-Wall -O2" )

find_package ( pHash REQUIRED )
find_package ( Boost REQUIRED )

add_executable( imgfind ${SOURCES} )
target_link_libraries (imgfind pHash boost_system boost_filesystem boost_regex)

