#include <list>
#include "network.h"

using std::list;

void Network::forward_propagation()
{
  for(auto layer = (++layers.begin()); layer != layers.end(); layer ++) {
    for(Neuron *neuron : *layer) {
      neuron->compute_activation();
    }
  }
}
