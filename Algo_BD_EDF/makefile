all: EDF BOUNDED_DELAY

EDF: main_edf.o edf.o
	clang++-9 main_edf.o edf.o -o EDF

BOUNDED_DELAY: main_bd.o bd.o
	clang++-9 main_bd.o bd.o -o BOUNDED_DELAY

main_edf.o: main_edf.cpp edf.hpp
	clang++-9 -c main_edf.cpp

main_bd.o: main_bd.cpp bd.hpp
	clang++-9 -c main_bd.cpp

bd.o: bd.cpp bd.hpp
	clang++-9 -c bd.cpp

edf.o: edf.cpp edf.hpp
	clang++-9 -c edf.cpp	

clean:
	rm *.o all

