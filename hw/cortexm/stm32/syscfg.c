/*
 * STM32 MCU - EXTI (system configuration controller) emulation.
 *
 * Copyright (c) 2016 Liviu Ionescu.
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

#include <hw/cortexm/stm32/syscfg.h>
#include <hw/cortexm/stm32/mcu.h>
#include <hw/cortexm/helper.h>
#include <hw/cortexm/svd.h>

/*
 * This file implements the STM32 SYSCFG, used in F4, F0 devices.
 */

/* ----- Private ----------------------------------------------------------- */

/* ------------------------------------------------------------------------- */

#if 0
static PeripheralInfo stm32f051xx_syscfg_info =
{
    .desc = "System configuration controller (SYSCFG)",
    .default_access_flags = PERIPHERAL_REGISTER_32BITS_ALL,

    .registers =
    (PeripheralRegisterInfo[] ) {
        {
            .desc =
            "Configuration register 1 (SYSCFG_CFGR1)",
            .name = "cfgr1",
            .offset_bytes = 0x00,
            /* 0x0000 000X (X is the memory mode selected by the actual boot mode configuration */
            .reset_value = 0x00000000,
            .readable_bits = 0x7FFF7FD3,
            /* MEM_MODE[1:0] */
            .writable_bits = 0x7FFF7FD3,
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 1 (SYSCFG_EXTICR1)",
            .name = "exticr1",
            .offset_bytes = 0x08,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 0 configuration",
                    .name = "exti0",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 1 configuration",
                    .name = "exti1",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 2 configuration",
                    .name = "exti2",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 3 configuration",
                    .name = "exti3",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 2 (SYSCFG_EXTICR2)",
            .name = "exticr2",
            .offset_bytes = 0x0C,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 4 configuration",
                    .name = "exti4",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 5 configuration",
                    .name = "exti5",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 6 configuration",
                    .name = "exti6",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 7 configuration",
                    .name = "exti7",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 3 (SYSCFG_EXTICR3)",
            .name = "exticr3",
            .offset_bytes = 0x10,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 8 configuration",
                    .name = "exti8",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 9 configuration",
                    .name = "exti9",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 10 configuration",
                    .name = "exti10",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 11 configuration",
                    .name = "exti11",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 4 (SYSCFG_EXTICR1)",
            .name = "exticr4",
            .offset_bytes = 0x14,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 12 configuration",
                    .name = "exti12",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 13 configuration",
                    .name = "exti13",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 14 configuration",
                    .name = "exti14",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 15 configuration",
                    .name = "exti15",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "Configuration register 2 (SYSCFG_CFGR2)",
            .name = "cfgr2",
            .offset_bytes = 0x18,
            .reset_value = 0x00000000,
            .readable_bits = 0x00000107,
            /* Bit 8 is rc_w1, cleared by writing 1. */
            .writable_bits = 0x00000107,
            /**/
        },
        {}, /**/
    }, /**/
};
#endif

static void stm32f051_syscfg_create_objects(Object *obj, JSON_Value *family)
{
    STM32SYSCFGState *state = STM32_SYSCFG_STATE(obj);

    JSON_Object *info = cm_json_parser_get_peripheral(family,
            "stm32f051:syscfg");

    peripheral_add_properties_and_children2(obj, info);

    state->f0.reg.cfgr1 = cm_object_get_child_by_name(obj, "cfgr1");
    state->f0.reg.exticr1 = cm_object_get_child_by_name(obj, "exticr1");
    state->f0.reg.exticr2 = cm_object_get_child_by_name(obj, "exticr2");
    state->f0.reg.exticr3 = cm_object_get_child_by_name(obj, "exticr3");
    state->f0.reg.exticr4 = cm_object_get_child_by_name(obj, "exticr4");
    state->f0.reg.cfgr2 = cm_object_get_child_by_name(obj, "cfgr2");

    state->exticr.exti[0] = cm_object_get_child_by_name(state->f0.reg.exticr1,
            "exti0");
    state->exticr.exti[1] = cm_object_get_child_by_name(state->f0.reg.exticr1,
            "exti1");
    state->exticr.exti[2] = cm_object_get_child_by_name(state->f0.reg.exticr1,
            "exti2");
    state->exticr.exti[3] = cm_object_get_child_by_name(state->f0.reg.exticr1,
            "exti3");

    state->exticr.exti[4] = cm_object_get_child_by_name(state->f0.reg.exticr2,
            "exti4");
    state->exticr.exti[5] = cm_object_get_child_by_name(state->f0.reg.exticr2,
            "exti5");
    state->exticr.exti[6] = cm_object_get_child_by_name(state->f0.reg.exticr2,
            "exti6");
    state->exticr.exti[7] = cm_object_get_child_by_name(state->f0.reg.exticr2,
            "exti7");

    state->exticr.exti[8] = cm_object_get_child_by_name(state->f0.reg.exticr3,
            "exti8");
    state->exticr.exti[9] = cm_object_get_child_by_name(state->f0.reg.exticr3,
            "exti9");
    state->exticr.exti[10] = cm_object_get_child_by_name(state->f0.reg.exticr3,
            "exti10");
    state->exticr.exti[11] = cm_object_get_child_by_name(state->f0.reg.exticr3,
            "exti11");

    state->exticr.exti[12] = cm_object_get_child_by_name(state->f0.reg.exticr4,
            "exti12");
    state->exticr.exti[13] = cm_object_get_child_by_name(state->f0.reg.exticr4,
            "exti13");
    state->exticr.exti[14] = cm_object_get_child_by_name(state->f0.reg.exticr4,
            "exti14");
    state->exticr.exti[15] = cm_object_get_child_by_name(state->f0.reg.exticr4,
            "exti15");
}

/* ------------------------------------------------------------------------- */

static void stm32f40x_syscfg_create_objects(Object *obj, JSON_Object *svd,
        const char *name)
{
    // DO NOT EDIT! Automatically generated!
    STM32SYSCFGState *state = STM32_SYSCFG_STATE(obj);

    JSON_Object *periph = svd_get_peripheral_by_name(svd, name);
    svd_add_peripheral_properties_and_children(obj, periph, svd);

    // Registers.
    state->f4.reg.memrm = cm_object_get_child_by_name(obj, "MEMRM");
    state->f4.reg.pmc = cm_object_get_child_by_name(obj, "PMC");
    state->f4.reg.exticr1 = cm_object_get_child_by_name(obj, "EXTICR1");
    state->f4.reg.exticr2 = cm_object_get_child_by_name(obj, "EXTICR2");
    state->f4.reg.exticr3 = cm_object_get_child_by_name(obj, "EXTICR3");
    state->f4.reg.exticr4 = cm_object_get_child_by_name(obj, "EXTICR4");
    state->f4.reg.cmpcr = cm_object_get_child_by_name(obj, "CMPCR");

    // MEMRM bitfields.
    state->f4.fld.memrm.mem_mode = cm_object_get_child_by_name(
            state->f4.reg.memrm, "MEM_MODE");

    // PMC bitfields.
    state->f4.fld.pmc.mii_rmii_sel = cm_object_get_child_by_name(
            state->f4.reg.pmc, "MII_RMII_SEL");

    // EXTICR1 bitfields.
    state->f4.fld.exticr1.exti0 = cm_object_get_child_by_name(
            state->f4.reg.exticr1, "EXTI0");
    state->f4.fld.exticr1.exti1 = cm_object_get_child_by_name(
            state->f4.reg.exticr1, "EXTI1");
    state->f4.fld.exticr1.exti2 = cm_object_get_child_by_name(
            state->f4.reg.exticr1, "EXTI2");
    state->f4.fld.exticr1.exti3 = cm_object_get_child_by_name(
            state->f4.reg.exticr1, "EXTI3");

    // EXTICR2 bitfields.
    state->f4.fld.exticr2.exti4 = cm_object_get_child_by_name(
            state->f4.reg.exticr2, "EXTI4");
    state->f4.fld.exticr2.exti5 = cm_object_get_child_by_name(
            state->f4.reg.exticr2, "EXTI5");
    state->f4.fld.exticr2.exti6 = cm_object_get_child_by_name(
            state->f4.reg.exticr2, "EXTI6");
    state->f4.fld.exticr2.exti7 = cm_object_get_child_by_name(
            state->f4.reg.exticr2, "EXTI7");

    // EXTICR3 bitfields.
    state->f4.fld.exticr3.exti8 = cm_object_get_child_by_name(
            state->f4.reg.exticr3, "EXTI8");
    state->f4.fld.exticr3.exti9 = cm_object_get_child_by_name(
            state->f4.reg.exticr3, "EXTI9");
    state->f4.fld.exticr3.exti10 = cm_object_get_child_by_name(
            state->f4.reg.exticr3, "EXTI10");
    state->f4.fld.exticr3.exti11 = cm_object_get_child_by_name(
            state->f4.reg.exticr3, "EXTI11");

    // EXTICR4 bitfields.
    state->f4.fld.exticr4.exti12 = cm_object_get_child_by_name(
            state->f4.reg.exticr4, "EXTI12");
    state->f4.fld.exticr4.exti13 = cm_object_get_child_by_name(
            state->f4.reg.exticr4, "EXTI13");
    state->f4.fld.exticr4.exti14 = cm_object_get_child_by_name(
            state->f4.reg.exticr4, "EXTI14");
    state->f4.fld.exticr4.exti15 = cm_object_get_child_by_name(
            state->f4.reg.exticr4, "EXTI15");

    // CMPCR bitfields.
    state->f4.fld.cmpcr.cmp_pd = cm_object_get_child_by_name(
            state->f4.reg.cmpcr, "CMP_PD");
    state->f4.fld.cmpcr.ready = cm_object_get_child_by_name(state->f4.reg.cmpcr,
            "READY");
}

#if 0
static PeripheralInfo stm32f4xxxx_syscfg_info =
{
    .desc = "System configuration controller (SYSCFG)",
    .default_access_flags = PERIPHERAL_REGISTER_32BITS_ALL,

    .registers =
    (PeripheralRegisterInfo[] ) {
        {
            .desc =
            "Memory remap register (SYSCFG_MEMRMP)",
            .name = "memrmp",
            .offset_bytes = 0x00,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "Memory mapping selection",
                    .name = "mem-mode",
                    .first_bit = 0,
                    .width_bits = 2,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "Peripheral mode configuration register (SYSCFG_PMC)",
            .name = "pmc",
            .offset_bytes = 0x04,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "Ethernet PHY interface selection",
                    .name =
                    "mii-rmii-sel",
                    .first_bit = 7,
                    .width_bits = 1,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 1 (SYSCFG_EXTICR1)",
            .name = "exticr1",
            .offset_bytes = 0x08,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 0 configuration",
                    .name = "exti0",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 1 configuration",
                    .name = "exti1",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 2 configuration",
                    .name = "exti2",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 3 configuration",
                    .name = "exti3",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 2 (SYSCFG_EXTICR2)",
            .name = "exticr2",
            .offset_bytes = 0x0C,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 4 configuration",
                    .name = "exti4",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 5 configuration",
                    .name = "exti5",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 6 configuration",
                    .name = "exti6",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 7 configuration",
                    .name = "exti7",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 3 (SYSCFG_EXTICR3)",
            .name = "exticr3",
            .offset_bytes = 0x10,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 8 configuration",
                    .name = "exti8",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 9 configuration",
                    .name = "exti9",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 10 configuration",
                    .name = "exti10",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 11 configuration",
                    .name = "exti11",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "External interrupt configuration register 4 (SYSCFG_EXTICR1)",
            .name = "exticr4",
            .offset_bytes = 0x14,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "EXTI 12 configuration",
                    .name = "exti12",
                    .first_bit = 0,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 13 configuration",
                    .name = "exti13",
                    .first_bit = 4,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 14 configuration",
                    .name = "exti14",
                    .first_bit = 8,
                    .width_bits = 4,
                    /**/
                },
                {
                    .desc =
                    "EXTI 15 configuration",
                    .name = "exti15",
                    .first_bit = 12,
                    .width_bits = 4,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {
            .desc =
            "Compensation cell control register (SYSCFG_CMPCR)",
            .name = "cmpcr",
            .offset_bytes = 0x20,
            .reset_value = 0x00000000,
            .bitfields =
            (RegisterBitfieldInfo[] ) {
                {
                    .desc =
                    "Compensation cell power-down",
                    .name = "cmp-pd",
                    .first_bit = 0,
                    .width_bits = 1,
                    /**/
                },
                {
                    .desc =
                    "Compensation cell ready flag",
                    .name = "ready",
                    .first_bit = 8,
                    .width_bits = 1,
                    .rw_mode =
                    REGISTER_RW_MODE_READ,
                    /**/
                },
                {} /**/
            },
            /**/
        },
        {}, /**/
    }, /**/
};
#endif

#if 0
static void stm32f4xx_syscfg_create_objects(Object *obj, JSON_Value *family)
{
    STM32SYSCFGState *state = STM32_SYSCFG_STATE(obj);

    JSON_Object *info = cm_json_parser_get_peripheral(family,
            "stm32f4xx:syscfg");

    peripheral_add_properties_and_children2(obj, info);

#if 0
    state->f4.reg.memrmp = cm_object_get_child_by_name(obj, "memrmp");
    state->f4.fld.memrmp.mem_mode = cm_object_get_child_by_name(
            state->f4.reg.memrmp, "mem-mode");
#endif

    state->f4.reg.pmc = cm_object_get_child_by_name(obj, "pmc");
    state->f4.reg.exticr1 = cm_object_get_child_by_name(obj, "exticr1");
    state->f4.reg.exticr2 = cm_object_get_child_by_name(obj, "exticr2");
    state->f4.reg.exticr3 = cm_object_get_child_by_name(obj, "exticr3");
    state->f4.reg.exticr4 = cm_object_get_child_by_name(obj, "exticr4");

    state->exticr.exti[0] = cm_object_get_child_by_name(state->f4.reg.exticr1,
            "exti0");
    state->exticr.exti[1] = cm_object_get_child_by_name(state->f4.reg.exticr1,
            "exti1");
    state->exticr.exti[2] = cm_object_get_child_by_name(state->f4.reg.exticr1,
            "exti2");
    state->exticr.exti[3] = cm_object_get_child_by_name(state->f4.reg.exticr1,
            "exti3");

    state->exticr.exti[4] = cm_object_get_child_by_name(state->f4.reg.exticr2,
            "exti4");
    state->exticr.exti[5] = cm_object_get_child_by_name(state->f4.reg.exticr2,
            "exti5");
    state->exticr.exti[6] = cm_object_get_child_by_name(state->f4.reg.exticr2,
            "exti6");
    state->exticr.exti[7] = cm_object_get_child_by_name(state->f4.reg.exticr2,
            "exti7");

    state->exticr.exti[8] = cm_object_get_child_by_name(state->f4.reg.exticr3,
            "exti8");
    state->exticr.exti[9] = cm_object_get_child_by_name(state->f4.reg.exticr3,
            "exti9");
    state->exticr.exti[10] = cm_object_get_child_by_name(state->f4.reg.exticr3,
            "exti10");
    state->exticr.exti[11] = cm_object_get_child_by_name(state->f4.reg.exticr3,
            "exti11");

    state->exticr.exti[12] = cm_object_get_child_by_name(state->f4.reg.exticr4,
            "exti12");
    state->exticr.exti[13] = cm_object_get_child_by_name(state->f4.reg.exticr4,
            "exti13");
    state->exticr.exti[14] = cm_object_get_child_by_name(state->f4.reg.exticr4,
            "exti14");
    state->exticr.exti[15] = cm_object_get_child_by_name(state->f4.reg.exticr4,
            "exti15");

    state->f4.reg.cmpcr = cm_object_get_child_by_name(obj, "cmpcr");
    state->f4.fld.cmpcr.cmp_pd = cm_object_get_child_by_name(
            state->f4.reg.cmpcr, "cmp-pd");
    state->f4.fld.cmpcr.ready = cm_object_get_child_by_name(state->f4.reg.cmpcr,
            "ready");

    cm_object_property_set_str(state->f4.fld.cmpcr.ready, "cmp-pd", "follows");
}
#endif

/* ------------------------------------------------------------------------- */

static void stm32_syscfg_instance_init_callback(Object *obj)
{
    qemu_log_function_name();

    // STM32SYSCFGState *state = STM32_SYSCFG_STATE(obj);

    /* capabilities are not yet available. */

    /* No interrupts for now, maybe add boot mode bits. */
}

static void stm32_syscfg_realize_callback(DeviceState *dev, Error **errp)
{
    qemu_log_function_name();

    /*
     * Parent realize() is called after setting properties and creating
     * registers.
     */

    STM32MCUState *mcu = stm32_mcu_get();
    CortexMState *cm_state = CORTEXM_MCU_STATE(mcu);

    STM32SYSCFGState *state = STM32_SYSCFG_STATE(dev);
    /* First thing first: get capabilities from MCU, needed everywhere. */
    state->capabilities = mcu->capabilities;

    /* Also keep a local pointer, to access them easier. */
    const STM32Capabilities *capabilities = state->capabilities;
    assert(capabilities != NULL);

    Object *obj = OBJECT(dev);

    /*
     * Creating the memory region in the parent class will trigger
     * an assertion if zro address or size.
     */
    uint32_t size = 0;
    hwaddr addr = 0;

    switch (capabilities->family) {
    case STM32_FAMILY_F0:
        addr = 0x40010000;
        size = 0x400;
        break;

    case STM32_FAMILY_F4:
        addr = 0x40013800;
        size = 0x400;
        break;

    default:
        assert(false);
        break;
    }

    cm_object_property_set_int(obj, addr, "mmio-address");
    cm_object_property_set_int(obj, size, "mmio-size-bytes");

    switch (capabilities->family) {
    case STM32_FAMILY_F0:
        stm32f051_syscfg_create_objects(obj, mcu->family_json);
        break;

    case STM32_FAMILY_F4:
        stm32f40x_syscfg_create_objects(obj, cm_state->svd_json, "SYSCFG");

        // For easier access, also maintain an array.
        state->exticr.exti[0] = state->f4.fld.exticr1.exti0;
        state->exticr.exti[1] = state->f4.fld.exticr1.exti1;
        state->exticr.exti[2] = state->f4.fld.exticr1.exti2;
        state->exticr.exti[3] = state->f4.fld.exticr1.exti3;
        state->exticr.exti[4] = state->f4.fld.exticr2.exti4;
        state->exticr.exti[5] = state->f4.fld.exticr2.exti5;
        state->exticr.exti[6] = state->f4.fld.exticr2.exti6;
        state->exticr.exti[7] = state->f4.fld.exticr2.exti7;
        state->exticr.exti[8] = state->f4.fld.exticr3.exti8;
        state->exticr.exti[9] = state->f4.fld.exticr3.exti9;
        state->exticr.exti[10] = state->f4.fld.exticr3.exti10;
        state->exticr.exti[11] = state->f4.fld.exticr3.exti11;
        state->exticr.exti[12] = state->f4.fld.exticr4.exti12;
        state->exticr.exti[13] = state->f4.fld.exticr4.exti13;
        state->exticr.exti[14] = state->f4.fld.exticr4.exti14;
        state->exticr.exti[15] = state->f4.fld.exticr4.exti15;

        // Actions.
        cm_object_property_set_str(state->f4.fld.cmpcr.ready, "CMP_PD",
                "follows");

        //stm32f4xx_syscfg_create_objects(obj, mcu->family_json);
        break;

    default:
        assert(false);
        break;
    }

    /* Call parent realize(). */
    if (!cm_device_parent_realize(dev, errp, TYPE_STM32_SYSCFG)) {
        return;
    }
}

static void stm32_syscfg_reset_callback(DeviceState *dev)
{
    qemu_log_function_name();

    /* Call parent reset(). */
    cm_device_parent_reset(dev, TYPE_STM32_SYSCFG);
}

static void stm32_syscfg_class_init_callback(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = stm32_syscfg_reset_callback;
    dc->realize = stm32_syscfg_realize_callback;
}

static const TypeInfo stm32_syscfg_type_info = {
    .name = TYPE_STM32_SYSCFG,
    .parent = TYPE_STM32_SYSCFG_PARENT,
    .instance_init = stm32_syscfg_instance_init_callback,
    .instance_size = sizeof(STM32SYSCFGState),
    .class_init = stm32_syscfg_class_init_callback,
    .class_size = sizeof(STM32SYSCFGClass) };

static void stm32_syscfg_register_types(void)
{
    type_register_static(&stm32_syscfg_type_info);

#if 0
    peripheral_serialize_info("f051-syscfg.json", "stm32f051:syscfg", &stm32f051xx_syscfg_info);
    peripheral_serialize_info("f4xx-syscfg.json", "stm32f4xx:syscfg", &stm32f4xxxx_syscfg_info);
#endif
}

type_init(stm32_syscfg_register_types);

/* ------------------------------------------------------------------------- */

