CC = g++
CPPFLAGS = -g -std=c++11 -Wall

TEST_DIR = tests

GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread
UTILS = $(TEST_DIR)/utils/runtime_evaluator.cpp $(TEST_DIR)/utils/random_generator.cpp

VLGR = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean
all: $(TARGET)

################## TESTS ##################

merge-test: $(TEST_DIR)/merge_test.cpp msort.h
	$(CC) $(CPPFLAGS) $< $(UTILS) $(GTEST_LL) -o $(TEST_DIR)/$@

merge-test-run: merge-test
	$(TEST_DIR)/merge-test

merge-test-vlgr: merge-test
	$(VLGR) $(TEST_DIR)/merge-test

functor-test: $(TEST_DIR)/functor_test.cpp functor.h
	$(CC) $(CPPFLAGS) $< $(GTEST_LL) -o $(TEST_DIR)/$@
	$(VLGR) $(TEST_DIR)/functor-test

fatalist-test: $(TEST_DIR)/fatalist_test.cpp
	$(CC) $(CPPFLAGS) $< $(GTEST_LL) -o $(TEST_DIR)/$@
	$(VLGR) $(TEST_DIR)/fatalist-test

cave-test: $(TEST_DIR)/cave_test.cpp
	$(CC) $(CPPFLAGS) $< $(GTEST_LL) -o $(TEST_DIR)/$@
	$(VLGR) $(TEST_DIR)/cave-test

###########################################

clean:
	rm $(TEST_DIR)/merge-test
	rm $(TEST_DIR)/functor-test
	rm $(TEST_DIR)/fatalist-test
	rm $(TEST_DIR)/cave-test
