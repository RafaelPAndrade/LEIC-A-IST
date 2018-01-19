# Main Makefile
# SO 2017
# Rafael Andrade, drsspam
# Projeto heatSim

SHELL         := /bin/sh
RELEASE_NAME  := heatSim_v4

# readablility script (error checking removal)
PYTHON                  := /usr/bin/python3
MAKE_READABLE           := rem_error_checking.py
FILES_TO_MAKE_READABLE  := src/threads_mem_save.c
READABLE_FILES          := src_readable

OBJ_FILES   := build
SRC_FILES   := src
LIB_FILES   := lib
TST_FILES   := tests
TST_COMM    := ./run_tests.sh

ZIP         := zip
ZIP_FLAGS   := -ur --quiet

CLEAN_COM   := cleaner

.DEFAULT_GOAL := .DEFAULT

.DEFAULT:
	$(MAKE) $(MAKECMDGOALS) -C $(OBJ_FILES)

.PHONY : zip test do
zip :
	$(MAKE) $(CLEAN_COM)
	$(ZIP) $(ZIP_FLAGS) $(RELEASE_NAME).zip $(MAKEFILE_LIST) ||:
	$(ZIP) $(ZIP_FLAGS) $(RELEASE_NAME).zip $(SRC_FILES) ||:
	$(ZIP) $(ZIP_FLAGS) $(RELEASE_NAME).zip $(OBJ_FILES) ||:
	$(ZIP) $(ZIP_FLAGS) $(RELEASE_NAME).zip $(LIB_FILES) ||:


test : do
	cd $(TST_FILES) && $(TST_COMM)

do :
	$(MAKE) -C $(OBJ_FILES)

readable :
	$(PYTHON) $(MAKE_READABLE) $(FILES_TO_MAKE_READABLE)
