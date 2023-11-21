#pragma once

#include "driver/gpio.h"

class trafficLightsCars
{
public:
    enum Mode : char
    {
        CARS_STOP,
        CARS_START,
        CARS_RUN,
        CARS_STOP_RUN
    };

private:
    gpio_num_t c_red_pin = GPIO_NUM_0;
    gpio_num_t c_orange_pin = GPIO_NUM_0;
    gpio_num_t c_green_pin = GPIO_NUM_0;

    gpio_num_t p_stop_pin = GPIO_NUM_0;
    gpio_num_t p_run_pin = GPIO_NUM_0;

    Mode c_mode;

public:
    trafficLightsCars(gpio_num_t red_pin, gpio_num_t orange_pin, gpio_num_t green_pin, gpio_num_t stop_pin, gpio_num_t run_pin);
    virtual ~trafficLightsCars();

public:
    void carsStopped();
    void carsStarting();
    void carsRunning();
    void carsStoppingRunning();

    void pedestriansStop();
    void pedestriansRun();

    void setLights(int, int, int);
};
