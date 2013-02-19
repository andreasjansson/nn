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
  double delta;
  list<Synapse *> incoming_synapses;
  list<Synapse *> outgoing_synapses;
  double bias;

  Neuron();
  Neuron(const Neuron &);
  ~Neuron();
  const double compute_activation();
  const double activation_derivative();
  void initialise();
  void create_synapse_from(Neuron &);

private:
  double activation_function(const double);
};

#endif
