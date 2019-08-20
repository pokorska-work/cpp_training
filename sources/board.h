#ifndef BOARD_H_
#define BOARD_H_

#include <unordered_map>
#include <unordered_set>
#include <thread>

#include "worm.h"

enum WormType {
  Lazy, Hunter
};

class Board {
 private:
  std::vector<std::vector<int>> board_;
  std::unordered_map<int, std::thread> worms_;
  std::unordered_map<int, WormType> wormTypes_;
  std::unordered_set<int> killed_;
  int nextId_;

 public:
  Board(int width, int height);
  ~Board();
  void addWorm(WormType type, int x, int y);
  int getWidth() const { return board_[0].size(); }
  int getHeight() const { return board_.size(); }
  bool isWormAt(int x, int y) const { return board_[x][y] != 0; }
  int at(int x, int y) const { return board_[x][y]; }
  void update(int id, int oldX, int oldY, int newX, int newY);
  WormType getWormType(int id) { return wormTypes_[id]; }
  bool checkKill(int id) { return killed_.count(id) > 0; }
  void clearDead();
};

#endif // BOARD_H_
