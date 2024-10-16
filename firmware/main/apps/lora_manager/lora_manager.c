#include "esp_log.h"
#include <lora_manager.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lora.h"
#include "neopixels_events.h"

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
         // neopixel_events_run_event(neopixel_message_notify);
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




