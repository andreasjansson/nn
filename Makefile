nn: main.cpp neuron.h neuron.cpp synapse.h network.h network.cpp nn.h
	g++ -g -std=c++0x -onn -O9 main.cpp neuron.cpp network.cpp
