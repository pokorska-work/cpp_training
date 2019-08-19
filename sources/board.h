#ifndef BOARD_H_
#define BOARD_H_

#include <unordered_map>
#include <thread>

#include "worm.h"

enum WormType {
  Lazy, Hunter
};

class Board {
 private:
  std::vector<std::vector<int>> board_;
  // TODO: cleanup dead worms.
  std::unordered_map<int, std::thread> worms_;
  int nextId_;

 public:
  Board(int width, int height): nextId_(1) { // TODO: handle incorrect arguments.
    board_.resize(height+1);
    for (int i = 0; i < board_.size(); ++i)
      board_[i].resize(width+1);
  }
  void addWorm(WormType type, int x, int y) {
    if (type == Lazy) {
      worms_.emplace(nextId_, std::thread(LazyWorm(x,y,this),nextId_));
      board_[x][y] = nextId_;
      nextId_++;
    }
  }
  int getWidth() const { return board_[0].size(); }
  int getHeight() const { return board_.size(); }
  bool isWormAt(int x, int y) const { return board_[x][y] != 0; }
  void update(int id, int oldX, int oldY, int newX, int newY) {
    board_[oldX][oldY] = 0;
    board_[newX][newY] = id;
  }
};

#endif // BOARD_H_