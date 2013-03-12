CXX=g++
CXXFLAGS = -Wall -Wextra -pedantic -g
OFILES = chessoutput.o frontend.o AI/AIrandom.o AI/chessAI.o AI/chessfunctions.o AI/chessmove.o 
.SUFFIXES: .o .cpp

frontend: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES)

clean:
	-rm -f AI/*.o AI/*~ *.o *~ outputfile.exe

chessoutput.o: chessoutput.cpp chessoutput.h AI/chessfunctions.h
frontend.o: frontend.cpp chessoutput.h AI/chessfunctions.h AI/chessmove.h \
 AI/chessfunctions.h AI/chessAI.h AI/AIgeneric.h
AIrandom.o: AI/AIrandom.cpp AI/AIrandom.h AI/chessmove.h \
  AI/chessfunctions.h AI/AIgeneric.h
#bitboard.o: AI/bitboard.cpp AI/bitboard.h
chessAI.o: AI/chessAI.cpp AI/chessAI.h AI/AIgeneric.h AI/AIrandom.h \
   AI/chessmove.h AI/chessfunctions.h
chessfunctions.o: AI/chessfunctions.cpp AI/chessfunctions.h
chessmove.o: AI/chessmove.cpp AI/chessmove.h AI/chessfunctions.h
#greedyai.o: AI/greedyai.cpp AI/greedyai.h AI/bitboard.h AI/chessmove.h \
    AI/chessfunctions.h

