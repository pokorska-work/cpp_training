#include "graphics.h"

#include <iostream>

using Gtk::DrawingArea;

bool WormArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  const int bWidth = board_.getWidth();
  const int bHeight = board_.getHeight();

  const int fieldWidth = width / bWidth;
  const int fieldHeight = height / bHeight;

  cr->save();
  cr->set_source_rgb(0.0,0.0,0.0);
  for (int y = 0; y < bHeight; ++y) {
    for (int x = 0; x < bWidth; ++x) {
      if (!board_.isWormAt(x,y)) continue;
      cr->arc(x*fieldWidth + fieldWidth/2, y*fieldHeight + fieldHeight/2,
              std::min(fieldWidth,fieldHeight) / 2.5, 0.0, 2.0 * M_PI);
      cr->fill_preserve();
    }
  }
  cr->restore();
  cr->stroke();

  force_redraw();

  return true;
}

void WormArea::force_redraw()
{
  auto win = get_window();
  if (win)
  {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
}

// Static function to set up and run the application.
int Graphics::createAndRun(int argc, char** argv) {
  auto app = Gtk::Application::create(argc, argv, "Worms");
  Graphics window;
  return app->run(window);
}

Graphics::Graphics() {
  set_title("Worms");
  set_default_size(1800,900);
  add(drawingArea_);
  show_all_children();
}

