CXX = g++
CXXFLAGS = `Magick++-config --cppflags --cxxflags --libs` -std=c++0x -O9
LDFLAGS = `Magick++-config --ldflags`
OBJECTS = nn.o network.o neuron.o

nn: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o nn

%.o: %.cpp %.h Makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o nn
