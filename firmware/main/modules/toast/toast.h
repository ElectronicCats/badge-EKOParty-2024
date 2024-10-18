#pragma once

#include <stdbool.h>
#include <stdio.h>

#define COOLDOWN_TIME_S 300
#define COOLDOWN_MEM "toast_cooldown"

typedef enum { WAITING_STATE, IN_PROGREES_STATE, FINISH_STATE } toast_states_t;

typedef struct {
  uint8_t state;
  uint8_t cooldown_time;
  volatile bool waiting;
} toast_ctx_t;

void toast_begin();