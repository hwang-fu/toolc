
INCLUDE := ./include
LIB		:= ./lib

.PHONY: all clean test

all:
	@./script/build.sh
	@find . -type f \( -name "*.c" -o -name "*.h" \) -exec wc -l {} +

clean:
	rm -rf ${INCLUDE}
	rm -rf ${LIB}
