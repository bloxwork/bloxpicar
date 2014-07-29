#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([PreInit], [1.0], [aleblo@web.de])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
#AC_CONFIG_SRCDIR([src/raspi-mpd.c])
#AM_INIT_AUTOMAKE([foreign])

AC_CONFIG_MACRO_DIR([m4])

PKG_CHECK_MODULES(JANSSON, jansson)

AC_PROG_CC
AC_PROG_INSTALL

# adding the lib to the files to link
#LIBS="-lrt $LIBS"

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
