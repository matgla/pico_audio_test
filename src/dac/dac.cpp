#include "dac/dac.hpp"

#include <hardware/pwm.h>
#include <hardware/gpio.h>
#include <hardware/clocks.h>
#include <hardware/irq.h>

#include <cstdio>
#include <cmath>
#include <limits>

namespace pico_audio
{

constexpr int audio_pin_left = 2;
constexpr int audio_pin_right = 3;

constexpr float fs = 176400;
constexpr int samples_size = 44100;

uint16_t samples[samples_size];
uint32_t current_sample = 0;

float current_time = 0.0f;

uint8_t count = 0;

uint16_t sample = 0;

bool first = true;

void __isr __time_critical_func(pwm_handler)()
{
    int left_pin_slice = pwm_gpio_to_slice_num(audio_pin_left);

    uint16_t sample = samples[current_sample >> 2];

    float tp = (float)(sample >> 8);
    float sample_high = tp * (0.6 + 0.4 * tp / 256) + 0.015 * 256;
    tp = (float)(sample & 0xff);
    float sample_low = tp * (0.6 + 0.4 * tp / 256) + 0.015 * 256;

    if (sample_low > 255) sample_low = 255;
    if (sample_high > 255) sample_high = 255;

    pwm_set_both_levels(left_pin_slice, (uint8_t)sample_high, (uint8_t)sample_low);
    pwm_clear_irq(left_pin_slice);  

    if (first)
    {
        printf("S: %d, H: %d, L: %d\n", sample, (uint16_t)sample_high, (uint16_t)sample_low);
    }

    if (current_sample < (samples_size * 4) - 1)
    {
        ++current_sample;
    }
    else 
    {
        current_sample = 0;
    }

    if (current_sample == 5000)
    {
        first = false;
    }
}

DAC::DAC()
{
    for (int i = 0; i < samples_size; ++i)
    {
        samples[i] = 32767.0 * sin((float)i / fs * 2.0 * 3.14 * 1000.0) + 32768;
    }

    init_pwm(audio_pin_left);
    init_pwm(audio_pin_right);
}

void DAC::init_pwm(int pin)
{
    constexpr uint32_t default_samplerate = 176400;
    gpio_set_function(pin, GPIO_FUNC_PWM);
    int pin_slice = pwm_gpio_to_slice_num(pin);
    pwm_clear_irq(pin_slice);
    pwm_set_irq_enabled(pin_slice, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_handler);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    samplerate_pwm(default_samplerate, pin_slice);
    pwm_set_gpio_level(pin, 0);
}

void DAC::samplerate_pwm(uint32_t rate, int pin_slice)
{
    pwm_config config = pwm_get_default_config();
    constexpr uint32_t wrap = 255;

    const float div = static_cast<float>(clock_get_hz(clock_index::clk_sys)) 
        / static_cast<float>(wrap) 
        / static_cast<float>(rate);

    printf("DIV: %f\n", div);

    pwm_config_set_clkdiv(&config, div);
    pwm_config_set_wrap(&config, wrap);
    pwm_config_set_phase_correct(&config, true);
    pwm_init(pin_slice, &config, true);
}


void DAC::samplerate(uint32_t rate)
{

}

} // namespace pico_audio
