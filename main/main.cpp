#include "pedestrians.h"
#include "traffic_lights.h"

#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "TRAFFIC LIGHTS";

const TickType_t TIME_WAITING = 5000;

static const gpio_num_t CARS_RED = GPIO_NUM_2;
static const gpio_num_t CARS_ORANGE = GPIO_NUM_4;
static const gpio_num_t CARS_GREEN = GPIO_NUM_16;

static const gpio_num_t PEDESTRIANS_WHITE_LED = GPIO_NUM_18;
static const gpio_num_t PEDESTRIANS_RED = GPIO_NUM_17;
static const gpio_num_t PEDESTRIANS_GREEN = GPIO_NUM_5;

static const gpio_num_t BUTTON = GPIO_NUM_15;

extern "C"
{
    void app_main(void)
    {
        ESP_LOGI(TAG, "Start of main");
        esp_log_level_set("*", ESP_LOG_DEBUG);

        pedestriansButton *button = new pedestriansButton(BUTTON);
        pedestriansWaitLed *white = new pedestriansWaitLed(PEDESTRIANS_WHITE_LED, pedestriansWaitLed::Mode::OFF);
        trafficLightsCars *trafficLights = new trafficLightsCars(CARS_RED, CARS_ORANGE, CARS_GREEN, PEDESTRIANS_RED, PEDESTRIANS_GREEN);

        while (1)
        {
            while (button->pedestriansButtonUnpressed())
            {
                trafficLights->carsRunning();
                vTaskDelay(1);
            }
            white->setWaitLedState(pedestriansWaitLed::Mode::ON);
            vTaskDelay(TIME_WAITING / portTICK_PERIOD_MS);
            trafficLights->carsStoppingRunning();
            trafficLights->carsStopped();
            white->setWaitLedState(pedestriansWaitLed::Mode::OFF);
            trafficLights->pedestriansRun();
            trafficLights->pedestriansStop();
            trafficLights->carsStarting();
        }
    }
}
