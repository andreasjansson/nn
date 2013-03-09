#include <math.h>
#include "neuron.h"
#include "synapse.h"
#include "nn.h"

Neuron::Neuron()
{
  bias = 0;
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
  synapse->weight = random_double(-.24, .24);
  incoming_synapses.push_back(synapse);
  other.outgoing_synapses.push_back(synapse);
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

double Neuron::activation_function(const double x)
{
  return 1 / (1 + exp(-x));
}

const double Neuron::activation_derivative()
{
  return activation * (1 - activation);
}

const double Neuron::get_delta_for_label(const double label)
{
  return (label - activation) * activation_derivative();
}

const double Neuron::get_delta(double avg_activation)
{
  static double sparsity_penalty_weight = 3;
  static double sparsity = .05;
  double delta = 0;
  for(Synapse *out_synapse : outgoing_synapses) {
    delta += out_synapse->weight * out_synapse->to->delta;
  }

  printf("%f\n", avg_activation);

  delta += sparsity_penalty_weight *
    (-(sparsity / avg_activation) + ((1 - sparsity) / (1 - avg_activation)));

  delta *= activation_derivative();
  return delta;
}

