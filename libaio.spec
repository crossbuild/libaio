Name: libaio
Version: 0.3.13
Release: 2
Summary: Linux-native asynchronous I/O access library
Copyright: LGPL
Group:  System Environment/Libraries
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-root
# Fix ExclusiveArch as we implement this functionality on more architectures
ExclusiveArch: i386
Requires: iniscripts >= 6.47-1

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
This package provides header files to include and libraries to link with
for the Linux-native asynchronous I/O facility ("async I/O", or "aio").

%prep
%setup

%build
make

%install
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

make install prefix=$RPM_BUILD_ROOT/usr root=$RPM_BUILD_ROOT

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

# if no libredhat-kernel.so is in place, the stub's version of 1.0.0
# will link correctly for apps.  This requires that the kernel's 
# libredhat-kernel.so be 1.0.1 or higher.
%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root)
%attr(0755,root,root) /usr/lib/libaio.so.*
%attr(0755,root,root) /lib/kernel/stub/*
%attr(0755,root,root) /lib/libredhat-kernel*
%doc COPYING TODO

%files devel
%defattr(-,root,root)
%attr(0644,root,root) /usr/include/*
%attr(0755,root,root) /usr/lib/libaio.so
%attr(0644,root,root) /usr/lib/libaio.a
%attr(0755,root,root) /usr/lib/libredhat-kernel.so

%changelog
* Mon Apr 29 2002 Benjamin LaHaise <bcrl@redhat.com>
- add requires initscripts >= 6.47-1 to get boot time libredhat-kernel 
  linkage correct.

* Thu Apr 25 2002 Benjamin LaHaise <bcrl@redhat.com>
- make /usr/lib/libredhat-kernel.so point to /lib/libredhat-kernel.so.1.0.0

* Mon Apr 15 2002 Tim Powers <timp@redhat.com>
- make the post scriptlet not use /bin/sh

* Sat Apr 12 2002 Benjamin LaHaise <bcrl@redhat.com>
- add /lib/libredhat-kernel* to %files.

* Fri Apr 12 2002 Benjamin LaHaise <bcrl@redhat.com>
- make the dummy install as /lib/libredhat-kernel.so.1.0.0 so 
  that ldconfig will link against it if no other is installed.

* Tue Jan 22 2002 Benjamin LaHaise <bcrl@redhat.com>
- add io_getevents

* Tue Jan 22 2002 Michael K. Johnson <johnsonm@redhat.com>
- Make linker happy with /usr/lib symlink for libredhat-kernel.so

* Mon Jan 21 2002 Michael K. Johnson <johnsonm@redhat.com>
- Added stub library

* Sun Jan 20 2002 Michael K. Johnson <johnsonm@redhat.com>
- Initial packaging
