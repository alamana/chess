CXX=g++
CXXFLAGS = -g
OFILES = frontend.o chessoutput.o AI/AIrandom.o AI/chessAI.o AI/chessmove.o AI/chessfunctions.o 
.SUFFIXES: .o .cpp

frontend: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES)

clean:
	-rm -f *.o *~ outputfile.exe

frontend.o: frontend.cpp chessoutput.h AI/chessfunctions.h AI/chessmove.h \
  AI/chessfunctions.h AI/chessAI.h
chessoutput.o: chessoutput.cpp chessoutput.h AI/chessfunctions.h \
  AI/chessfunctions.h
AIrandom.o: AI/AIrandom.cpp AI/AIrandom.h AI/chessmove.h \
  AI/chessfunctions.h AI/AIgeneric.h
chessAI.o: AI/chessAI.cpp AI/chessAI.h AI/AIgeneric.h AI/AIrandom.h
chessfunctions.o: AI/chessfunctions.cpp AI/chessfunctions.h
chessmove.o: AI/chessmove.cpp AI/chessmove.h AI/chessfunctions.h
#greedyai.o: AI/greedyai.cpp AI/greedyai.h AI/bitboard.h AI/chessmove.h \
  AI/chessfunctions.h
#bitboard.o: AI/bitboard.cpp AI/bitboard.h
