#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/adc.h" 
    
#define BLINK_GPIO 33
    
    
/* void hello_task(void *pvParameter)
{
    
    while(1)
    {
        printf("Hello world!\n");
        vTaskDelay(700 / portTICK_RATE_MS);
    }
}*/
    
void blinky(void *pvParameter)
{
    
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
    
void AnalogRead() {

    int read_raw;
    adc2_config_channel_atten( ADC2_CHANNEL_5, ADC_ATTEN_11db );
    while(1){
        esp_err_t r = adc2_get_raw( ADC2_CHANNEL_5, ADC_WIDTH_12Bit, &read_raw);
        if ( r == ESP_OK ) {
            printf("ADC value: \n");            
            printf("%d\n", read_raw );
        } else if ( r == ESP_ERR_TIMEOUT ) {
            printf("ADC2 used by Wi-Fi.\n");
        }
        vTaskDelay(700 / portTICK_RATE_MS);
    }
}
 

void app_main()
{
    xTaskCreatePinnedToCore(&AnalogRead, "AnalogRead", 2048, NULL, 2, NULL, 0);
    //xTaskCreatePinnedToCore(&hello_task, "hello_task", 2048, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(&blinky, "blinky", 512,NULL,2,NULL, 1);
}