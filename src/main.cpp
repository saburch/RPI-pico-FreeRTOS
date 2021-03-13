#include "FreeRTOS.h"
#include "task.h"
#include "GPIO.hpp"
#include "stdio.h"
#include "pico/stdlib.h"

// Constants
const uint16_t      STACK_SIZE      = 512; // bytes
const TickType_t    ON_OFF_DURATION = 500; // ms
const int           LED_PIN         = 25;
const char* const   TASK_NAME       = "Blink Task";

[[noreturn]]
void vTaskCode(void * pvParameters)
{
    (void) pvParameters;
    pico_cpp::GPIO_Pin ledPin(LED_PIN,pico_cpp::PinType::Output);

    for (;;)
    {
        printf("Hi!\n");
        ledPin.set_high();
        vTaskDelay(ON_OFF_DURATION);
        ledPin.set_low();
        vTaskDelay(ON_OFF_DURATION);
    }
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    stdio_init_all();

    TaskHandle_t taskHandle = nullptr;
    const BaseType_t status = xTaskCreate(
                vTaskCode,
                TASK_NAME,
                STACK_SIZE,
                nullptr,
                tskIDLE_PRIORITY,
                &taskHandle
            );

    //if (status != pdFREERTOS_ERRNO_NONE)
    //    return -1;

    // Start the execution
    vTaskStartScheduler();

    for (;;)
    {
        // Whe should never enter this loop, since vTaskStartScheduler never returns
        configASSERT(0);
    }
}
