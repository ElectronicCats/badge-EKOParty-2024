#include "sounds.h"
#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 830
#define NOTE_A5 880
#define NOTE_C6  1047
#define NOTE_E6  1319
#define NOTE_F6  1397

static bool is_playing = false;

static int melody_notes[] = {
    NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_C6, NOTE_A5,
    NOTE_E6, NOTE_E6, NOTE_E6, NOTE_F6, NOTE_C6, NOTE_GS5, NOTE_F5, NOTE_C6, NOTE_A5
};

static int melody_times[] = {
    500, 500, 500, 350, 150, 500, 350, 150, 1000,
    500, 500, 500, 350, 150, 500, 350, 150, 1000
};

void play_sound(uint32_t note, uint32_t time) {
  buzzer_set_freq(note);
  buzzer_play_for(time);
  vTaskDelay(time / portTICK_PERIOD_MS);
}

void play_tango(){
  for(int i = 0; i < 100; i++){
    buzzer_set_freq(notes[i]);
    buzzer_play_for(times[i]);
    vTaskDelay(times[i] / portTICK_PERIOD_MS);
  }
  buzzer_stop();
  vTaskDelete(NULL);
}

void sounds_stop_music() {
  is_playing = false;
}

void sounds_play_music() {
  is_playing = true;
  xTaskCreate(play_tango, "play_sound", 4096, NULL, 5, NULL);
}