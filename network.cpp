#include <list>
#include <assert.h>
#include "network.h"
#include "neuron.h"

using std::list;
using std::vector;

Network::Network(vector<int> &layer_sizes)
  : layers()
{
  for(int size : layer_sizes) {
    Layer *layer = new Layer();
    for(int i = 0; i < size; i ++) {
      Neuron *neuron = new Neuron();
      if(layers.size() > 0) {
        Layer *previous_layer = layers.back();
        for(auto previous_neuron : *previous_layer) {
           neuron->create_synapse_from(*previous_neuron);
        }
      }
      layer->push_back(neuron);
    }
    layers.push_back(layer);
  }

  input_layer = layers.front();
  output_layer = layers.back();
}

Network::~Network()
{
  for(Layer *layer : layers) {
    for(Neuron *neuron : *layer) {
      delete neuron;
    }
    delete layer;
  }
};

void Network::train(const vector<double> &example, const vector<double> &labels,
                    int iterations)
{
  Layer *input_layer = layers[0];
  assert(input_layer->size() == example.size());
  assert(output_layer->size() == labels.size());

  int i = 0;
  for(Neuron *neuron : *input_layer) {
    neuron->activation = example[i ++];
  }

  for(i = 0; i < iterations; i ++) {
    forward_propagation();
    back_propagation(labels);
  }
}

double Network::test(const vector<double> &example)
{
  return 0;
}

void Network::forward_propagation()
{
  for(auto layer = (++layers.begin()); layer != layers.end(); layer ++) {
    for(Neuron *neuron : **layer) {
      neuron->compute_activation();
    }
  }
}

void Network::back_propagation(const vector<double> &labels)
{
  for(int i = layers.size() - 1; i >= 0; -- i) {
    Layer *layer = layers[i];
    int j = 0;
    for(Neuron *neuron : *layer) {
      double label = labels[j ++];
      if(layer == output_layer) {
        neuron->delta = -(label - neuron->activation) * neuron->activation_derivative();
      }
      else if(layer > 0) {
        neuron->delta = 0;
        for(Synapse *out_synapse : neuron->outgoing_synapses) {
          neuron->delta += out_synapse->weight * out_synapse->to->delta;
        }
        neuron->delta *= neuron->activation_derivative();
      }
    }
  }
}
