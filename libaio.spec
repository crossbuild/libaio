Name: libaio
Version: 0.3.5
Release: 1
Summary: Linux-native asynchronous I/O access library
Copyright: LGPL
Group:  System Environment/Libraries
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-root
# Fix ExclusiveArch as we implement this functionality on more architectures
ExclusiveArch: i386

%description
The Linux-native asynchronous I/O facility ("async I/O", or "aio") has a
richer API and capability set than the simple POSIX async I/O facility.
This library, libaio, provides the Linux-native API for async I/O.
The POSIX async I/O facility requires this library in order to provide
kernel-accelerated async I/O capabilities, as do applications which
require the Linux-native async I/O API.

%package devel
Summary: Development files for Linux-native asynchronous I/O access
Group: Development/System
Requires: libaio

%description devel
This package provides header files and libraries to link against for
the Linux-native asynchronous I/O facility ("async I/O", or "aio").

%prep
%setup

%build
make

%install
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

make install prefix=$RPM_BUILD_ROOT/usr

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root)
%attr(0755,root,root) /usr/lib/libaio.so.*
%doc COPYING TODO

%files devel
%defattr(-,root,root)
%attr(0644,root,root) /usr/include/*
%attr(0755,root,root) /usr/lib/libaio.so
%attr(0644,root,root) /usr/lib/libaio.a

%changelog
* Sun Jan 20 2002 Michael K. Johnson <johnsonm@redhat.com>
- Initial packaging
