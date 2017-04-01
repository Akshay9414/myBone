# Added feature
# Compile UserPinConfig.h on change of timestamp
# compile .c main code. Can write in int main() like code
# removed auto clean up on exit feature 



#    This file is a part of the wiringBone library
#    Copyright (C) 2015 Abhraneel Bera

#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 3 of the License, or (at your option) any later version.

#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.

#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
#    USA


SRC_SEARCH_DIR = ../

INCLUDE_DIR = .

CPPFLAGS = -Wall

CPPFLAGS += -lpthread

PRUFLAGS = -lpruio

CPPFLAGS += -Wno-delete-non-virtual-dtor

CFLAGS = -Wall

CFLAGS += -lpthread

#include ../Makefile.mk

INCLUDE := $(addprefix -I , $(INCLUDE_DIR) $(SRC_SEARCH_DIR))

LIB_SRC := $(wildcard *.cpp)

C_SRC += $(wildcard $(addsuffix *.c, $(SRC_SEARCH_DIR)))

CPP_SRC += $(wildcard $(addsuffix *.cpp, $(SRC_SEARCH_DIR)))

INO_SRC += $(wildcard $(addsuffix *.ino, $(SRC_SEARCH_DIR)))

MAIN_SRC = $(C_SRC) $(CPP_SRC) $(INO_SRC)

LIB_OBJ = $(LIB_SRC:.cpp=.o)

C_OBJ = $(C_SRC:.c=.o) 

CPP_OBJ = $(CPP_SRC:.cpp=.o) 

INO_OBJ = $(INO_SRC:.ino=.o) 

MAIN_OBJ = $(addsuffix .o, $(basename $(notdir $(LIB_SRC) $(MAIN_SRC))))

PINS_OBJ = PINS.o

all: main  

main: $(LIB_OBJ) $(C_OBJ) $(CPP_OBJ) $(INO_OBJ) $(PINS_OBJ)  
	@echo Compiling Main executable
	@g++ $(MAIN_OBJ) $(INCLUDE) $(CPPFLAGS) $(PRUFLAGS) -o $@

$(PINS_OBJ): UserPinConfig.h

$(LIB_OBJ): %.o : %.cpp 
	@echo Compiling $<
	@g++ -c $< $(INCLUDE) $(CPPFLAGS) -o $@

$(C_OBJ): %.o : %.c
	@echo Compiling $(notdir $<)
	@g++ -include Arduino.h -c $< $(INCLUDE) $(CFLAGS) -o $(notdir $@)

$(CPP_OBJ): %.o : %.cpp
	@echo Compiling $(notdir $<)
	@g++ -include Arduino.h -c $< $(INCLUDE) $(CPPFLAGS) -o $(notdir $@)

$(INO_OBJ): %.o : %.ino
	@echo Compiling $(notdir $<)
	@g++ -x c++ -include Arduino.h -c $< $(INCLUDE) $(CPPFLAGS) -o $(notdir $@)

start: pru
#	@mkdir -p $(OBJ_DIR)

pru: PRU0.p PRU1.p
	@echo Compiling PRU Assembly
	@pasm -V3 -c -CPRU0code PRU0.p
	@pasm -V3 -c -CPRU1code PRU1.p

clean:
	rm -rf *.o main 
