
COMPILER = g++ -std=c++11
CFLAGS   = -O3 -w
LIBS     =
LDFLAGS  = -lm						# usr/libのライブラリがリンク
INCLUDE  = -I/usr/include/boost
SOURCES  = $(wildcard *.cpp)
SRC_DRIVE = drive_sim.cpp main.cpp
MAIN = $(basename $(SOURCES))

all: $(MAIN)
$(MAIN): %: %.cpp
	$(COMPILER) $(CFLAGS) $(INCLUDE) $< -o $@ $(LDFLAGS)

DriveSim: $(SRC_DRIVE)
	$(COMPILER) $(CFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(MAIN)
