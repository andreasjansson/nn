#include <list>
#include <assert.h>
#include "network.h"
#include "neuron.h"
#include "nn.h"
#include <signal.h>

using std::list;
using std::vector;
using std::get;

Network::Network(vector<int> &layer_sizes)
  : layers(), learning_rate(.9), weight_decay(0.0001)
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

void Network::train(const list<TrainingExample> &training_examples, int iterations)
{
  Layer *input_layer = layers[0];

  for(int i = 0; i < iterations; i ++) {
    for(const TrainingExample &training_example : training_examples) {

      vector<double> example = training_example.first;
      vector<double> labels = training_example.second;
      assert(input_layer->size() == example.size());
      assert(output_layer->size() == labels.size());

      int j = 0;
      for(Neuron *neuron : *input_layer) {
        neuron->activation = example[j ++];
      }
      
      forward_propagation();
      back_propagation(labels);

      /*
      print_debugging();
      printf("\n");
      */
    }

    //printf("%5d ", i);
    
    learning_rate *= .99;
    printf("learning_rate: %f\n", learning_rate);
  }

  //print_debugging();
}

list<double> *Network::test(const vector<double> &example)
{
  int j = 0;
  for(Neuron *neuron : *input_layer) {
    neuron->activation = example[j ++];
  }

  forward_propagation();

  list<double> *result = new list<double>();
  for(Neuron *neuron : *output_layer) {
    result->push_back(neuron->activation);
  }      
  
  return result;
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
  for(int i = layers.size() - 1; i >= 1; -- i) {
    Layer *layer = layers[i];

    int j = 0;
    for(Neuron *neuron : *layer) {
      double label = labels[j ++];
      if(layer == output_layer) {
        neuron->delta = -neuron->get_delta_for_label(label);
      }
      else {

        double avg_activation = 0;
        if(layer != output_layer) {
          for(double label : labels) {
            avg_activation += neuron->activation * label;
          }
          avg_activation /= labels.size();
        }

        neuron->delta = neuron->get_delta(avg_activation);
      }
    }
  }

  //printf("------------------\n");

  for(int i = 0; i < layers.size() - 1; ++ i) {
    Layer *layer = layers[i];
    for(Neuron *neuron : *layer) {
      for(Synapse *synapse : neuron->outgoing_synapses) {
        synapse->weight -= learning_rate * (neuron->activation * synapse->to->delta +
                                            weight_decay * synapse->weight);
      }
      neuron->bias -= learning_rate * neuron->delta;
    }
  }
}

void Network::print_debugging()
{
  int layer_i = 0;
  for(Layer *layer : layers) {
    printf("Layer %d\n", layer_i);
    int neuron_i = 0;
    
    for(Neuron *neuron : *layer) {
      printf("  (%d)\n", neuron);
      printf("    Activation: %f\n", neuron->activation);
      printf("    Bias: %f\n", neuron->bias);
      printf("    Delta: %f\n", neuron->delta);

      for(Synapse *synapse : neuron->outgoing_synapses) {
        printf("    --> (%d) weight: %f\n", synapse->to, synapse->weight);
      }

      neuron_i ++;
    }

    layer_i ++;
  }
}
