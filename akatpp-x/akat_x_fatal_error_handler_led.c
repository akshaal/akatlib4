X_FATAL_ERROR_HANDLER$() {
    cli();

    FUNCTION$(void delay_approx300ms()) {
        for (u16 i = 0; i < 10000; i++) {
            akat_delay_us(30);
        }
    }

    while(1) {
        for (u8 i = 0; i < code; i++) {
            ${gpio_name}.set(1);
            delay_approx300ms();
            ${gpio_name}.set(0);
            delay_approx300ms();
        }

        delay_approx300ms();
        delay_approx300ms();
    }
}
