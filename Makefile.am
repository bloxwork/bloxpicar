ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS=bloxpicar
bloxpicar_SOURCES=src/bloxpicar.c 

bloxpicar_LDADD= \
	-lwiringPi \
	-lwiringPiDev
	

MAINTAINERCLEANFILES = \
	$(srcdir)/aclocal.m4 \
	$(srcdir)/config.guess \
	$(srcdir)/config.h.in \
	$(srcdir)/config.sub \
	$(srcdir)/configure \
	$(srcdir)/configure.sh \
	$(srcdir)/depcomp \
	$(srcdir)/env.sh \
	$(srcdir)/install-sh \
	$(srcdir)/ltmain.sh \
	$(srcdir)/make.sh \
	$(srcdir)/missing \
	`find "$(srcdir)" -type f -name Makefile.in -print` \
	`find "$(srcdir)/m4" -type f -print`
	
