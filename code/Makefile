TARGET = turing
SUBDIR = $(shell ls ./ -R | grep /)
SUBDIRS = $(subst :,/,$(SUBDIR))
RESULT = $(foreach dir, $(SUBDIRS), $(wildcard $(dir)result.txt))
CONSOLE = $(foreach dir, $(SUBDIRS), $(wildcard $(dir)console.txt))

$(TARGET) : src/main.cpp src/tm.h src/tm.cpp
	g++ -g -o $(TARGET) src/main.cpp src/tm.h src/tm.cpp
	
clean :
	-rm $(TARGET)
	-rm $(RESULT) $(CONSOLE)