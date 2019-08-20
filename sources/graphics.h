#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <gtkmm.h>
#include "board.h"

class WormArea : public Gtk::DrawingArea {
 private:
  Board board_;
  bool debug_ = false;

 protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  void draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
      int x, int y, int rectangle_width, int rectangle_height, int id);

 public:
  WormArea(int width, int height);
  virtual ~WormArea() { }
  void force_redraw();
  void setDebug(bool debug) { debug_ = debug; }
};

class Graphics : public Gtk::Window {
 private:
  WormArea drawingArea_;
 public:
  // Seting up and running the application.
  static int createAndRun(int argc, char** argv,
      int width, int height, bool debug = false);

  Graphics(int width, int height, bool debug = false);
  virtual ~Graphics() { }
};

#endif // GRAPHICS_H_
