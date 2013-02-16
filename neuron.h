#ifndef NEURON_H
#define NEURON_H

#include <list>
#include "synapse.h"

using std::list;

class Synapse;

class Neuron
{
public:
  double activation;

  const double MIN_INIT_WEIGHT;
  const double MAX_INIT_WEIGHT;
  const double MIN_INIT_BIAS;
  const double MAX_INIT_BIAS;

  Neuron();
  Neuron(const Neuron &);
  ~Neuron();
  const double compute_activation();
  void initialise();

private:
  list<Synapse *> incoming_synapses;
  double bias;

  double activation_function(const double);
};

#endif
