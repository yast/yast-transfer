#
# Makefile.am for devtools/devtools/skeletons/agent/doc/autodocs
#

htmldir = $(docdir)/autodocs

html_DATA = index.html $(wildcard *.html)
CLEANFILES = $(html_DATA)

index.html: $(srcdir)/../../agent-curl/*.h $(srcdir)/../../agent-tftp/*.h $(srcdir)/../../module/*.ycp
	cd $(srcdir)/../../agent-curl && @ybindir@/ydoc @RPMNAME@ *.h
	mv -f $(srcdir)/../../agent-curl/*.html .
	cd $(srcdir)/../../agent-tftp && @ybindir@/ydoc @RPMNAME@ *.h
	mv -f $(srcdir)/../../agent-tftp/*.html .
	cd $(srcdir)/../../module && @ybindir@/ydoc @RPMNAME@ *.ycp
	mv -f $(srcdir)/../../module/*.html .
