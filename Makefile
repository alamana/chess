CXX=g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -fpermissive `pkg-config --cflags gtk+-3.0`
OFILES = chessoutput.o frontend.o AI/AIabpruning.o AI/AIrandom.o AI/AIgreedy.o AI/AIoptimized.o AI/AIoptimizedmove.o AI/chessAI.o AI/chessfunctions.o AI/chessmove.o AI/AInegascout.o AI/Simulator.o
LIBS=`pkg-config --libs gtk+-3.0`
.SUFFIXES: .o .cpp

frontend: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) $(LIBS)

clean:
	-rm -f AI/*.o AI/*~ GUI/*.o GUI/*~ *.o *~ outputfile.exe

AIabpruning.o: AI/AIabpruning.cpp AI/AIabpruning.h AI/AIgeneric.h \
    AI/chessmove.h AI/chessfunctions.h AI/Simulator.h
AIgreedy.o: AI/AIgreedy.cpp AI/AIgreedy.h AI/AIgeneric.h AI/chessmove.h \
    AI/chessfunctions.h AI/Simulator.h
AInegascout.o: AI/AInegascout.cpp AI/AInegascout.h AI/AIgeneric.h \
    AI/chessmove.h AI/chessfunctions.h AI/Simulator.h
AIoptimized.o: AI/AIoptimized.cpp AI/AIoptimized.h AI/AIgeneric.h \
    AI/AIoptimizedmove.h  AI/chessfunctions.h AI/chessmove.h \
    AI/Simulator.h chessoutput.h chessfunctions.h
AIoptimizedmove.o: AI/AIoptimizedmove.cpp AI/AIoptimizedmove.h  \
    AI/chessfunctions.h
AIrandom.o: AI/AIrandom.cpp AI/AIrandom.h AI/chessmove.h \
    AI/chessfunctions.h AI/Simulator.h AI/AIgeneric.h
chessAI.o: AI/chessAI.cpp AI/chessAI.h AI/AIgeneric.h AI/AIrandom.h \
    AI/chessmove.h AI/chessfunctions.h AI/Simulator.h AI/AIgreedy.h \
    AI/AIabpruning.h AI/AIoptimized.h AI/AIoptimizedmove.h  \
    AI/AInegascout.h
chessfunctions.o: AI/chessfunctions.cpp AI/chessfunctions.h
chessmove.o: AI/chessmove.cpp AI/chessmove.h AI/chessfunctions.h \
    AI/Simulator.h
Simulator.o: AI/Simulator.cpp AI/Simulator.h AI/chessmove.h \
    AI/chessfunctions.h
chessoutput.o: chessoutput.cpp chessoutput.h AI/chessfunctions.h
frontend.o: frontend.cpp chessoutput.h AI/chessfunctions.h AI/chessmove.h \
    AI/chessfunctions.h AI/Simulator.h AI/chessAI.h AI/AIgeneric.h
