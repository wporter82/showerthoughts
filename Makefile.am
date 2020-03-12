AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = showerthoughts
showerthoughts_SOURCES = main.c
showerthoughts_LDADD = -lcurl -ljson-c
clean-full: clean
	-rm -rf .deps/
	-rm -rf autom4te.cache/
	-rm Makefile
	-rm Makefile.in
	-rm configure
	-rm config.log
	-rm config.status
	-rm install-sh
	-rm compile
	-rm aclocal.m4
	-rm missing
	-rm depcomp
