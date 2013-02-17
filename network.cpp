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
}

void Network::train(vector<double> &annotated_example)
{
  Layer *input_layer = layers[0];
  assert(input_layer->size() == annotated_example.size() - 1);
}

double Network::test(vector<double> &example)
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
