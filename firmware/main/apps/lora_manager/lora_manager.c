#include "esp_log.h"
#include <lora_manager.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"
#include "neopixels_events.h"
#include "stdint.h"
#include "sounds.h"
#include <string.h>
#include "general/general_screens.h"
#include "menus_module.h"
#include "screen_saver.h"

#define MAX_WORDS 10 
#define MAX_WORD_LENGTH 17
#define MAX_CHAR_PER_ENTRY 15

uint8_t buf[LORA_PACKET_LENGTH];

static general_menu_t item_menu;

void split_and_group_string(const char *str, char *result[]) {
    char *temp_str = strdup(str);
    char *token = strtok(temp_str, "_");
    int i = 0;

    result[i] = (char *)malloc(MAX_CHAR_PER_ENTRY * sizeof(char));
    result[i][0] = '\0';

    while (token != NULL && i < MAX_WORDS) {
      
        if (strlen(result[i]) + strlen(token) + 1 <= MAX_CHAR_PER_ENTRY) {
            if (strlen(result[i]) > 0) {
                strcat(result[i], " ");
            }
            strcat(result[i], token);
        } else {
            i++;
            result[i] = (char *)malloc(MAX_CHAR_PER_ENTRY * sizeof(char));
            result[i][0] = '\0';
            strcat(result[i], token);
        }

        token = strtok(NULL, "_");
    }
    result[++i] = NULL;
    item_menu.menu_count = i;
    free(temp_str);
}

static void exit_notification(){
   neopixel_events_stop_event();
   menus_module_reset();
}

static void alert_scrolling(char *message){
   char *cadena[MAX_WORDS];

   item_menu.menu_items = malloc(MAX_WORDS * sizeof(char *));

   split_and_group_string(message, cadena);
   for(int i = 0; i < MAX_WORDS; i++){
      if(cadena[i] == NULL){
         break;
      }
      item_menu.menu_items[i] = cadena[i];
   }
   item_menu.menu_level = GENERAL_TREE_APP_INFORMATION;
   general_register_scrolling_menu(&item_menu);
   general_screen_display_scrolling_text_handler(exit_notification);
}

static void lora_command_handler(){
   ESP_LOGI("lora", "Received: %s", buf);
   char *command = strtok((char *)buf, ":");
   if(command == NULL){
      ESP_LOGE("lora", "Error parsing command execute");
      return;
   }

   if(strcmp(command, "PLAY") == 0){
      char *note_str = strtok(NULL, ":");
      char *duration_str = strtok(NULL, ":");
      if (note_str != NULL && duration_str != NULL) {
         uint32_t note = atoi(note_str);
         uint32_t duration = atoi(duration_str);
         play_sound(note, duration);
      }
   } else if(strcmp(command, "STOP") == 0){
      sounds_stop_music();
   } else if(strcmp(command, "NOTIFY") == 0){
      char *notification_str = strtok(NULL, ":");
      screen_saver_stop();
      neopixel_events_run_event(neopixel_message_notify);
      alert_scrolling(notification_str);
   }

}

void task_rx(void *p)
{
   int x;
   for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
         x = lora_receive_packet(buf, sizeof(buf));
         buf[x] = 0;
         lora_receive();
         lora_command_handler();
      }
      vTaskDelay(1);
   }
}

void lora_module_begin()
{
   uint8_t err = lora_init();
   if(err != 1){
      ESP_LOGE("lora", "Error initializing lora module");
      return;
   }
   lora_set_frequency(915e6);
   lora_set_spreading_factor(8);
   lora_set_bandwidth(125e3);
   lora_set_coding_rate(4);
   lora_set_preamble_length(8);
   lora_enable_crc();
   xTaskCreate(&task_rx, "task_rx", 2048, NULL, 5, NULL);
}




