#
# Makefile.am for devtools/devtools/skeletons/agent/src
#
AM_CXXFLAGS = -DY2LOG=\"agent-curl\"

plugin_LTLIBRARIES = libpy2ag_curl.la
noinst_LTLIBRARIES = liby2ag_curl.la

liby2ag_curl_la_SOURCES =                   \
	CurlAgent.cc		\
	CurlAgent.h			\
	curlcpp.cc          \
	curlcpp.h           \
	curloptcpp.cc       \
	curlstoragecpp.cc   \
	curlutilscpp.cc		
liby2ag_curl_la_LDFLAGS = -version-info 2:0

libpy2ag_curl_la_SOURCES =                           \
        $(liby2ag_curl_la_SOURCES)                   \
		Y2CCCurlAgent.cc	\
		Y2CCCurlAgent.h		\
		Y2CurlAgentComponent.cc	\
		Y2CurlAgentComponent.h	
libpy2ag_curl_la_LDFLAGS = -version-info 2:0
libpy2ag_curl_la_LIBADD =  $(CURL_LIBS)

INCLUDES = -I$(includedir) $(CURL_CFLAGS)

