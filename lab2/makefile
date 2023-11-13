MKDIR := MKDIR_
SRCdir := src
TESTSdir := tests

EXE := bin/exec
argFile := tests/arg.txt

COMDERS := $(wildcard $(PWD)/*.cpp)
HEAMDERS := $(wildcard $(PWD)/*.h)
TESTERIN := $(wildcard $(PWD)/*.in)
TESTEROUT := $(wildcard $(PWD)/*.out)

FLAGINC = -o $@ -c -I include $<
FLAGSO = -shared -o

HEADERS := $(wildcard include/*.h)
LIBS := $(addprefix lib/,libscalar.a libmatrix.so)
LIBS_DEPENDECIES := $(addprefix build/,exceptions logger matrix)
SCALAR_DEPENDENCIES := $(addsuffix _static.o,$(LIBS_DEPENDECIES))
MATRIX_DEPENDENCIES := $(addsuffix _dynamic.o,$(LIBS_DEPENDECIES))

TEST1ARGS := A
TEST2ARGS := A
TEST3ARGS := d
TEST4ARGS := X
TEST5ARGS := T
TEST6ARGS := S
TEST7ARGS := M
TEST8ARGS := M
TESTS_FROM := 1
TESTS_TO := 8
TESTS := $(addprefix test,$(shell seq $(TESTS_FROM) $(TESTS_TO)))

vpath %.h include
vpath %.cpp $(SRCdir)

all: build | format

.PHONY: format
format:
	@if [ ! -d "$(PWD)/src" ]; then\
		mkdir src;\
	fi;\
	if [ "$(COMDERS)" ]; then\
		mv *.cpp src;\
	fi;\
	if [ ! -d "$(PWD)/include" ]; then\
		mkdir include;\
	fi;\
	if [ "$(HEAMDERS)" ]; then\
			mv *.h include;\
	fi;\
	if [ ! -d "$(PWD)/tests" ]; then\
		mkdir tests;\
	fi;\
build/%_static.o: %.cpp $(HEADERS) | $(MKDIR)build
	@g++ $(FLAGINC)

build/%_dynamic.o: %.cpp $(HEADERS) | $(MKDIR)build
	@g++ $(FLAGINC) -fPIC

lib/libscalar.a: $(SCALAR_DEPENDENCIES) | $(MKDIR)lib
	@ar rcs $@ $^

lib/libmatrix.so: $(MATRIX_DEPENDENCIES) | $(MKDIR)lib
	@g++ $(FLAGSO) $@ $^

$(MKDIR)%:
	@mkdir -p $(patsubst $(MKDIR)%,%,$@)

.PHONY: libs
libs: $(LIBS)

.PHONY: tests
tests: $(TESTS)

test%: $(TESTSdir)/test%.in $(TESTSdir)/test%.out | build
	@$(EXE) -$(TEST$(patsubst test%,%,$@)ARGS) $< > build/test.out
	@-diff $(word 2, $^) build/test.out > build/test.log
	@[ -s build/test.log ] && echo "$(patsubst test%,%,$@)st Test Failed" || echo "$(patsubst test%,%,$@)st Test Passed"
	@rm -rf build/test.log build/test.out
	@mv outputLog.log ./build/

.PHONY: pre_run
pre_run: 
	@read -p "Enter arguments for the operation: " argument;\
	echo $$argument > $(argFile)

.PHONY: run
run: build | pre_run
	@./bin/exec $(shell cat tests/arg.txt) tests/run.in > tests/run.out
	@mv outputLog.log ./build/

.PHONY: clean
clean:
	@rm -rf bin build lib
	@find $(PWD) -type f -exec touch {} +

.PHONY: unformat
unformat:
	@rm -rf bin build lib
	@if [ -d "$(PWD)/src" ]; then\
		mv src/* ./;\
		rmdir src;\
	fi;\
	if [ -d "$(PWD)/include" ]; then\
		mv include/* ./;\
		rmdir include;\
	fi;\
	if [ -d "$(PWD)/tests" ]; then\
		mv tests/* ./;\
		rmdir tests;\
	fi;\

.PHONY: man
man:
	@echo "make format   => creates the necessary directories and groups the files appropriately!"
	@echo "make unformat => removes all directories and moves the all files to the current directory!"
	@echo "make clean    => removes all the extra folders and files created when using build!"
	@echo "make          => only builds the code and organises it!"
	@echo "make build    => only builds the code and organises it!"
	@echo "make tests    => formats and builds and tests the code!"
	@echo "make libs     => makes a libs directory and creates appropriate files in it!"