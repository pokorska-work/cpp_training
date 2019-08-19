#ifndef WORM_H_
#define WORM_H_

#include <vector>
#include <thread>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

//#include "board.h"
#include <iostream>

class Board;

class Worm : public std::thread {
 protected:
  int id_;
  int x_, y_; // Coordinates of the head
  int currDir_;
  std::vector<std::pair<int,int>> tail_; // coordinates of the tail
  bool alive;
  Board* board_; // No ownership, TODO: change to shared_ptr

 public:
  Worm(int x, int y, Board* b, int dir = 0)
    : x_(x), y_(y), currDir_(dir), alive(true), board_(b) {}
  void move();
  void kill() { alive = false; }
  virtual void run() = 0;
  void operator()(int id) { id_ = id; run(); }
  int getId() const { return id_; }
};

class LazyWorm : public Worm {
 public:
  LazyWorm(int x, int y, Board* b) : Worm(x,y,b) {
    srand(time(nullptr));
    currDir_ = rand() % 4;
  }
  void run();
};


#endif // WORM_H_
