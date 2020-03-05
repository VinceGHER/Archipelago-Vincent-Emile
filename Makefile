# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = project.cc city.cc node.cc error.cc tools.cc city.h node.h error.h tools.h
OFILES =  project.o city.o node.o error.o tools.o

# Regles
project: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o project
project.o: $(CXXFILES)
	$(CXX) $(CXXFLAGS) -c $< 
city.o: city.cc node.cc error.cc tools.cc city.h node.h error.h tools.h
	$(CXX) $(CXXFLAGS) -c $< 
node.o: node.cc error.cc tools.cc node.h error.h tools.h
	$(CXX) $(CXXFLAGS) -c $< 
error.o: error.cc error.h
	$(CXX) $(CXXFLAGS) -c $<
tools.o: tools.cc tools.h
	$(CXX) $(CXXFLAGS) -c $<
	