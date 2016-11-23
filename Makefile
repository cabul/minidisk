VERSION ?= Debug
VERBOSE ?= 0

echo_0 = @
echo = $(echo_$(VERBOSE))

cflags_Debug = -g
cflags_Release = -O2

# cflags_sfml = -Iext/sfml/include
# libs_sfml = -Lext/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
cflags_sfml = 
libs_sfml = -lsfml-graphics -lsfml-window -lsfml-system

cc = g++
cflags = -std=c++11 -Wall -pedantic
cflags += $(cflags_$(VERSION))  $(cflags_sfml)
libs = -lm $(libs_sfml)

sources = $(shell find src -name "*.cc")
objects = $(sources:%.cc=build/%.o)
depfiles = $(sources:%.cc=build/%.deps)
target = build/minidisk

.PHONY: all clean

all: $(target)

$(target): $(objects)
	@echo "+ building $@"
	@mkdir -p $(@D)
	$(echo)$(cc) $(cflags) -o $@ $^ $(libs)

build/%.o: %.cc
	@echo "+ compiling $<"
	@mkdir -p $(@D)
	$(echo)$(cc) $(cflags) -c $< -o $@

build/%.deps: %.cc
	@mkdir -p $(@D)
	@$(cc) -MM -MT $(@:%.deps=%.o) $< -o $@

-include $(depfiles)

clean:
	@rm -rf build
