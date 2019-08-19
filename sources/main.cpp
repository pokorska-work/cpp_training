#include <iostream>
#include "graphics.h"
#include "worm.h"

#include "board.h"

int main(int argc, char** argv) {
  std::cout << "Worms app\n";
  //std::thread t(LazyWorm(1,2,nullptr),2);
  //t.join();
  return Graphics::createAndRun(argc, argv);
}
