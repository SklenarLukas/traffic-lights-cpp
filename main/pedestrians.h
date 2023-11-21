#pragma once

#include "driver/gpio.h"

class pedestriansWaitLed
{
public:
    enum class Mode
    {
        OFF,
        ON
    };

private:
    gpio_num_t p_wait_pin = GPIO_NUM_0;
    Mode p_wait_mode;

    static const char *TAG;

public:
    pedestriansWaitLed(gpio_num_t wait_pin, Mode wait_mode = Mode::OFF);
    virtual ~pedestriansWaitLed();

public:
    void pedestriansWaitLedOn();
    void pedestriansWaitLedOff();
    void setWaitLedState(Mode p_new_mode);
};

class pedestriansButton
{

private:
    gpio_num_t p_button_pin = GPIO_NUM_0;

    static const char *TAG;

public:
    pedestriansButton(gpio_num_t button_pin);
    virtual ~pedestriansButton();

public:
    bool pedestriansButtonUnpressed();
};
