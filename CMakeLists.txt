
cmake_minimum_required (VERSION 2.6)
project (imgfind)

add_subdirectory (kernel)
add_subdirectory (docs)

set ( SOURCES imgfind.cc )

add_executable ( imgfind ${SOURCES} )
