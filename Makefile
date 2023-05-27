DATE := $(shell date)
OS := $(shell uname -s)
CC := gcc
LIB_SRC := s21_matrix_oop.cpp
TEST_SRC := matrix_test.cpp
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
TFLAG := -lgtest
ifeq ($(OS), Linux)
    CC := g++
endif

all: clean s21_matrix_oop.a test

test:
	$(CC) $(CFLAGS) $(LIB_SRC) $(TEST_SRC) -o s21_matrix_oop_test $(TFLAG)
	./s21_matrix_oop_test

s21_matrix_oop.a:
	$(CC) $(CFLAGS) -c $(LIB_SRC)
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	rm s21_matrix_oop.o

clean:
	rm -rf *.o          \
	s21_matrix_oop.a    \
	s21_matrix_oop_test \
	main                \
	.clang-format

check: check_clang check_leaks

check_clang:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -n *.cpp *.h
	@clang-format -i *.cpp *.h
	@rm .clang-format

check_leaks: test
ifeq ($(OS), Linux)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./s21_matrix_oop_test
else
	leaks -atExit -- ./s21_matrix_oop_test | grep LEAK:
endif

push:
	git add .
	git commit -m "$(DATE)"
	git push origin develop

.PHONY: all             \
		clean           \
		test            \
		s21_matrix_oop.a

