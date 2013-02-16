#ifndef SYNAPSE_H
#define SYNAPSE_H

class Neuron;

class Synapse
{
public:
  Neuron &from;
  Neuron &to;
  double weight;
};

#endif
