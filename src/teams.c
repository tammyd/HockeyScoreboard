#include "teams.h"

void draw_seperator_lines(Layer *layer, GContext *ctx) {
  graphics_draw_line(ctx, GPoint(14,88), GPoint(129,88));
  graphics_draw_line(ctx, GPoint(14,125), GPoint(129,125));
}


void VAN_draw_background(Layer *layer, GContext *ctx) {
	
	//setup
  GRect bounds = layer_get_bounds(layer);
  GColor blue = GColorFromRGB(13, 23, 154);
  GColor green = GColorFromRGB(30, 70, 13);
  
  
  //set the background color
  graphics_context_set_fill_color(ctx, blue);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  //draw white stripes
  graphics_context_set_stroke_color(ctx, GColorWhite);
  draw_box(layer, ctx, 4, 4, 2);
  draw_box(layer, ctx, 12, 12, 2);
  draw_seperator_lines(layer, ctx);
  
  //draw green stripes
  graphics_context_set_stroke_color(ctx, green);
  draw_box(layer, ctx, 6, 6, 6);
	
}

void VAN_load_fonts(GFont *time_font, GFont *date_font, GFont *weather_font) {
  *time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NHL_VAN_64));
  *date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NHL_VAN_28));
  *weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NHL_VAN_22));
  
}

void CGY_draw_background(Layer *layer, GContext *ctx) {
	
	//setup
  GRect bounds = layer_get_bounds(layer);
  GColor gold = GColorFromRGB(228, 146, 43);
  GColor red = GColorFromRGB(152, 28, 23);
  
  
  //set the background color
  graphics_context_set_fill_color(ctx, red);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  //draw black stripes
  graphics_context_set_stroke_color(ctx, GColorBlack);
  draw_box(layer, ctx, 4, 4, 4);
  draw_box(layer, ctx, 12, 12, 2);
  draw_seperator_lines(layer, ctx);
  
  //draw gold stripe
  graphics_context_set_stroke_color(ctx, gold);
  draw_box(layer, ctx, 8, 8, 2);
  
  //draw white stripe
  graphics_context_set_stroke_color(ctx, GColorWhite);
  draw_box(layer, ctx, 10, 10, 2);
	
}

void CGY_load_fonts(GFont *time_font, GFont *date_font, GFont *weather_font) {
  *time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NHL_CGY_60));
  *date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NHL_CGY_26));
  *weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_NHL_CGY_22));
  
}
