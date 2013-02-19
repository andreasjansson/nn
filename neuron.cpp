#include <math.h>
#include "neuron.h"
#include "synapse.h"
#include "util.h"

#define MIN_INIT_WEIGHT 0
#define MAX_INIT_WEIGHT 0.01
#define MIN_INIT_BIAS 0
#define MAX_INIT_BIAS 0.0

Neuron::Neuron()
{
  bias = random_double(MIN_INIT_BIAS, MAX_INIT_BIAS);
}

Neuron::Neuron(const Neuron &neuron)
{

}

Neuron::~Neuron()
{

}

void Neuron::create_synapse_from(Neuron &other)
{
  Synapse *synapse = new Synapse(&other, this);
  synapse->weight = random_double(MIN_INIT_WEIGHT, MAX_INIT_WEIGHT);
  incoming_synapses.push_back(synapse);
  other.outgoing_synapses.push_back(synapse);
}

double Neuron::activation_function(const double x)
{
  return 1 / (1 + exp(-x));
}

const double Neuron::compute_activation()
{
  activation = 0;

  for(Synapse *synapse : incoming_synapses) {
    activation += synapse->weight * synapse->from->activation;
  }

  activation += bias;

  return activation = activation_function(activation);
}

const double Neuron::activation_derivative()
{
  return activation * (1 - activation);
}
