#ifndef NEURON_H
#define NEURON_H

#include <list>
#include <math.h>
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
  void initialise();
  void create_synapse_from(Neuron &);
  const double activation_derivative();
  const double get_delta_for_label(const double);
  const double get_delta(double avg_activation);

private:
  double activation_function(const double);
};

#endif
