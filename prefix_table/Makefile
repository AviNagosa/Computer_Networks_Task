prefix_table_opt: main_opt.o  prefix_table_opt.o
	clang++-9  main_opt.o prefix_table_opt.o -o prefix_table_opt

prefix_table: main.o  prefix_table.o
	clang++-9  main.o prefix_table.o -o prefix_table

prefix_table_opt.o: prefix_table_opt.cpp prefix_table_opt.hpp
	clang++-9 -c prefix_table_opt.cpp

prefix_table.o: prefix_table.cpp prefix_table.hpp	
	clang++-9 -c prefix_table.cpp

main.o: main.cpp prefix_table.hpp
	clang++-9 -c main.cpp

main_opt.o: main_opt.cpp prefix_table_opt.hpp
	clang++-9 -c main_opt.cpp

clean:
	rm *.o all

