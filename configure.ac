# see semver.org for version info
AC_INIT([shared-lib-test],[0.0.1],[bvideau@anl.gov])

# are we in the right source dir ?
AC_CONFIG_SRCDIR([src/target.c])

# build artefacts in separate dir
AC_CONFIG_AUX_DIR([m4])
AC_CONFIG_MACRO_DIR([m4])

# automake should fail on any error
AM_INIT_AUTOMAKE([-Wall -Werror foreign 1.12])
AM_PROG_AR

# check for libtool
LT_INIT([disable-static])

# check for programs
AC_LANG([C])
AC_PROG_CC
AC_PROG_CC_STDC
AC_HEADER_ASSERT

AC_CHECK_LIB([dl], [dlopen])
AC_CHECK_LIB([pthread], [pthread_once])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])

AC_OUTPUT
