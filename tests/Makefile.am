TESTS = \
	check_token \
	check_tile \
	check_board
check_PROGRAMS = \
	check_token \
	check_tile \
	check_board
check_token_sources = \
	check_token.c \
	../token.h
check_tile_sources = \
	check_tile.c \
	../token.h \
	../tile.h
check_board_sources = \
	check_tile.c \
	../token.h \
	../tile.h \
	../board.h
check_token_CFLAGS = @CHECK_CFLAGS@
check_tile_CFLAGS = @CHECK_CFLAGS@
check_board_CFLAGS = @CHECK_CFLAGS@
check_token_LDADD = $(top_builddir)/libhnef/libhnef.la @CHECK_LIBS@
check_tile_LDADD = $(top_builddir)/libhnef/libhnef.la @CHECK_LIBS@
check_board_LDADD = $(top_builddir)/libhnef/libhnef.la @CHECK_LIBS@
