AM_CFLAGS = -Wall -Werror -Wpedantic

lib_LTLIBRARIES = libTarget.la libMockup.la

libTarget_la_SOURCES = target.c

libMockup_la_LDFLAGS = -L$(builddir)/.libs -lTarget

libMockup_la_SOURCES = mockup.c
