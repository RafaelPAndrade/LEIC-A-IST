# Build Makefile
# SO 2017
# Rafael Andrade, drsspam
# Projeto heatSim

SHELL       := /bin/sh
PROGRAM     := ../heatSim

SRC_FILES   := ../src
LIB_FILES   := ../lib

vpath %.h $(SRC_FILES):$(LIB_FILES)
vpath %.c $(SRC_FILES):$(LIB_FILES)

CC          := gcc
CFLAGS      := -Wall -Wextra -pedantic -pedantic-errors -g

base        := matrix2d error_handling parse
objects      = $(addsuffix .o, $(base))

define compile
	$(CC) $(CFLAGS) $(objects) -o $(PROGRAM)
endef


# Targets
.PHONY: v3 v2 v1 v0

# 4th: Threaded, memory sharing, timed saves
v3: CFLAGS += -pthread
v3: $(addsuffix .o, $(base) main3 threads_mem_save)
v3: base += main3 threads_mem_save # this is a make limitation
v3:
	$(compile)

# 3th: Threaded, memory sharing
v2: CFLAGS += -pthread
v2: $(addsuffix .o, $(base) main2 threads_mem)
v2: base += main2 threads_mem # this is a make limitation
v2:
	$(compile)

# 2nd: Threaded, message passing
v1: CFLAGS += -pthread
v1: $(addsuffix .o, $(base) main1 threads_mess leQueue mplib3)
v1: base += main1 threads_mess leQueue mplib3 # this is a make limitation
v1:
	$(compile)


# 1st: Single thread
v0: $(addsuffix .o, $(base) main0 sequential)
v0: base += main0 sequential # this is a make limitation
v0:
	$(compile)


# Source code

common_headers := simul.h matrix2d.h error_handling.h

# Main files
main0.o    : $(common_headers)
main1.o    : $(common_headers)
main2.o    : $(common_headers)
main3.o    : $(common_headers)

sequential.o       : $(common_headers)
threads_mess.o     : $(common_headers) mplib3.h
threads_mem.o      : $(common_headers)
threads_mem_save.o : $(common_headers)

error_handling.o : error_handling.h
parse.o          : error_handling.h

# Libs
leQueue.o  : leQueue.h
mplib3.o   : mplib3.h leQueue.h
matrix2d.o : matrix2d.h


# Utils
.PHONY : clean cleaner full
clean :
	$(RM) ./*.o

cleaner : clean
	$(RM) $(PROGRAM)

full  : cleaner
	$(MAKE)
