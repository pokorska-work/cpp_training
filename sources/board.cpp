#include "board.h"


Board::Board(int width, int height) : nextId_{1}, killAll_{false} {
  board_.resize(height);
  for (int i = 0; i < (int)board_.size(); ++i)
    board_[i].resize(width);
}

Board::~Board() {
  for (auto& worm : worms_)
    worm.second.join();
}

void Board::addWorm(WormType type, int x, int y) {
  if (board_[x][y] > 0) return;
  if (type == Lazy) {
    worms_.emplace(nextId_, std::thread(LazyWorm(x,y,this),nextId_));
  } else {
    worms_.emplace(nextId_, std::thread(HunterWorm(x,y,this),nextId_));
  }
  board_[x][y] = nextId_;
  wormTypes_[nextId_] = type;
  nextId_++;
}

void Board::update(int id, int oldX, int oldY, int newX, int newY) {
  int targetId = board_[newX][newY];
  if (targetId != 0 && targetId != id)
    killed_.insert(targetId);
  board_[oldX][oldY] = 0;
  board_[newX][newY] = id;
}

bool Board::checkKill(int id) {
  return killAll_ || killed_.find(id) != killed_.end();
}

void Board::killAll() {
  killAll_ = true;
}

void Board::clearDead() {
  for (int i = 0; i < (int)board_.size(); ++i)
    for (int j = 0; j < (int)board_[0].size(); ++j)
      if (killed_.find(board_[i][j]) != killed_.end())
        board_[i][j] = 0;
}
