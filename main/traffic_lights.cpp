#include "traffic_lights.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <initializer_list>

const TickType_t TIME_ORANGE_CARS = 2000;
const TickType_t TIME_CARS_TRANSIT = 1500;
const TickType_t TIME_GREEN_PEDS = 5000;
const TickType_t TIME_PEDS_TRANSIT = 3000;
const TickType_t TIME_RED_ORANGE = 1000;

trafficLightsCars::trafficLightsCars(gpio_num_t red, gpio_num_t orange, gpio_num_t green, gpio_num_t stop, gpio_num_t run)
    : c_red_pin(red), c_orange_pin(orange), c_green_pin(green), p_stop_pin(stop), p_run_pin(run)
{
    for (gpio_num_t pin : {c_red_pin, c_orange_pin, c_green_pin, p_stop_pin, p_run_pin})
    {
        gpio_reset_pin(pin);
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    }
}

trafficLightsCars::~trafficLightsCars() {}

void trafficLightsCars::setLights(int red, int orange, int green)
{
    gpio_set_level(c_red_pin, red);
    gpio_set_level(c_orange_pin, orange);
    gpio_set_level(c_green_pin, green);
}

void trafficLightsCars::carsRunning()
{
    setLights(0, 0, 1);
    gpio_set_level(p_stop_pin, 1);
}

void trafficLightsCars::carsStopped()
{
    setLights(1, 0, 0);
    vTaskDelay(TIME_CARS_TRANSIT / portTICK_PERIOD_MS);
}

void trafficLightsCars::carsStarting()
{
    setLights(1, 1, 0);
    vTaskDelay(TIME_RED_ORANGE / portTICK_PERIOD_MS);
}

void trafficLightsCars::carsStoppingRunning()
{
    setLights(0, 1, 0);
    vTaskDelay(TIME_ORANGE_CARS / portTICK_PERIOD_MS);
}

void trafficLightsCars::pedestriansStop()
{
    gpio_set_level(p_stop_pin, 1);
    gpio_set_level(p_run_pin, 0);
    vTaskDelay(TIME_PEDS_TRANSIT / portTICK_PERIOD_MS);
}

void trafficLightsCars::pedestriansRun()
{
    gpio_set_level(p_stop_pin, 0);
    gpio_set_level(p_run_pin, 1);
    vTaskDelay(TIME_GREEN_PEDS / portTICK_PERIOD_MS);
}
