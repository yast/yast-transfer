#
# Makefile.am for y2a_tftp/src
#

AM_CXXFLAGS = -Wall -DY2LOG=\"agent-tftp\" # -g # -pedantic # -W

plugin_LTLIBRARIES = libpy2ag_tftp.la
noinst_LTLIBRARIES = liby2ag_tftp.la

liby2ag_tftp_la_SOURCES =                    \
	TftpAgent.cc		\
	TftpAgent.h
liby2ag_tftp_la_LDFLAGS = -version-info 2:0
liby2ag_tftp_la_LIBADD = @AGENT_LIBADD@

libpy2ag_tftp_la_SOURCES =                           \
        $(liby2ag_tftp_la_SOURCES)                   \
        Y2CCTftpAgent.cc
libpy2ag_tftp_la_LDFLAGS = -version-info 2:0
libpy2ag_tftp_la_LIBADD = @AGENT_LIBADD@

INCLUDES = -I$(includedir)

