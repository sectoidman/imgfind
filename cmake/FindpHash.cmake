#
#  FindpHash.cmake - Library search script to find the pHash lib for cmake
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


find_path ( pHash_INCLUDE_DIRS pHash.h "$ENV{NAMER_ROOT}" )

find_library ( pHash_LIBRARIES libpHash "$ENV{NAMER_ROOT}" )

set ( pHash_FOUND TRUE )
 
if ( NOT pHash_INCLUDE_DIRS )
  set ( pHash_FOUND FALSE )
endif ( NOT pHash_INCLUDE_DIRS )

if ( NOT pHash_LIBRARIES )
  set ( pHash_FOUND FALSE )
endif ( NOT pHash_LIBRARIES )

