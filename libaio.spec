Name: libaio
Version: 0.3.96
Release: 2
Summary: Linux-native asynchronous I/O access library
Copyright: LGPL
Group:  System Environment/Libraries
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-root
# Fix ExclusiveArch as we implement this functionality on more architectures
ExclusiveArch: i386 x86_64 ia64 s390 s390x ppc ppc64

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
* Wed Jun 18 2003 Michael K. Johnson <johnsonm@redhat.com> 0.3.96-2
- optimization in io_getevents from Arjan van de Ven in 0.3.96-1
- deal with ia64 in 0.3.96-2

* Wed May 28 2003 Michael K. Johnson <johnsonm@redhat.com> 0.3.95-1
- ppc bugfix from Julie DeWandel

* Tue May 20 2003 Michael K. Johnson <johnsonm@redhat.com> 0.3.94-1
- symbol versioning fix from Ulrich Drepper

* Mon Jan 27 2003 Benjamin LaHaise <bcrl@redhat.com>
- bump to 0.3.93-3 for rebuild.

* Mon Dec 16 2002 Benjamin LaHaise <bcrl@redhat.com>
- libaio 0.3.93 test release
- add powerpc support from Gianni Tedesco <gianni@ecsc.co.uk>
- add s/390 support from Arnd Bergmann <arnd@bergmann-dalldorf.de>

* Fri Sep 12 2002 Benjamin LaHaise <bcrl@redhat.com>
- libaio 0.3.92 test release
- build on x86-64

* Thu Sep 12 2002 Benjamin LaHaise <bcrl@redhat.com>
- libaio 0.3.91 test release
- build on ia64
- remove libredhat-kernel from the .spec file

* Thu Sep  5 2002 Benjamin LaHaise <bcrl@redhat.com>
- libaio 0.3.90 test release

* Mon Apr 29 2002 Benjamin LaHaise <bcrl@redhat.com>
- add requires initscripts >= 6.47-1 to get boot time libredhat-kernel 
  linkage correct.
- typo fix

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
