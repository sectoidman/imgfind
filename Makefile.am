bin_PROGRAMS=imgfind
imgfind_SOURCES=imgfind.cc imgfind.1 xmalloc.c system.h aclocal.m4 getopt.c getopt1.c getopt.h

#  uncomment the following if imgfind requires the math library
#imgfind_LDADD=-lm

EXTRA_DIST=imgfind.lsm.in #NAME.texinfo imgfind.spec.in

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list
#TESTS=chk

#  build and install the .info pages
info_TEXINFOS = imgfind.texinfo
imgfind_TEXINFOS = gpl.texinfo

#  install the man pages
man_MANS=imgfind.1
