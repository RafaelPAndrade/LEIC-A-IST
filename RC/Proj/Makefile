# Main Makefile
# RC 2018/19
# Rafael Andrade, Diogo Ramalho, Manuel Manso
# P1 Grupo 28

SHELL         := /bin/sh
RELEASE_NAME  := proj_28

SRC_FILES   := BS.py CS.py user.py
LIB_FILES   := $(wildcard lib/*.py)

ZIP         := zip
ZIP_FLAGS   := -ur --quiet


.PHONY : zip
zip :
	$(ZIP) $(ZIP_FLAGS) $(RELEASE_NAME).zip $(MAKEFILE_LIST) ||:
	$(ZIP) $(ZIP_FLAGS) $(RELEASE_NAME).zip $(SRC_FILES) ||:
	$(ZIP) $(ZIP_FLAGS) $(RELEASE_NAME).zip $(LIB_FILES) ||:

.PHONY: clean
clean:
	$(RM) $(wildcard *.pickle)
