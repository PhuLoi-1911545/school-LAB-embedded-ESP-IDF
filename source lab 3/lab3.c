#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#include "freertos/semphr.h"
#include "esp_err.h"



// bai 1
// static void task_1(void* args)
// {
//     while(1)
//     {
//         printf("\n L01 - Nhom 3 - TASK 1 \n");
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }

// static void task_2(void* args)
// {
//     while(1)
//     {
//         printf("\n L01 - Nhom 3 - TASK 2\n");	
//         vTaskDelay(pdMS_TO_TICKS(100));
//     }
// }

// static void task_3(void* args)
// {
//     while(1)
//     {
//         printf("\n L01 - Nhom 3 - TASK 3\n");
//         vTaskDelay(pdMS_TO_TICKS(100));	
//     }
// }

// void app_main(void) {
//     vTaskDelay(pdMS_TO_TICKS(100));

//     xTaskCreatePinnedToCore(task_2, "task 2", 1024, NULL, 0, NULL, 0);
//     xTaskCreatePinnedToCore(task_3, "task 3", 1024, NULL, 0, NULL, 0);
//     vTaskDelay(pdMS_TO_TICKS(4500));
//     xTaskCreatePinnedToCore(task_1, "task 1", 1024, NULL, 1, NULL, 0);
    
// }



//bai 2
// static void task_1(void* arg)
// {
//     while(1)
//     {
//         printf("\n L01 - Nhom 3 - TASK 1 \n");
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }

// static void task_2(void* arg)
// {
//     while(1)
//     {
//         printf("\n L01 - Nhom 3 - TASK 2\n");
//         vTaskDelay(pdMS_TO_TICKS(100));
//     }
// }

// static void task_3(void* arg)
// {
//     while(1)
//     {
//         printf("\n L01 - Nhom 3 - TASK 3\n");
//         vTaskDelay(pdMS_TO_TICKS(100));	
//     }
// }

// void app_main(void) {
//     vTaskDelay(pdMS_TO_TICKS(100));

//     xTaskCreatePinnedToCore(task_2, "task 2", 1024, NULL, 0, NULL, 0);
//     xTaskCreatePinnedToCore(task_3, "task 3", 1024, NULL, 0, NULL, 0);
//     vTaskDelay(pdMS_TO_TICKS(5000));
//     xTaskCreatePinnedToCore(task_1, "task 1", 1024, NULL, 1, NULL, 0);
    
// }



//bai 3
static void task_1(void* arg)
{
    while(1)
    {
        for (int j=0; j<3; j++)
        {
            printf("\n L01 - Nhom 3 - TASK 1 \n");
            for (int k=0; k<1000; k++)
            {
                for (int m=0; m<600; m++)
                {
                    __asm__ __volatile__("NOP");
                }
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void task_2(void* arg)
{
    while(1)
    {
        for (int j=0; j<3; j++)
        {
            printf("\n L01 - Nhom 3 - TASK 2 \n");
            for (int k=0; k<1000; k++)
            {
                for (int m=0; m<1000; m++)
                {
                    __asm__ __volatile__("NOP");
                }
            }
        }

        taskYield();
    }
}

static void task_3(void* arg)
{
    while(1)
    {
        for (int j=0; j<3; j++)
        {
            printf("\n L01 - Nhom 3 - TASK 3 \n");
            for (int k=0; k<1000; k++)
            {
                for (int m=0; m<1000; m++)
                {
                    __asm__ __volatile__("NOP");
                }
            }
        }
        
        taskYield();
    }
}

void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(100));

    xTaskCreatePinnedToCore(task_2, "task 2", 1024, NULL, 0, NULL, 0);
    xTaskCreatePinnedToCore(task_3, "task 3", 1024, NULL, 0, NULL, 0);
    vTaskDelay(pdMS_TO_TICKS(5000));
    xTaskCreatePinnedToCore(task_1, "task 1", 1024, NULL, 1, NULL, 0);
    
}