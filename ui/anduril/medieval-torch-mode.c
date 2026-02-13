#ifdef USE_MEDIEVAL_TORCH_MODE

void medieval_torch_iter(void);

static uint8_t base_level;
static uint8_t aggression = 40;
static uint16_t flame_wave = 0;

uint8_t medieval_torch_state(Event event, uint16_t arg)
{
    if (event == EV_enter_state) {
        base_level = memorized_level;
        if (base_level < 5) base_level = 5;
        set_level(base_level);
        return EVENT_HANDLED;
    }

    // 1C → Off
    else if (event == EV_1click) {
        set_state(off_state, 0);
        return EVENT_HANDLED;
    }

    // Hold → adjust brightness
    else if (event == EV_click1_hold) {
        base_level += 1;
        if (base_level > MAX_LEVEL) base_level = MAX_LEVEL;
        set_level(base_level);
        return EVENT_HANDLED;
    }

    else if (event == EV_click2_hold) {
        if (base_level > 1) base_level -= 1;
        set_level(base_level);
        return EVENT_HANDLED;
    }

    // Tick = simulate flame
    else if (event == EV_tick) {
        medieval_torch_iter();
        return EVENT_HANDLED;
    }

    return EVENT_NOT_HANDLED;
}

//void medieval_torch_iter(void)
{
    int16_t brightness = base_level;

    // slow breathing wave
    flame_wave += 7;
    brightness += (triangle_wave(flame_wave) >> 3);

    // micro flicker
    if ((pseudo_rand() & 0x03) == 0)
        brightness += pseudo_rand() % (aggression / 4);

    // temperature reactive flare
#ifdef USE_THERMAL_REGULATION
    if (temperature > 45) {
        brightness += pseudo_rand() % (aggression / 2);
    }
#endif

    // gust flare
    if ((pseudo_rand() & 0x1F) == 0) {
        brightness += aggression;
    }

    if (brightness > MAX_LEVEL)
        brightness = MAX_LEVEL;

    if (brightness < 1)
        brightness = 1;

    set_level(brightness);
}

#endif
