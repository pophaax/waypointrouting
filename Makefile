#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    coursecalculation
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror -std=c++14
LIBS = -I$(SAILINGROBOTS_HOME)

SOURCES_WPR = WaypointRouting.cpp
HEADERS_WPR = WaypointRouting.h
FILE_WPR = WaypointRouting.o



all : $(FILE_WPR)

$(FILE_WPR) : $(SOURCES_WPR) $(HEADERS_WPR)
	$(CC) $(SOURCES_WPR) $(FLAGS) $(LIBS) -c -o $(FILE_WPR)

clean :
	rm -f $(FILE_WPR)