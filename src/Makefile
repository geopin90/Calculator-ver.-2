CC=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
TEST=-lgtest
REP=--coverage
PBUILD=../build/

all: clean tests

install: build copy
	rm -rf $(PBUILD)

copy:
	mkdir $(HOME)/Applications/CojessCalc/
	cp -rf $(PBUILD)calc.app $(HOME)/Applications/CojessCalc/
	open $(HOME)/Applications/CojessCalc/

build:
	mkdir $(PBUILD)
	cp calc.pro $(PBUILD)
	cd $(PBUILD) && qmake calc.pro && make

uninstall:
	rm -rf $(HOME)/Applications/CojessCalc/

dvi:
	open info.html

dist:
	tar -cvf $(HOME)/Applications/CojessCalc.tar $(HOME)/Applications/CojessCalc/calc.app info.html
	open $(HOME)/Applications/

tests:
	$(CC) $(FLAGS) $(REP) test.cpp ../src/QT_calc/Model/model.cpp -o test $(TEST)
	./test

gcov_report: tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	make open

open:
	open report/index.html

clean:
	rm -rf *.out *.o *.a *.gcda *.gcno *.info test m
	rm -rf ../build/
	rm -rf report/

check: tests lint cpp leaks clean

lint:
	python3 ../materials/linters/cpplint.py --extension=cpp test.cpp QT_calc/Model/* QT_calc/Controller/* QT_calc/View/*.h QT_calc/View/*.cpp

cpp:
	cppcheck --enable=all --suppress=unknownMacro --suppress=unusedFunction --suppress=missingInclude --language=c++ test.cpp QT_calc/Model/* QT_calc/Controller/* QT_calc/View/*.h QT_calc/View/*.cpp

leaks:
	leaks -atExit -- ./test

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -v --log-file=valgrind-out.txt ./test