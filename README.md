# Description

Reacts to switching the joystick stick switch.

## Principle of work

The input receives a PWM signal from an RC receiver. For different stick positions there will be different duty cycle. By measuring its duration, you can determine the position of the stick and send a signal to the MC output.

# Hardware

Since my option was needed to turn on the LED backlight, I do not use external power and a powerful transistor. I also needed only one position.

# Firwmware

SDCC is used for compilation. You also need STM8S_SPL from ST - a library for working with peripherals.

## How to flash

I use stm8flash for flash.

First of all, you need to configure Option bytes for hardware. For capturing, the 1st channel of the 1st timer is used (Channel 1 TIM1).

```bash
echo -ne '\x00\x00\xff\x01\xfe\x00\xff\x00\xff\x00\xff' > opt.bin
stm8flash -c stlinkv2 -p stm8s103f3 -s opt -w opt.bin
```

This line activates alternative functions of the leg we need: Port C5 alternate function = TIM2_CH1; port C6 alternate function =TIM1_CH1; port C7 alternate function = TIM1_CH2.

Then we are already flashing the firmware itself (firmware.bin). Here you can already use: make upload, or manually download stm8flash.

```bash
./stm8flash -c stlinkv2 -p stm8s003f3 -w firmware.ihx
```
