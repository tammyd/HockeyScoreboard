#include "helpers.h"

void draw_box(Layer *layer, GContext *ctx, int x_offset, int y_offset, int stroke) {
  GRect bounds = layer_get_bounds(layer);
  for (int i = 0; i < stroke; i++) {
    graphics_draw_rect(ctx, GRect(x_offset + i, y_offset + i, bounds.size.w - 2*(x_offset + i), bounds.size.h - 2*(y_offset + i)));
  }
}