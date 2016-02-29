# norootforbuild

%define fedora_version 12

%if 0%{?fedora}
	%define breq qt4-devel
	%define qmake /usr/bin/qmake-qt4
	%define lrelease /usr/bin/lrelease-qt4
%endif
%if 0%{?suse_version}
	%define breq libqt4-devel
	%define qmake /usr/bin/qmake
	%define lrelease /usr/bin/lrelease
	%define _qt4_translationdir /usr/share/qt4/translations
%endif
%if 0%{?mandriva_version}
	%define breq libqt4-devel qt4-linguist
	%define qmake /usr/lib/qt4/bin/qmake
	%define lrelease /usr/lib/qt4/bin/lrelease
	%define _qt4_translationdir /usr/lib/qt4/translations
%endif

Name:		qrdc
Version:	0.0.1
Release:	1
License:	GPL
Source:		%{name}_%{version}.tar.gz
Group:		Network
Summary:	QT-based Remote Desctop Connection frontend.
Vendor:		TI_Eugene <ti.eugene@gmail.com>
BuildRequires:	gcc-c++, make, %{breq}
BuildRoot:	%{_tmppath}/%{name}-%{version}-build
Prefix:		/usr

%description
%{summary}

%if 0%{?mandriva_version} == 0
	%debug_package
%endif

%prep
%setup -q

%build
%{lrelease} %{name}.pro
%{qmake}
make

%install
%{__rm} -rf %{buildroot}
%{makeinstall} INSTALL_ROOT=%{buildroot}

%clean
%{__rm} -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc doc/*
%{_bindir}/%{name}
%{_qt4_translationdir}/%{name}_*.qm
%{_datadir}/applications/%{name}.desktop
%{_datadir}/pixmaps/%{name}.png

%changelog
* Sun Mar 31 2010 TI_Eugene <ti.eugene@gmail.com>
- Initital build in OBS
