#
# Makefile.am for .../agent-pam/doc/autodocs
#

htmldir = $(docdir)/autodocs

html_DATA = index.html $(wildcard *.html *.png) doxygen.css @RPMNAME@.tag
CLEANFILES = $(html_DATA) doxygen.log doxygen.conf installdox

index.html: $(srcdir)/../../agent-curl/*.h $(srcdir)/../../agent-tftp/*.h
	${YDOXYGEN} PROJECT_NAME=@RPMNAME@ INPUT=../..
