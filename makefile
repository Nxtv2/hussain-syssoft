.PHONY: unittests
unittests:
	@echo "Running tests"
	gcc lib/dplist.c -o lib/libdplist.so -lm -fPIC -shared -DRUN_AVG_LENGTH=5 -ggdb3
	gcc unittests.c -DDEBUG -ggdb3 -lcheck -lsubunit -ldplist -Wall -pedantic -L./lib -Wl,-rpath=./lib -o unittests -DRUN_AVG_LENGTH=5 -lm
	./unittests