TESTS = check_hnef
check_PROGRAMS = check_hnef
check_hnef_SOURCES = \
	check_hnef.c \
	../board.h \
	../tile.h \
	../token.h
check_hnef_CFLAGS = @CHECK_CFLAGS@
check_hnef_LDADD = $(top_builddir)/libhnef/libhnef.la @CHECK_LIBS@
