#include "graphics.h"

#include <iostream>

using Gtk::DrawingArea;

WormArea::WormArea() : board_(50,50) {
  for (int i = 0; i < 50; ++i) {
    board_.addWorm(Lazy,rand() % board_.getWidth(), rand() % board_.getHeight());
  }
  for (int i = 0; i < 20; ++i) {
    board_.addWorm(Hunter,rand() % board_.getWidth(), rand() % board_.getHeight());
  }
}

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
      if (board_.getWormType(board_.at(x,y)) == Hunter)
        cr->set_source_rgb(1.0,0.0,0.0);
      if (debug_) {
        this->draw_text(cr, x*fieldWidth + fieldWidth/2,
            y*fieldHeight + fieldHeight/2,
            fieldWidth, fieldHeight, board_.at(x,y));
      } else {
        cr->arc(x*fieldWidth + fieldWidth/2, y*fieldHeight + fieldHeight/2,
                std::min(fieldWidth,fieldHeight) / 2.5, 0.0, 2.0 * M_PI);
        cr->fill_preserve();
      }
      cr->stroke();
      cr->set_source_rgb(0.0,0.0,0.0);
    }
  }
  cr->restore();
  cr->stroke();

  force_redraw();

  return true;
}

void WormArea::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
    int x, int y, int rectangle_width, int rectangle_height, int id) {
  Pango::FontDescription font;
  font.set_family("Monospace");
  font.set_weight(Pango::WEIGHT_BOLD);
  auto layout = create_pango_layout(std::to_string(id));
  layout->set_font_description(font);

  int text_width;
  int text_height;

  //get the text dimensions (it updates the variables -- by reference)
  layout->get_pixel_size(text_width, text_height);

  // Position the text in (x,y)
  cr->move_to(x,y);

  layout->show_in_cairo_context(cr);
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
int Graphics::createAndRun(int argc, char** argv, bool debug) {
  auto app = Gtk::Application::create(argc, argv, "Worms");
  Graphics window(debug);
  return app->run(window);
}

Graphics::Graphics(bool debug) {
  set_title("Worms");
  set_default_size(1800,900);
  drawingArea_.setDebug(debug);
  add(drawingArea_);
  show_all_children();
  srand(time(nullptr));
}

