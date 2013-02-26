#include <list>
#include <tuple>
#include <vector>
#include <stdio.h>
#include <armadillo>
#include <random>
#include <Magick++.h>
#include <math.h>
#include <string>
#include <cstdlib>
#include <sys/time.h>
#include "network.h"
#include "nn.h"

using std::list;
using std::vector;
using std::tuple;
using std::make_tuple;
using std::initializer_list;

void preprocess_training_examples(list<TrainingExample> &examples)
{
  vector<double> mins;
  vector<double> maxes;

  int i;
  for(TrainingExample &example : examples) {
    i = 0;
    for(double x : example.first) {
      if(mins.size() <= i) {
        mins.push_back(x);
        maxes.push_back(x);
      }
      else {
        if(x < mins[i])
          mins[i] = x;
        if(x > maxes[i])
          maxes[i] = x;
      }
      i ++;
    }
  }

  for(TrainingExample &example : examples) {
    for(i = 0; i < example.first.size(); i ++) {
      example.first[i] = (example.first[i] - mins[i]) / (maxes[i] - mins[i]);
    }
  }
}

void load_image2(arma::mat &image)
{
  image.fill(-1.);
  for(int i = 0; i < image.n_cols; i ++) {
    image(i, i) = 1;
  }
  for(int i = 0; i < image.n_cols; i ++) {
    image(image.n_cols - i - 1, i) = 1;
  }
}

void save_image(arma::mat &image, std::string filename) {
  Magick::Image im(Magick::Geometry(image.n_cols, image.n_rows), Magick::Color("black"));
  im.modifyImage();
  im.type(Magick::GrayscaleType);
  Magick::PixelPacket *pixels = im.getPixels(0, 0, image.n_cols, image.n_rows);
  for(int y = 0; y < image.n_rows; y ++) {
    for(int x = 0; x < image.n_cols; x ++) {
      pixels[x + y * image.n_cols] = Magick::ColorGray((image(x, y) + 1) / 2.0);
    }
  }

  im.syncPixels();
  im.filterType(Magick::PointFilter);
  im.resize("800x800");
  im.write(filename.c_str());
}

void save_image(list<Neuron *> *neurons, int single_width, std::string filename) {
  int row = 0, column = 0, x = 0, y = 0;
  int border = 2;
  int rows = sqrt(neurons->size());
  int columns = ceil(neurons->size() / float(rows));

  //printf("%d,%d\n", rows, columns);

  int height = rows * single_width + (rows - 1) * border;
  int width = columns * single_width + (columns - 1) * border;
  Magick::Image im(Magick::Geometry(width, height), Magick::Color("black"));
  im.modifyImage();
  im.type(Magick::GrayscaleType);
  Magick::PixelPacket *pixels = im.getPixels(0, 0, width, height);

  for(Neuron *neuron : *neurons) {
    x = 0;
    y = 0;
    for(Synapse *synapse : neuron->outgoing_synapses) {
      int im_x = x + column * (border + single_width);
      int im_y = y + row * (border + single_width);

      //printf("%d, %d\n", im_x, im_y);

      pixels[im_x + im_y * width] = Magick::ColorGray(synapse->weight);

      x ++;
      if(x == single_width) {
        x = 0;
        y ++;
      }
    }

    column ++;
    if(column == columns) {
      column = 0;
      row ++;
    }
  }

  im.syncPixels();
  im.filterType(Magick::PointFilter);
  im.resize("800x800");
  im.write(filename.c_str());
}

void load_image(arma::mat &image)
{
  Magick::Image im;
  im.read("image.jpg");
  Magick::Color colour;
  Magick::PixelPacket *pixels = im.getPixels(0, 0, image.n_cols, image.n_rows);
  for(int y = 0; y < image.n_rows; y ++) {
    for(int x = 0; x < image.n_cols; x ++) {
      colour = pixels[x + y * image.n_cols];
      image(x, y) = Magick::ColorGray(colour).shade() * 2 - 1;
    }
  }

  save_image(image, "loaded.jpg");
}

int main(int argc, char **argv)
{
  int side = 8;
  arma::mat image(600, 600);
  load_image(image);
  save_image(image, "original.jpg");

  struct timeval tv;
  gettimeofday(&tv,NULL);
  srandom((unsigned)(tv.tv_usec + time(NULL)));

  vector<int> layer_sizes{side * side, 25, side * side};
  Network network(layer_sizes);

  //save_image(network.layers[1], side, std::string("layer1_first.png"));

  list<TrainingExample> training_examples;

  arma::mat training_image;
  for(int i = 0; i < 10; i ++) {

    char istr[10];
    sprintf(istr, "%d", i);

    if(image.n_cols <= side && image.n_rows <= side) {
      training_image = image;
    }
    else {
      int left = random() % (image.n_cols - side);
      int top = random() % (image.n_rows - side);
      training_image = image.submat(top, left, top + side - 1, left + side - 1);

      //save_image(training_image, std::string("train_") + istr + ".jpg");
    }
    training_image.reshape(side * side, 1);

    arma::colvec col = training_image.col(0);
    vector<double> data = arma::conv_to<vector<double> >::from(col);
    training_examples.push_back({data, data});
  }

  network.train(training_examples, 100);

  //  network.print_debugging();

  save_image(network.layers[1], side, "out.png");

  /*
  list<TestExample> test_examples{
    {0.08, 0.58, 0.07, 0.08},
    {0.56, 0.21, 0.68, 0.75}
  };

  for(TestExample &example : test_examples) {
    list<double> *result = network.test(example);
    printf("[ ");
    for(double x : example) {
      printf("%.2f ", x);
    }
    printf("] => ");
    printf("[ ");
    for(double x : *result) {
      printf("%.2f ", x);
    }
    printf("]\n");

    free(result);
  }
  */
}
