#pragma once
#include "esp_random.h"
#include <stdbool.h>
#include <stdio.h>

typedef void (*neopixel_event)(void);
typedef struct {
  neopixel_event animation;
  volatile bool is_running;
} neopixel_animation_ctx_t;

void neopixel_scanning_event();
void neopixel_events_stop_event();
void neopixel_events_run_event(neopixel_event event);

void neopixel_llamaneitor_init();
void neopixel_message_notify();