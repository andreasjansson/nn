nn: main.cpp neuron.h neuron.cpp synapse.h network.h network.cpp nn.h Makefile
	g++ -g -std=c++0x -onn -O0 main.cpp neuron.cpp network.cpp
