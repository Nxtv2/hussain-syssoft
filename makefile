.PHONY: unittests
unittests:
	@echo "Running tests"
	gcc lib/dplist.c -o lib/libdplist.so -lm -fPIC -shared -DRUN_AVG_LENGTH=5
	gcc unittests.c -DDEBUG -lcheck -lsubunit -ldplist -Wall -pedantic -L./lib -Wl,-rpath=./lib -o unittests -DRUN_AVG_LENGTH=5 -lm
	./unittests