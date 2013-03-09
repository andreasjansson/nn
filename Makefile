CXX = g++
CXXFLAGS = `Magick++-config --cppflags --cxxflags --libs` -std=c++0x -O9 -fopenmp -g
LDFLAGS = `Magick++-config --ldflags` -fopenmp
OBJECTS = nn.o network.o neuron.o

library: $(OBJECTS)
#	ar rvs nn.a $(OBJECTS)
	$(CXX) -shared -Wl,-undefined,dynamic_lookup $(LDFLAGS) -o libnn.so $(OBJECTS)

install: libnn.so
	cp libnn.so /usr/local/lib/libnn.so

nn: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o nn

%.o: %.cpp %.h Makefile
	$(CXX) -fPIC $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o *.so
