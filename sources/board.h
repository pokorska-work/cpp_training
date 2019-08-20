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
  Board(int width, int height): nextId_(1) { // TODO: handle incorrect arguments.
    board_.resize(height+1);
    for (int i = 0; i < board_.size(); ++i)
      board_[i].resize(width+1);
  }
  ~Board() {
    for (auto& worm : worms_)
      worm.second.join();
  }
  void addWorm(WormType type, int x, int y) {
    if (type == Lazy) {
      worms_.emplace(nextId_, std::thread(LazyWorm(x,y,this),nextId_));
    } else {
      worms_.emplace(nextId_, std::thread(HunterWorm(x,y,this),nextId_));
    }
    board_[x][y] = nextId_;
    wormTypes_[nextId_] = type;
    nextId_++;
  }
  int getWidth() const { return board_[0].size(); }
  int getHeight() const { return board_.size(); }
  bool isWormAt(int x, int y) const { return board_[x][y] != 0; }
  int at(int x, int y) const { return board_[x][y]; }
  void update(int id, int oldX, int oldY, int newX, int newY) {
    int targetId = board_[newX][newY];
    if (targetId != 0 && targetId != id)
      killed_.insert(targetId);
    board_[oldX][oldY] = 0;
    board_[newX][newY] = id;
  }
  WormType getWormType(int id) {
    return wormTypes_[id];
  }
  bool checkKill(int id) {
    return killed_.count(id) > 0;
  }
  void clearDead() {
    for (int i = 0; i < board_.size(); ++i)
      for (int j = 0; j < board_[0].size(); ++j)
        if (killed_.count(board_[i][j]) > 0)
          board_[i][j] = 0;
  }
};

#endif // BOARD_H_
