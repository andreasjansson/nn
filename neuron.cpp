#include <math.h>
#include "neuron.h"
#include "synapse.h"
#include "nn.h"

#define MIN_INIT_WEIGHT 0
#define MAX_INIT_WEIGHT 0.01
#define MIN_INIT_BIAS 0
#define MAX_INIT_BIAS 0.0

Neuron::Neuron()
{
  bias = 0 * random_double(MIN_INIT_BIAS, MAX_INIT_BIAS);
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
  return tanh(x * 2);
}

const double Neuron::compute_activation()
{
  activation = 0;

  for(Synapse *synapse : incoming_synapses) {
    activation += synapse->weight * synapse->from->activation;
  }

  activation += bias;

  activation = activation_function(activation);
  return activation;
}

const double Neuron::activation_derivative()
{
  return 1 - tanh(4 * activation * activation);
}

const double Neuron::get_delta_for_label(const double label)
{
  return (label - activation) * activation_derivative();
}

const double Neuron::get_delta()
{
  double delta = 0;
  for(Synapse *out_synapse : outgoing_synapses) {
    delta += out_synapse->weight * out_synapse->to->delta;
  }
  delta *= activation_derivative();
  return delta;
}
