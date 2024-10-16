#pragma once

#include <stdio.h>

typedef enum { WAITING_STATE, IN_PROGREES_STATE, FINISH_STATE } toast_states_t;

typedef struct {
  uint8_t state;
  uint8_t cooldown_time;
} toast_ctx_t;

void toast_begin();