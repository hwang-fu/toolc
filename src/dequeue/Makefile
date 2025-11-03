CC 		:= clang

CFLAGS 	:= -Wall
CFLAGS 	+= -O2
CFLAGS 	+= -fPIC

LFLAGS 	:=

AR 		:= ar
ARFLAGS := rcs

BUILD := ./build
LIB   := ./lib

DIRS  := $(BUILD)
DIRS  += $(LIB)

SRCS := $(wildcard *.c)

TARGET  := $(patsubst %.c,$(LIB)/lib%.a,$(SRCS))

.PHONY: all clean

all: $(DIRS) $(TARGET)

dirs: | $(BUILD) $(LIB)
$(BUILD) $(LIB):
	@mkdir -p $@

$(LIB)/lib%.a: $(BUILD)/%.o
	$(AR) $(ARFLAGS) $@ $<

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(LIB)
	rm -rf $(BUILD)
