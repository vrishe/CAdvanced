TARGETS := seqlen trinum
CC := g++

SOURCES := $(foreach path,$(wildcard src/*.cpp),$(basename $(notdir $(path))))
HEADERS := $(patsubst %,include/%.h,$(filter-out $(TARGETS), $(SOURCES)))
MODULES := $(patsubst %,src/%.cpp,$(filter-out $(TARGETS), $(SOURCES)))

% : $(foreach %,$(TARGETS),src/%.cpp) $(HEADERS) $(MODULES) | $(BINDIR)
	$(CC) -std=c++11 -Wall -pedantic -I ./include $(MODULES) $< -o bin/$@.exe

all: $(TARGETS);

$(BINDIR): 
	mkdir bin

clean:
	rm -rf bin/*.*