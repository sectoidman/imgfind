#
#  CMakeLists.cmake - cross-platform makefile
#
#  Copyright (C) 2011 Joseph Woodruff
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2, or (at your option)
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
project (imgfind)
link_directories ( /usr/lib )
include_directories ( /usr/include )
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} . )

add_subdirectory (kernel)
add_subdirectory (docs)

set ( SOURCES imgfind.cc )

set ( CMAKE_CXX_FLAGS "-Wall -g" )

find_package ( pHash REQUIRED )

add_executable( imgfind ${SOURCES} )
target_link_libraries (imgfind pHash)
