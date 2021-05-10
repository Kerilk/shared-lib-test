AM_COLOR_TESTS = yes

AM_TESTS_ENVIRONMENT = export LIBTARGET='../src/.libs/libTarget.so'; export LD_LIBRARY_PATH='../src/.libs/':$$LD_LIBRARY_PATH;

TEST_PROGS = \
	test_dlopen

check_PROGRAMS = $(TEST_PROGS)
TESTS = $(TEST_PROGS)
