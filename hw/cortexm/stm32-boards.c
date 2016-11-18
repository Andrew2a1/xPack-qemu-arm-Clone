/*
 * STM32 boards emulation.
 *
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <hw/cortexm/board.h>
#include <hw/cortexm/stm32-mcus.h>
#include <hw/cortexm/gpio-led.h>
#include <hw/cortexm/button-gpio.h>
#include <hw/cortexm/button-reset.h>
#include <hw/cortexm/helper.h>

/*
 * This file defines several STM32 boards.
 * Where available, the board names follow the CMSIS Packs names.
 */

/* ----- ST STM32F4-Discovery ----- */

static GPIOLEDInfo stm32f4_discovery_leds_info[] = {
    {
        .name = "green-led",
        .active_low = false,
        .colour_message = "Green",
        .x = 258,
        .y = 218,
        .w = 8,
        .h = 10,
        .gpio_path = "/machine/mcu/stm32/gpio[d]",
        .port_bit = 12, },
    {
        .name = "orange-led",
        .active_low = false,
        .colour_message = "Orange",
        .x = 287,
        .y = 246,
        .w = 8,
        .h = 10,
        .gpio_path = "/machine/mcu/stm32/gpio[d]",
        .port_bit = 13, },
    {
        .name = "red-led",
        .active_low = false,
        .colour_message = "Red",
        .x = 258,
        .y = 274,
        .w = 8,
        .h = 10,
        .gpio_path = "/machine/mcu/stm32/gpio[d]",
        .port_bit = 14, },
    {
        .name = "blue-led",
        .active_low = false,
        .colour_message = "Blue",
        .x = 230,
        .y = 246,
        .w = 8,
        .h = 10,
        .gpio_path = "/machine/mcu/stm32/gpio[d]",
        .port_bit = 15, },
    { }, /**/
};

static ButtonGPIOInfo stm32f4_discovery_buttons_user_info[] = {
    {
        .name = "user",
        .x = 262,
        .y = 164,
        .w = 40,
        .h = 40,

        .active_low = false,
        .gpio_path = "/machine/mcu/stm32/gpio[a]",
        .port_bit = 0, },
    { }, /**/
};

static ButtonResetInfo stm32f4_discovery_button_reset_info = {
    .x = 262,
    .y = 324,
    .w = 40,
    .h = 40 };

static void stm32f4_discovery_board_init_callback(MachineState *machine)
{
    CortexMBoardState *board = CORTEXM_BOARD_STATE(machine);

    cortexm_board_greeting(board);
    BoardGraphicContext *board_graphic_context =
            cortexm_board_init_graphic_image(board, "STM32F4-Discovery.jpg");

    {
        /* Create the MCU. */
        Object *mcu = cm_object_new_mcu(machine, TYPE_STM32F407VG);

        /* Set the board specific oscillator frequencies. */
        cm_object_property_set_int(mcu, 8000000, "hse-freq-hz"); /* 8.0 MHz */
        cm_object_property_set_int(mcu, 32768, "lse-freq-hz"); /* 32 kHz */

        cm_object_realize(mcu);
    }

    Object *peripheral = cm_container_get_peripheral();
    /* Create board LEDs. */
    gpio_led_create_from_info(peripheral, stm32f4_discovery_leds_info,
            board_graphic_context);

    if (board_graphic_context != NULL) {
        /* Create board buttons. */
        button_reset_create_from_info(peripheral,
                &stm32f4_discovery_button_reset_info, board_graphic_context);
        button_gpio_create_from_info(peripheral,
                stm32f4_discovery_buttons_user_info, board_graphic_context);
    }
}

static void stm32f4_discovery_board_class_init_callback(ObjectClass *oc,
        void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = "ST Discovery kit for STM32F407/417 lines";
    mc->init = stm32f4_discovery_board_init_callback;
}

static const TypeInfo stm32f4_discovery_machine = {
    .name = BOARD_TYPE_NAME("STM32F4-Discovery"),
    .parent = TYPE_CORTEXM_BOARD,
    .class_init = stm32f4_discovery_board_class_init_callback, };

#if 0

static void stm32f4_discovery2_board_init_callback(MachineState *machine)
{
    CortexMBoardState *board = CORTEXM_BOARD_STATE(machine);

    cortexm_board_greeting(board);

    {
        /* Create the MCU */
        Object *mcu = cm_object_new_mcu(machine, TYPE_STM32F407VG);

        /* Set the board specific oscillator frequencies. */
        cm_object_property_set_int(mcu, 8000000, "hse-freq-hz"); /* 8.0 MHz */
        cm_object_property_set_int(mcu, 32768, "lse-freq-hz"); /* 32 kHz */

        cm_object_realize(mcu);
    }

    cortexm_board_init_graphic_image(board, "STM32F4-Discovery.png");
    Object *peripheral = cm_container_get_peripheral();
    gpio_led_create_from_info(peripheral, stm32f4_discovery_leds_info,
            &(board->graphic_context));
}

static void stm32f4_discovery2_board_class_init_callback(ObjectClass *oc,
        void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = "ST Discovery kit for STM32F407/417 lines";
    mc->init = stm32f4_discovery2_board_init_callback;
}

static const TypeInfo stm32f4_discovery2_machine = {
    .name = BOARD_TYPE_NAME("STM32F4-Discovery2"),
    .parent = TYPE_CORTEXM_BOARD,
    .class_init = stm32f4_discovery2_board_class_init_callback,};

#endif

/* ----- ST STM32F429I-Discovery ----- */

static GPIOLEDInfo stm32f429i_discovery_leds_info[] = {
    {
        .name = "green-led",
        .active_low = false,
        .colour_message = "Green",
        .x = 519,
        .y = 109,
        .w = 10,
        .h = 8,
        .gpio_path = "/machine/mcu/stm32/gpio[g]",
        .port_bit = 13, },
    {
        .name = "red-led",
        .active_low = false,
        .colour_message = "Red",
        .x = 519,
        .y = 130,
        .w = 10,
        .h = 8,
        .gpio_path = "/machine/mcu/stm32/gpio[g]",
        .port_bit = 14, },
    { }, /**/
};

static void stm32f429i_discovery_board_init_callback(MachineState *machine)
{
    CortexMBoardState *board = CORTEXM_BOARD_STATE(machine);

    cortexm_board_greeting(board);

    {
        /* Create the MCU */
        Object *mcu = cm_object_new_mcu(machine, TYPE_STM32F429ZI);

        /* Set the board specific oscillator frequencies. */
        cm_object_property_set_int(mcu, 8000000, "hse-freq-hz"); /* 8.0 MHz */
        cm_object_property_set_int(mcu, 32768, "lse-freq-hz"); /* 32 kHz */

        cm_object_realize(mcu);
    }

    cortexm_board_init_graphic_image(board, "STM32F429I-Discovery.jpg");

    Object *peripheral = cm_container_get_peripheral();
    gpio_led_create_from_info(peripheral, stm32f429i_discovery_leds_info,
            &(board->graphic_context));
}

static void stm32f429i_discovery_board_class_init_callback(ObjectClass *oc,
        void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = "ST Discovery kit for STM32F429/439 lines";
    mc->init = stm32f429i_discovery_board_init_callback;
}

static const TypeInfo stm32f429i_discovery_machine = {
    .name = BOARD_TYPE_NAME("STM32F429I-Discovery"),
    .parent = TYPE_CORTEXM_BOARD,
    .class_init = stm32f429i_discovery_board_class_init_callback };

#if 0
/* ----- ST STM32F3-Discovery ----- */
static void
stm32f3_discovery_board_init_callback(MachineState *machine);

static QEMUMachine stm32f3_discovery_machine = {
    .name = "STM32F3-Discovery",
    .desc = "ST Discovery kit for STM32F303 line (Experimental)",
    .init = stm32f3_discovery_board_init_callback};

static void stm32f3_discovery_board_init_callback(MachineState *machine)
{
    cm_board_greeting(machine);
//cortexm_mcu_alloc(machine, TYPE_STM32F303VC);

    /* TODO: Add board inits */
}

/* ----- ST STM32F0-Discovery ----- */
static void
stm32f0_discovery_board_init_callback(MachineState *machine);

static QEMUMachine stm32f0_discovery_machine = {
    .name = "STM32F0-Discovery",
    .desc = "ST Discovery kit for STM32F051 line (Experimental)",
    .init = stm32f0_discovery_board_init_callback};

static void stm32f0_discovery_board_init_callback(MachineState *machine)
{
    cm_board_greeting(machine);
//cortexm_mcu_alloc(machine, TYPE_STM32F051R8);

    /* TODO: Add board inits */
}

/* ----- ST STM32VL-Discovery ----- */
static void
stm32vl_discovery_init_callback(MachineState *machine);

static QEMUMachine stm32vl_discovery_machine = {
    .name = "STM32VL-Discovery",
    .desc = "ST Discovery kit for STM32F100 Value Line (Experimental)",
    .init = stm32vl_discovery_init_callback};

static void stm32vl_discovery_init_callback(MachineState *machine)
{
    cm_board_greeting(machine);
//cortexm_mcu_alloc(machine, TYPE_STM32F100RB);

    /* TODO: Add board inits */
}
#endif

/* ----- Boards inits ----- */
static void stm32_machines_init(void)
{
    type_register_static(&stm32f4_discovery_machine);
    // type_register_static(&stm32f4_discovery2_machine);
    type_register_static(&stm32f429i_discovery_machine);
#if 0
    qemu_register_machine(&stm32f3_discovery_machine);
    qemu_register_machine(&stm32f0_discovery_machine);
    qemu_register_machine(&stm32vl_discovery_machine);
#endif
}

type_init(stm32_machines_init);
