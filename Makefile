all: bjam

doc:
	doxygen Doxyfile

doc.latex: doc
	make -C /doc/latex

bjam:
ifeq ($(wildcard ./boost/.*),)
	./bin/prepare-boost.sh 1.56.0
endif
ifeq ($(wildcard ./boost/bjam),)
	cd ./boost && ./bootstrap.sh
endif
	BOOST_ROOT=./boost ./boost/bjam toolset=gcc warnings=all

clean: clean.doc

clean.doc:
	-rm -r ./doc
