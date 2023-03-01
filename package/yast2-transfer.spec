#
# spec file for package yast2-transfer
#
# Copyright (c) 2013 SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#


Name:           yast2-transfer
Version:        3.1.4
Release:        0

BuildRoot:      %{_tmppath}/%{name}-%{version}-build
Source0:        %{name}-%{version}.tar.bz2

Group:	        System/YaST
License:        GPL-2.0
BuildRequires:	curl-devel gcc-c++ perl-XML-Writer update-desktop-files yast2 doxygen yast2-core-devel libtool
BuildRequires:  yast2-devtools >= 3.1.10
%if 0%{?suse_version} < 1220
BuildRequires:  libxcrypt-devel
%endif
Requires:       yast2-ruby-bindings >= 1.0.0

Summary:	YaST2 - Agent for Various Transfer Protocols
Provides:	yast2-agent-curl yast2-agent-tftp yast2-agent-curl-devel yast2-agent-tftp-devel
Obsoletes:	yast2-agent-curl yast2-agent-tftp yast2-agent-curl-devel yast2-agent-tftp-devel
Obsoletes:	yast2-transfer-devel-doc
Requires:	curl 

%description
A YaST2 Agent for various Transfer Protocols: FTP, HTTP, and TFTP.

%prep
%setup -n %{name}-%{version}

%build
%yast_build

%install
%yast_install

rm -f $RPM_BUILD_ROOT/%{yast_plugindir}/libpy2ag_curl.la
rm -f $RPM_BUILD_ROOT/%{yast_plugindir}/libpy2ag_tftp.la


%files
%defattr(-,root,root)
%{yast_scrconfdir}/*.scr
%{yast_plugindir}/libpy2ag_curl.so.*
%{yast_plugindir}/libpy2ag_curl.so
%{yast_plugindir}/libpy2ag_tftp.so.*
%{yast_plugindir}/libpy2ag_tftp.so
%{yast_moduledir}/*

%dir %{yast_docdir}
%doc %{yast_docdir}/COPYING
