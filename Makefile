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
LIBS =

SOURCES_WPR = WaypointRouting.cpp
HEADERS_WPR = WaypointRouting.h
FILE_WPR = WaypointRouting.o

SOURCES_SW = StandardWaypoint.cpp
HEADERS_SW = StandardWaypoint.h
FILE_SW = StandardWaypoint.o

SOURCES_TW = TimedWaypoint.cpp
HEADERS_TW = TimedWaypoint.h
FILE_TW = TimedWaypoint.o



all : $(FILE_WPR) $(FILE_SW) $(FILE_TW)

$(FILE_WPR) : $(SOURCES_WPR) $(HEADERS_WPR)
	$(CC) $(SOURCES_WPR) $(FLAGS) $(LIBS) -c -o $(FILE_WPR)

$(FILE_SW) : $(SOURCES_SW) $(HEADERS_SW)
	$(CC) $(SOURCES_SW) $(FLAGS) $(LIBS) -c -o $(FILE_SW)

$(FILE_TW) : $(SOURCES_TW) $(HEADERS_TW)
	$(CC) $(SOURCES_TW) $(FLAGS) $(LIBS) -c -o $(FILE_TW)

clean :
	rm -f $(FILE_WPR) $(FILE_SW) $(FILE_TW)