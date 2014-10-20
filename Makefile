all: bjam.prepare bjam

doc:
	doxygen Doxyfile

doc.latex: doc
	make -C /doc/latex

bjam:
	BOOST_ROOT=./boost ./boost/bjam toolset=gcc
	
bjam.prepare:
	./bin/prepare-boost.sh 1.56.0 && \
	cd ./boost && \
	./bootstrap.sh

clean: clean.doc

cleandoc:
	-rm -r ./doc
