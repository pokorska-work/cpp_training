#include "worm.h"
#include "board.h"

void Worm::move() {
  int oldX = x_, oldY = y_;
  if (currDir_ == LEFT) x_--;
  else if (currDir_ == RIGHT) x_++;
  else if (currDir_ == UP) y_--;
  else if (currDir_ == DOWN) y_++;
  else std::cout << "Wrong direction: " << currDir_ << "\n";
  board_->update(id_,oldX,oldY,x_,y_);
}

void LazyWorm::run() {
  while (alive) {
    std::cout << "I'm at " << x_ << " " << y_ << "\n";
    // Pick waiting time between 0.1s and 1s.
    int delay = rand() % 901;
    std::this_thread::sleep_for(std::chrono::milliseconds(100 + delay));

    // Pick the direction - with probability 0.75 stay with current direction,
    // with probability 0.125 turn right and with 0.125 turn left.
    int dice = rand() % 8;
    if (dice == 0) { // turn right
      currDir_++;
      currDir_ %= 4;
    } else if (dice == 1) { // turn left
      (int)currDir_--;
      if (currDir_ < 0) currDir_ += 4;
    }
    this->move();
  }
}
