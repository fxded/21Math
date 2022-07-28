TARGET = s21_math.c
TEST_TARGET = math_test.c


CC = gcc
CFLAGS = -O3 -Wall -Werror -Wextra -std=c11 -pedantic
TEST_FLAGS = -lcheck -lm -lpthread -lgcov

RM = rm -rf
a = 1
OBJ_DIR = ./obj/
OBJ = s21_math.o

all: test gcov_report s21_math.a

gcov_report: test
	gcovr -r. --html --html-details -o tests/coverage_report.html

test: lib.a s21_tests.o $(OBJ)
	$(CC) $(CFLAGS) $^ $(TEST_FLAGS) -o test
	./test

lib.a: $(OBJ)
	ar rcs $@ $(OBJ)

s21_math.a: s21_math_verter.o
	ar rcs $@ $(OBJ)

s21_tests.o: s21_tests.c
	$(CC) $(CFLAGS) --coverage -c $^


s21_math.o: $(TARGET)
	$(CC) $(CFLAGS) --coverage -c $^

s21_math_verter.o: $(TARGET)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o
	rm -rf *.gc*
	rm -rf *.a
	rm -rf test

.PHONY: all test clean check fclean gcovr gcov_report rebuild

git:
	read a
	git commit -a -m"$a"
	git push origin develop