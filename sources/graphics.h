#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <gtkmm.h>
#include "board.h"

class WormArea : public Gtk::DrawingArea {
 private:
  Board board_;

 protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

 public:
  WormArea() : board_(100,100) { board_.addWorm(Lazy,0,0); board_.addWorm(Lazy,99,99); }
  virtual ~WormArea() { }
  void force_redraw();
};

class Graphics : public Gtk::Window {
 private:
  WormArea drawingArea_;
 public:
  // Seting up and running the application.
  static int createAndRun(int argc, char** argv);

  Graphics();
  virtual ~Graphics() { }
};

#endif // GRAPHICS_H_
