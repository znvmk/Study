#TAR:zndb.out

#cc :=gcc


zndb.out:zndb.o DbQuery.o 
	g++ -o out/zndb.out obj/zndb.o obj/DbQuery.o 
zndb.o:src/zndb.cpp
	g++ -c -o obj/zndb.o src/zndb.cpp
DbQuery.o:src/DbQuery.cpp
	g++ -c -o obj/DbQuery.o src/DbQuery.cpp

#伪目标
.PHONY:clean

clean:
	rm -r obj/*.o out/*.out \
		out/db/*

run:
	./out/zndb.out
	
