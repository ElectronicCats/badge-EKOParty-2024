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

uint8_t buf[32];

void task_rx(void *p)
{
   int x;
   for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
         x = lora_receive_packet(buf, sizeof(buf));
         buf[x] = 0;
         printf("Received:");
         for(int i=0; i<x; i++) {
            printf(" %02x", buf[i]);
         }
         ESP_LOGI("lora", "Received: %s", buf);
         printf("\n");
         lora_receive();
         // Check if play sound command is present.
         // If 'play_sound' is received, play the music.

         char *command = strtok((char *)buf, ":");
         if (command != NULL && strcmp(command, "play") == 0) {
            // Extraer los parámetros
            char *note_str = strtok(NULL, ":");
            char *duration_str = strtok(NULL, ":");

            if (note_str != NULL && duration_str != NULL) {
               // Convertir los parámetros a enteros
               uint32_t note = atoi(note_str);
               uint32_t duration = atoi(duration_str);

               // Llamar a la función para tocar el sonido
               play_sound(note, duration);
            }
         }
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
   lora_set_spreading_factor(7);
   lora_set_bandwidth(125e3);
   lora_set_coding_rate(4);
   lora_set_preamble_length(8);
   lora_enable_crc();
   xTaskCreate(&task_rx, "task_rx", 2048, NULL, 5, NULL);
}




