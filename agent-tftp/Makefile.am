#
# Makefile.am for y2a_tftp/src
#

AM_CXXFLAGS = -Wall -DY2LOG=\"agent-curl\" # -g # -pedantic # -W

plugin_LTLIBRARIES = libpy2ag_tftp.la
noinst_LTLIBRARIES = liby2ag_tftp.la

liby2ag_tftp_la_SOURCES =                    \
	TftpAgent.cc		\
	TftpAgent.h
liby2ag_tftp_la_LDFLAGS = -version-info 2:0

libpy2ag_tftp_la_SOURCES =                           \
        $(liby2ag_tftp_la_SOURCES)                   \
        Y2CCTftpAgent.cc         Y2CCTftpAgent.h  \
        Y2TftpAgentComponent.cc  Y2TftpAgentComponent.h
libpy2ag_tftp_la_LDFLAGS = -version-info 2:0

INCLUDES = -I$(includedir)

