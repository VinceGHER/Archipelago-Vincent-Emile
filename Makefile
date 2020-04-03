# Definitions de macros
OUT = projet
CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc  gui.cc city.cc node.cc error.cc tools.cc graphic.cc city.h gui.h node.h error.h tools.h graphic.h constantes.h
OFILES =  projet.o gui.o city.o node.o error.o tools.o graphic.o
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`

# Regles
# création du ficher executable (commande: make)

all: $(OUT)

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)
projet.o: $(CXXFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
gui.o: gui.cc city.cc node.cc error.cc tools.cc graphic.cc gui.h city.h node.h error.h tools.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
city.o: city.cc node.cc error.cc tools.cc graphic.cc city.h node.h error.h tools.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING) 
node.o: node.cc error.cc tools.cc graphic.cc node.h error.h tools.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
error.o: error.cc error.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
tools.o: tools.cc graphic.cc tools.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)
graphic.o: graphic.cc graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

clean:
	@echo "Cleaning compilation files"
	@rm *.o $(OUT) *.cc~ *.h~


# création du fichier de test (commande: make sequenceTest)
sequenceTest: sequenceTest.o city.o node.o error.o tools.o
	$(CXX) $(CXXFLAGS) sequenceTest.o city.o node.o error.o tools.o -o sequenceTest && ./sequenceTest
sequenceTest.o: sequenceTest.cc node.cc city.cc  error.cc tools.cc city.h node.h error.h tools.h
	$(CXX) $(CXXFLAGS) -c $<
	