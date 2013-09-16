# flags
# CC=clang++ -std=c++11 -stdlib=libc++ -lpthread
CC=g++ -std=c++11 -pthread
CFLAGS=-c -g3 -O0 -Wall -I.
LDFLAGS=

# tests
TESTSOURCES=$(shell find tst -iname '*.cpp')
TESTOBJECTS=$(TESTSOURCES:tst/%.cpp=obj/tst/%.o)
	
TESTEXECUTABLE=GTest

all: $(TESTSOURCES) $(TESTEXECUTABLE)
	./${TESTEXECUTABLE}

$(TESTEXECUTABLE): $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(LDFLAGS) $(TESTOBJECTS) -lgtest $(patsubst obj/main.o, ,$(OBJECTS)) -o $(TESTEXECUTABLE)

obj/tst/%.o : tst/%.cpp tst/*test.hpp tst/test_common.h typelist/**/*.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -lgtest -o $@

clean:
	rm -rf obj/**/*.o
	rm -rf obj/*.o
	rm -rf $(EXECUTABLE) $(TESTEXECUTABLE)

