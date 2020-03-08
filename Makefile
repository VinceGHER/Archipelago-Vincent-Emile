# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = project.cc city.cc node.cc error.cc tools.cc city.h node.h error.h tools.h
OFILES =  project.o city.o node.o error.o tools.o
DEBUG = -D NDEBUG

# Regles
# création du ficher executable (commande: make)
project: $(OFILES)
	$(CXX) $(CXXFLAGS) $(DEBUG) $(OFILES) -o project
project.o: $(CXXFILES)
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<
node.o: node.cc error.cc tools.cc node.h error.h tools.h constantes.h
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $< 
city.o: city.cc node.cc error.cc tools.cc city.h node.h error.h tools.h
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $< 
error.o: error.cc error.h
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<
tools.o: tools.cc tools.h
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

# création du fichier de test (commande: make sequenceTest)
sequenceTest: sequenceTest.o city.o node.o error.o tools.o
	$(CXX) $(CXXFLAGS) $(DEBUG) sequenceTest.o city.o node.o error.o tools.o -o sequenceTest && ./sequenceTest
sequenceTest.o: sequenceTest.cc node.cc city.cc  error.cc tools.cc city.h node.h error.h tools.h
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<
	