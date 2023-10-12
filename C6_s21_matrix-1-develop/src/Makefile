CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -std=c11
NAME = s21_matrix.a test
OS=$(shell uname -s)
ifeq ($(OS), Linux)
	FLAGS_PLATFORM = -lcheck -lm -lpthread -lrt -lsubunit
else
	FLAGS_PLATFORM = -lcheck -lm -lpthread
endif

.PHONY: all clean test s21_matrix.a gcov_report

all: clean s21_matrix.a

test: s21_test_matrix.o s21_matrix.a s21_matrix.o
	$(CC) s21_matrix.o s21_test_matrix.o s21_matrix.a $(FLAGS_PLATFORM) -o test
	./test

	
s21_matrix.o: s21_matrix.c	
	$(CC) $(CC_FLAGS) -c s21_matrix.c

s21_test_matrix.o: s21_test_matrix.c	
	$(CC) $(CC_FLAGS) -c s21_test_matrix.c

gcov_report: s21_matrix.a 
	$(CC) $(CC_FLAGS) --coverage s21_matrix.c s21_test_matrix.c $(FLAGS_PLATFORM) -o gcov_report.o
	@./gcov_report.o
	@lcov -t x21_test_matrix -o s21_test_matrix.info -c -d .
	@genhtml -o gcov_report s21_test_matrix.info
	@open ./gcov_report/index.html


check: s21_matrix.a
	cppcheck *.h *.c
	cp ../materials/linters/.clang-format ../src
	clang-format -n *.h *.c
	$(CC) s21_test_matrix.c s21_matrix.a -lcheck
	$(CC) $(CC_FLAGS) -c s21_test_matrix.c -o test.o
	$(CC) test.o s21_matrix.a $(FLAGS_PLATFORM) -o test
	CK_FORK=no leaks --atExit -- ./test
	rm -rf .clang-format

s21_matrix.a: s21_matrix.o
	$(CC) -c s21_matrix.c
	ar rcs s21_matrix.a s21_matrix.o

clean:
	@rm -f *.a
	@rm -f s21_matrix
	@rm -f *.o
	@rm -f *.txt
	@rm -f *.gcda
	@rm -f *.gcdo
	@rm -f *.gcno
	@rm -f *.info
	@rm -rf *.dSYM
	@rm -rf ./gcov_report
	@rm -f test
	@rm -f *.out

vg: s21_matrix.a
	CK_FORK=no valgrind --tool=memcheck ./test

leak: s21_matrix.a
	CK_FORK=no leaks -atExit -- ./test

install lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

clang:
	cp ../materials/linters/.clang-format ../src
	clang-format -i *.h *.c
	rm -rf .clang-format

push:
	make clean
	make clang
	git add *.c *.h Makefile
	git commit -m "Update"
	git push origin develop


