#ifndef NETWORK_H
#define NETWORK_H

#include <list>
#include <vector>
#include "neuron.h"
#include "nn.h"

using std::list;
using std::vector;

typedef vector<Neuron *> Layer;

class Network {

public:
  vector<Layer *> layers;
  Layer *input_layer;
  Layer *output_layer;

  Network(vector<int> &);
  ~Network();
  //Network(const Network &);
  void train(const list<TrainingExample> &, int = 10);
  list<double> *test(const vector<double> &);
  void print_debugging();

private:
  double learning_rate;
  double weight_decay;

  void forward_propagation();
  void back_propagation(const vector<double> &);
};

#endif
