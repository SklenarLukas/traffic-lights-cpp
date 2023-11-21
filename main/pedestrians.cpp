#include "pedestrians.h"

#include "esp_log.h"

const char *pedestriansWaitLed::TAG = "LED";
const char *pedestriansButton::TAG = "BUTTON";

pedestriansWaitLed::pedestriansWaitLed(gpio_num_t wait_pin, Mode wait_mode) : p_wait_pin(wait_pin), p_wait_mode(wait_mode)
{
    ESP_LOGW(TAG, "Creation of class, pin: %d", p_wait_pin);
    gpio_reset_pin(p_wait_pin);
    gpio_set_direction(p_wait_pin, GPIO_MODE_INPUT_OUTPUT);
    pedestriansWaitLedOff();
}

pedestriansWaitLed::~pedestriansWaitLed() {}

void pedestriansWaitLed::setWaitLedState(Mode p_new_mode)
{
    p_wait_mode = p_new_mode;
    if (p_wait_mode == Mode::ON)
    {
        pedestriansWaitLedOn();
    }
    else
    {
        pedestriansWaitLedOff();
    }
}

void pedestriansWaitLed::pedestriansWaitLedOff()
{
    gpio_set_level(p_wait_pin, p_wait_mode == Mode::OFF ? 0 : 1);
    ESP_LOGD(TAG, "Switching to OFF state, pin: %d", p_wait_pin);
}

void pedestriansWaitLed::pedestriansWaitLedOn()
{
    gpio_set_level(p_wait_pin, p_wait_mode == Mode::ON ? 1 : 0);
    ESP_LOGD(TAG, "Switching to ON state, pin: %d", p_wait_pin);
}

pedestriansButton::pedestriansButton(gpio_num_t button_pin) : p_button_pin(button_pin)
{
    ESP_LOGW(TAG, "Creation of class, pin: %d", p_button_pin);
    gpio_reset_pin(p_button_pin);
    gpio_set_direction(p_button_pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(p_button_pin, GPIO_PULLUP_ONLY);
}

pedestriansButton::~pedestriansButton() {}

bool pedestriansButton::pedestriansButtonUnpressed()
{
    return gpio_get_level(p_button_pin) == 1;
}
