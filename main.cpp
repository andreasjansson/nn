#include "network.h"

int main(int argc, char **argv)
{
  double training_data[][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1}
  };

  int nlayers = 3;
  int nneurons[3] = {2, 2, 1};

  Network();
}
