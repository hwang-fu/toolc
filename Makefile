ROOT 	:= .
INCLUDE := ./include/hwangfu
LIB 	:= ./lib

.PHONY: update build clean test

update:
	${MAKE} clean && ${MAKE} build

build:
	@./script/build.sh
	@echo
	@echo
	@find . -type f \( -name "*.c" -o -name "*.h" \) -exec wc -l {} +

clean:
	rm -rf ${INCLUDE}/*
	rm -rf ${LIB}/*

test:
	./script/test.sh
