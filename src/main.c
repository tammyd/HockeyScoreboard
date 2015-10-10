#include <pebble.h>

#include "helpers.h"
#include "teams.h"

static Window      *s_main_window;        // main window
static TextLayer   *s_conditions_layer;   // text layer displaying conditions
static TextLayer   *s_hour_layer0;        // text layer displaying hours
static TextLayer   *s_min_layer0;         // text layer displaying minutes
static TextLayer   *s_hour_layer1;        // text layer displaying hours
static TextLayer   *s_min_layer1;         // text layer displaying minutes
static TextLayer   *s_colon_layer;        // text layer displaying colon
static TextLayer   *s_date_layer;         // text layer
static TextLayer   *s_temperature_layer;  // text layer displaying temperature
static GFont        s_time_font;          // time display font
static GFont        s_weather_font;       // weather display font
static GFont        s_date_font;          // date display font
static GFont        s_colon_font;         // time colon display font
static GBitmap     *s_background_image;   // background image
static Layer       *s_background_layer;   // background image container

enum DataKeys {
  KEY_TEMPERATURE = 0,
  KEY_CONDITIONS = 1,
  KEY_CONFIG_TEAM = 2,
  KEY_CONFIG_TEMP_UNIT_F = 3
};

enum Teams {
  VAN = 0,
  CGY = 1
};

typedef struct {
  bool tempC;
  int team;
  GColor8 textColor;
} __attribute__((__packed__)) SettingsData;

SettingsData settings = {
  .tempC = true,
  .team = VAN
};

static void configure_team_settings() {
  switch(settings.team) {
    default:
    case VAN:
      settings.textColor = GColorWhite; break;
    case CGY:
      settings.textColor = GColorWhite; break;
  }
}


// define all the fonts used
static void load_fonts() {
  switch(settings.team) {
    default:
    case VAN:
      VAN_load_fonts(&s_time_font, &s_date_font, &s_weather_font); break;
    case CGY:
      CGY_load_fonts(&s_time_font, &s_date_font, &s_weather_font); break;
  }

  s_colon_font = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
}


static void draw_background(Layer *layer, GContext *ctx) {

  switch(settings.team) {
    default:
    case VAN:
      VAN_draw_background(layer, ctx); break;
    case CGY:
      CGY_draw_background(layer, ctx); break;
  }
}

// build up the pieces that make up background layer
static void create_background_layer() {
  s_background_layer = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(s_background_layer, draw_background);
}

static void create_layers() {
  create_background_layer();
  s_conditions_layer = text_layer_create(GRect(18, 126, 108, 50));
  s_temperature_layer = text_layer_create(GRect(22, 126, 30, 50)); //GRect: x,y,w,h
  
  //time layers
  s_hour_layer0 = text_layer_create(GRect(22, 10, 30, 70)); //GRect: x,y,w,h
  s_hour_layer1 = text_layer_create(GRect(45, 10, 30, 70)); //GRect: x,y,w,h
  s_min_layer0 = text_layer_create(GRect(76, 10, 30, 70));
  s_min_layer1 = text_layer_create(GRect(99, 10, 30, 70));
  s_colon_layer = text_layer_create(GRect(68, 30, 6, 70));
  
  s_date_layer = text_layer_create(GRect(0, 88, 144, 30));
}


// build up the pieces that display the weather information
static void define_weather_layer() {
  text_layer_set_background_color(s_conditions_layer, GColorClear);
  text_layer_set_text_color(s_conditions_layer, settings.textColor);
  text_layer_set_text_alignment(s_conditions_layer, GTextAlignmentRight);
  text_layer_set_font(s_conditions_layer, s_weather_font);
  text_layer_set_text(s_conditions_layer, "    ");
}

static void define_temperature_layer() {
  text_layer_set_background_color(s_temperature_layer, GColorClear);
  text_layer_set_text_color(s_temperature_layer, settings.textColor);
  text_layer_set_text_alignment(s_temperature_layer, GTextAlignmentLeft);
  text_layer_set_font(s_temperature_layer, s_weather_font);
  text_layer_set_text(s_temperature_layer, "    ");
}

// build up the pieces that display the time information
static void define_time_layer() {
  
  text_layer_set_background_color(s_hour_layer0, GColorClear);
  text_layer_set_background_color(s_hour_layer1, GColorClear);
  text_layer_set_background_color(s_min_layer0, GColorClear);
  text_layer_set_background_color(s_min_layer1, GColorClear);
  text_layer_set_text_color(s_hour_layer0, settings.textColor);
  text_layer_set_text_color(s_hour_layer1, settings.textColor);
  text_layer_set_text_color(s_min_layer0, settings.textColor);
  text_layer_set_text_color(s_min_layer1, settings.textColor);
  text_layer_set_text(s_hour_layer0, " ");
  text_layer_set_text(s_hour_layer1, " ");
  text_layer_set_text(s_min_layer0, "  ");
  text_layer_set_text(s_min_layer1, "  ");
  text_layer_set_font(s_hour_layer0, s_time_font);
  text_layer_set_font(s_hour_layer1, s_time_font);
  text_layer_set_font(s_min_layer0, s_time_font);
  text_layer_set_font(s_min_layer1, s_time_font);
  text_layer_set_text_alignment(s_hour_layer0, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_hour_layer1, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_min_layer0, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_min_layer1, GTextAlignmentLeft);

 
  text_layer_set_background_color(s_colon_layer, GColorClear);
  text_layer_set_text_color(s_colon_layer, settings.textColor);
  text_layer_set_font(s_colon_layer, s_colon_font);
  text_layer_set_text(s_colon_layer, ":");
  text_layer_set_text_alignment(s_colon_layer, GTextAlignmentCenter);

}

// build up the pieces that display the date information
static void define_date_layer() {
  
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, settings.textColor);
  text_layer_set_text(s_date_layer, "... ... ..");
  text_layer_set_font(s_date_layer, s_date_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
}

static void define_layers() {
  define_weather_layer();
  define_temperature_layer();
  define_time_layer();
}


// update the date text
static void update_date() {
  APP_LOG(APP_LOG_LEVEL_INFO, "update_date()");
  // build and populate the time structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char date_buffer[] = "WED JUN 30"; //using this as a placeholder example date

  //update the date's string buffer with formatted date
  strftime(date_buffer, sizeof("WED JUN 30"), "%a %b %d", tick_time);
  text_layer_set_text(s_date_layer, date_buffer);
}

static void _setNumberLayerAlignment(char *value, TextLayer *layer) {
  int ival = atoi(value);
  if (ival == 1) {
    text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  } else {
    text_layer_set_text_alignment(layer, GTextAlignmentLeft);
  }
}
static void _setLayerAlignment(char *hour0, char *hour1, char *min0, char *min1) {
  _setNumberLayerAlignment(hour0, s_hour_layer0);
  _setNumberLayerAlignment(hour1, s_hour_layer1);
  _setNumberLayerAlignment(min0, s_min_layer0);
  _setNumberLayerAlignment(min1, s_min_layer1);
}

static void update_time() {
  APP_LOG(APP_LOG_LEVEL_INFO, "update_time()");
  // build and populate the time structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Create 2 long-lived buffers for the hour and min
  static char hour_buffer[] = "00";
  static char min_buffer[] = "00";

  //update the hour and min buffers with formatted values from the time strucure
  if (!clock_is_24h_style()) {
    strftime(hour_buffer, sizeof("00"), "%I", tick_time);
  } else {
    strftime(hour_buffer, sizeof("00"), "%H", tick_time);
  }
  strftime(min_buffer, sizeof("00"), "%M", tick_time);

  static char hour0[] = "0";
  static char hour1[] = "0";
  static char min0[] = "0";
  static char min1[] = "0";
  strncpy(hour0, hour_buffer, 1);
  strncpy(hour1, hour_buffer+1, 1);
  strncpy(min0, min_buffer, 1);
  strncpy(min1, min_buffer+1, 1);

  //update the display's hour and min layers with the formatted values
  _setLayerAlignment(hour0, hour1, min0, min1);
  text_layer_set_text(s_hour_layer0, hour0);
  text_layer_set_text(s_hour_layer1, hour1);
  text_layer_set_text(s_min_layer0, min0);
  text_layer_set_text(s_min_layer1, min1);
}


static void build_team_layout() {
  configure_team_settings();
  load_fonts();
  define_layers();
}


// Load up the main window
static void main_window_load(Window *window) {
  create_layers();
  build_team_layout();

  // Add each layer as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), s_background_layer);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_hour_layer0));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_hour_layer1));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_min_layer0));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_min_layer1));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_colon_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_conditions_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_temperature_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_temperature_layer));
}

// Cleanup time data structures
static void unload_time_layer() {
  text_layer_destroy(s_hour_layer0);
  text_layer_destroy(s_hour_layer1);
  text_layer_destroy(s_min_layer0);
  text_layer_destroy(s_min_layer1);
  text_layer_destroy(s_colon_layer);
  fonts_unload_custom_font(s_time_font);
}

static void unload_temperature_layer() {
  text_layer_destroy(s_temperature_layer);
  fonts_unload_custom_font(s_weather_font);
}

// Cleanup background data structures
static void unload_background_layer() {
  // bitmap_layer_destroy(s_background_layer);
  layer_destroy(s_background_layer);
  gbitmap_destroy(s_background_image);
}

// Cleanup weather data structures
static void unload_weather_layer() {
  text_layer_destroy(s_conditions_layer);
  fonts_unload_custom_font(s_weather_font);
}

// Cleanup date data structures
static void unload_date_layer() {
  text_layer_destroy(s_date_layer);
  fonts_unload_custom_font(s_date_font);
}

// Cleanup the main window's data structures
static void main_window_unload(Window *window) {
  unload_time_layer();
  unload_background_layer();
  unload_weather_layer();
  unload_date_layer();
  unload_temperature_layer();
}

static void update_weather() {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);

  // Send the message!
  app_message_outbox_send();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  update_date();

  // Get weather update every 10 minutes
  if(tick_time->tm_min % 10 == 0) {
    update_weather();
  }
}

static int convert_team_to_enum(char *team) {
  if (strcmp(team,"VAN") != 0) {
    return VAN;
  }
  if (strcmp(team,"CGY") != 0) {
    return CGY;
  }

  return 0;
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
  static char temperature_buffer[8];
  static char conditions_buffer[32];
  static int temperature = 0;

  bool updateWeather = false;

  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
      case KEY_TEMPERATURE:
        temperature = (int)t->value->int32;
        updateWeather = true;
        break;
      case KEY_CONDITIONS:
        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
        text_layer_set_text(s_conditions_layer, conditions_buffer);
        break;
      case KEY_CONFIG_TEMP_UNIT_F:
        settings.tempC = !(bool)t->value->int32;
        updateWeather = true;
        break;
      case KEY_CONFIG_TEAM:
        settings.team = convert_team_to_enum(t->value->cstring);
        build_team_layout();
        break;
      default:
        APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
        break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }

  if (updateWeather) {
    if (settings.tempC) {
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%dC", temperature);
    } else {
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%dF", temperature);
    }
    text_layer_set_text(s_temperature_layer, temperature_buffer);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
