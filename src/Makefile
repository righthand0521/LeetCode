SUBDIRS := $(wildcard */.)
SUBDIRS := $(filter-out uthash/., $(SUBDIRS))
ALLSUBDIRS = $(SUBDIRS:%=%)
BUILDSUBDIRS = $(SUBDIRS:%=build-%)
TESTSUBDIRS = $(SUBDIRS:%=test-%)
CLEANSUBDIRS = $(SUBDIRS:%=clean-%)

CC = gcc
C++ = g++
# CFLAGS = -ansi -g -Wall -O3 -ffreestanding -o
# CFLAGS = -std=c99 -g -Wall -O3 -ffreestanding -o
CFLAGS = -Wall -O3 -o
GPROFFLAGS = -Wall -pg -lc -o
LDFLAGS = -lm
DEBUGFLAGS = -DDEBUG=1
GDBFLAGS = -g3
CPPFLAGS = -DCPP=1

QUIET = @
ECHO = echo
RM = rm -rf
CP = cp
STRIP = strip
OBJDUMP = objdump -S ?
FILE = file
VALGRIND = valgrind
VALGRIND_ARGS = -s --tool=memcheck --leak-check=full --max-stackframe=5000000
VALGRIND_VER = $(shell valgrind --version)
GPROF = gprof

SRC = $(wildcard *.c)
OBJS  = $(patsubst %.c, %, $(wildcard *.c))
C++_SRC = $(wildcard *.cpp)
C++_OBJS  = $(patsubst %.cpp, %, $(wildcard *.cpp))
GMON = gmon.out

PATCH_VER = $(subst patch, , $(subst GNU, , $(shell for file in `patch -v | grep patch`; do echo $$file; done)))
PATCH_VER_MAJOR = $(word 1, $(subst ., ,$(PATCH_VER)))
PATCH_VER_MINOR = $(word 2, $(subst ., ,$(PATCH_VER)))
PATCH_VER_2_7 = $(shell [ $(PATCH_VER_MAJOR) -gt 2 -o \( $(PATCH_VER_MAJOR) -eq 2 -a $(PATCH_VER_MINOR) -ge 7 \) ] && echo true)
ifeq ($(PATCH_VER_2_7), true)
	PATCH_RESULT=found
else
	PATCH_RESULT=notfound
endif

JAVAC = javac
JAVAC_VER = $(subst patch, , $(subst GNU, , $(shell for file in `javac --version`; do echo $$file; done)))
JAVAC_FLAGS = -g
JAVA = java
JAVA_VER = $(subst patch, , $(subst GNU, , $(shell for file in `java --version`; do echo $$file; done)))
JAVA_SRC = $(wildcard *.java)
JAVA_OBJS  = $(patsubst %.java, %, $(wildcard *.java))

PYTHON = python3
PYTHON_VER = $(subst patch, , $(subst GNU, , $(shell for file in `python3 --version`; do echo $$file; done)))
PYTHON_SRC = $(wildcard *.py)

RUST = rustc
RUST_VER = $(subst patch, , $(subst GNU, , $(shell for file in `rustc --version`; do echo $$file; done)))
RUST_SRC = $(wildcard *.rs)
RUST_OBJS  = $(patsubst %.rs, %, $(wildcard *.rs))
RUST_FMT= rustfmt

all: clean $(ALLSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) $$file-c $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(CC) $(CFLAGS) $$file-c $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(FILE) $$file-c; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(CFLAGS) $$file-cpp $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(CPPFLAGS); \
		$(C++) $(CFLAGS) $$file-cpp $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(CPPFLAGS); \
		$(FILE) $$file-cpp; \
	done
	$(QUIET)$(ECHO)

build: clean $(BUILDSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) $$file-c $$file.c $(LDFLAGS); \
		$(CC) $(CFLAGS) $$file-c $$file.c $(LDFLAGS); \
		$(ECHO) $(STRIP) $$file-c; \
		$(STRIP) $$file-c; \
		$(FILE) $$file-c; \
		$(ECHO) ./$$file-c; \
		./$$file-c; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(CFLAGS) $$file-cpp $$file.cpp $(LDFLAGS) $(CPPFLAGS); \
		$(C++) $(CFLAGS) $$file-cpp $$file.cpp $(LDFLAGS) $(CPPFLAGS); \
		$(ECHO) $(STRIP) $$file-cpp; \
		$(STRIP) $$file-cpp; \
		$(FILE) $$file-cpp; \
		$(ECHO) ./$$file-cpp; \
		./$$file-cpp; \
	done
	$(QUIET)$(ECHO)

gprof: clean $(GPROFSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(GPROFFLAGS) $$file-c $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(GPROFFLAGS) $$file-c $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(FILE) $$file-c; \
		$(ECHO) "$(GPROF) -b $$file-c $(GMON)"; \
		$(ECHO) "$(GPROF) -b -A $$file-c $(GMON)"; \
		$(ECHO) "$(GPROF) -b $$file-c $(GMON) | gprof2dot | dot -T png -o output.png"; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $$file-cpp $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS) $(CPPFLAGS); \
		$(C++) $(CFLAGS) $$file-cpp $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS) $(CPPFLAGS); \
		$(FILE) $$file-cpp; \
	done
	$(QUIET)$(ECHO)

valgrind: clean $(VALGRINDSUBDIRS)
	$(QUIET)$(ECHO)
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) $$file-c $$file.c $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS); \
		$(CC) $(CFLAGS) $$file-c $$file.c $(DEBUGFLAGS) $(LDFLAGS); \
		$(FILE) $$file-c; \
		$(ECHO) "$(VALGRIND) $(VALGRIND_ARGS)" ./$$file-c; \
		$(VALGRIND) $(VALGRIND_ARGS) ./$$file-c; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(CFLAGS) $$file-cpp $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(GDBFLAGS) $(CPPFLAGS); \
		$(C++) $(CFLAGS) $$file-cpp $$file.cpp $(DEBUGFLAGS) $(LDFLAGS) $(CPPFLAGS); \
		$(FILE) $$file-cpp; \
		$(ECHO) "$(VALGRIND) $(VALGRIND_ARGS)" ./$$file-cpp; \
		$(VALGRIND) $(VALGRIND_ARGS) ./$$file-cpp; \
	done
	$(QUIET)$(ECHO)

lib: clean
	@for file in $(OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(CC) $(CFLAGS) -fPIC -shared lib$$file-c.so $$file.c; \
		$(CC) $(CFLAGS) -fPIC -shared lib$$file-c.so $$file.c; \
		$(FILE) lib$$file-c.so; \
	done
	$(QUIET)$(ECHO)
	@for file in $(C++_OBJS) ; do \
		$(ECHO) ; \
		$(ECHO) $(C++) $(CFLAGS) -fPIC -shared lib$$file-cpp.so $$file.cpp; \
		$(C++) $(CFLAGS) -fPIC -shared lib$$file-cpp.so $$file.cpp; \
		$(FILE) lib$$file-cpp.so; \
	done

java:
	$(QUIET)$(ECHO)
	@find . -name "*.class" -exec echo rm {} \; -exec rm -rf {} \;
	$(QUIET)$(ECHO)
	@for file in $(JAVA_OBJS) ; do \
		$(ECHO) $(JAVAC) $(JAVAC_FLAGS) $$file.java -d .; \
		$(JAVAC) $(JAVAC_FLAGS) $$file.java -d .; \
	done
	$(QUIET)$(ECHO)
	@find . -name "*.class" -exec $(FILE) {} \;
	$(QUIET)$(ECHO)

python: clean
	$(QUIET)$(ECHO)
	@for file in $(PYTHON_SRC) ; do \
		$(ECHO) $(PYTHON) $$file; \
		$(PYTHON) $$file; \
	done
	$(QUIET)$(ECHO)

rust: clean
	$(QUIET)$(ECHO)
	@for file in $(RUST_OBJS) ; do \
		$(ECHO) $(RUST_FMT) $$file.rs; \
		$(RUST_FMT) $$file.rs; \
		$(ECHO) $(RUST) $$file.rs; \
		$(RUST) $$file.rs; \
		$(FILE) $$file; \
		$(ECHO) ./$$file; \
		$(ECHO) $(RUST_FMT) --cfg clang $$file.rs; \
		$(ECHO) RUST_BACKTRACE=1 ./$$file; \
		$(ECHO) RUST_BACKTRACE=full ./$$file; \
	done
	$(QUIET)$(ECHO)

clean: $(CLEANSUBDIRS)
	$(QUIET)$(ECHO)
	@find . -name "*.so" -exec echo rm {} \; -exec rm -rf {} \;
	@find . -name "*.out" -exec echo rm {} \; -exec rm -rf {} \;
	@find . -name "vgcore.*" -exec echo rm {} \; -exec rm -rf {} \;
	@find . -name "__pycache__" -exec echo rm {} \; -exec rm -rf {} \;
	@for file in $(OBJS) ; do \
		if [ -e $$file-c ]; then \
			$(ECHO) $(RM) $$file-c; \
			$(RM) $$file-c; \
		fi; \
	done
	@for file in $(C++_OBJS) ; do \
		if [ -e $$file-cpp ]; then \
			$(ECHO) $(RM) $$file-cpp; \
			$(RM) $$file-cpp; \
		fi; \
	done
	@find . -name "*.class" -exec echo rm {} \; -exec rm -rf {} \;
	@for file in $(RUST_OBJS) ; do \
		if [ -e $$file ]; then \
			$(ECHO) $(RM) $$file; \
			$(RM) $$file; \
		fi; \
	done
	$(QUIET)$(ECHO)


$(ALLSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:%=%)

$(BUILDSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:build-%=%) build

$(GPROFSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:gprof-%=%) gprof

$(VALGRINDSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:valgrind-%=%) valgrind

$(CLEANSUBDIRS):
	$(QUIET)$(ECHO)
	$(MAKE) -C $(@:clean-%=%) clean

info:
	$(QUIET)$(ECHO) "CC = $(CC)"
	$(QUIET)$(ECHO) "C++ = $(C++)"
	$(QUIET)$(ECHO) "CFLAGS = $(CFLAGS)"
	$(QUIET)$(ECHO) "GPROFFLAGS = $(GPROFFLAGS)"
	$(QUIET)$(ECHO) "LDFLAGS = $(LDFLAGS)"
	$(QUIET)$(ECHO) "CPPFLAGS = $(CPPFLAGS)"
	$(QUIET)$(ECHO) "DEBUGFLAGS = $(DEBUGFLAGS)"
	$(QUIET)$(ECHO) "GDBFLAGS = $(GDBFLAGS)"
	$(QUIET)$(ECHO) "VALGRIND_VER = $(VALGRIND_VER)"
	$(QUIET)$(ECHO) "PATCH_VER=$(PATCH_VER)"
	$(QUIET)$(ECHO) "PATCH_VER_MAJOR=$(PATCH_VER_MAJOR)"
	$(QUIET)$(ECHO) "PATCH_VER_MINOR=$(PATCH_VER_MINOR)"
	$(QUIET)$(ECHO) "PATCH_VER_2_7=$(PATCH_VER_2_7)"
	$(QUIET)$(ECHO) "PATCH_RESULT=${PATCH_RESULT}"
	$(QUIET)$(ECHO) "JAVAC_VER=$(JAVAC_VER)"
	$(QUIET)$(ECHO) "JAVA_VER=$(JAVA_VER)"
	$(QUIET)$(ECHO) "PYTHON_VER=$(PYTHON_VER)"
	$(QUIET)$(ECHO) "RUST_VER=$(RUST_VER)"
