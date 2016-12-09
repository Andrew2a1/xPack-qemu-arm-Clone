/*
 * STM32 MCU - PWR (power controller) emulation.
 *
 * Copyright (c) 2015 Liviu Ionescu.
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

#ifndef STM32_PWR_H_
#define STM32_PWR_H_

#include "qemu/osdep.h"

#include <hw/cortexm/peripheral.h>
#include <hw/cortexm/stm32/capabilities.h>

/* ------------------------------------------------------------------------- */

#define DEVICE_PATH_STM32_PWR DEVICE_PATH_STM32 "PWR"

/* ------------------------------------------------------------------------- */

#define TYPE_STM32_PWR TYPE_STM32_PREFIX "pwr" TYPE_PERIPHERAL_SUFFIX

/* ------------------------------------------------------------------------- */

/* Parent definitions. */
#define TYPE_STM32_PWR_PARENT TYPE_PERIPHERAL
typedef PeripheralClass STM32PWRParentClass;
typedef PeripheralState STM32PWRParentState;

/* ------------------------------------------------------------------------- */

/* Class definitions. */
#define STM32_PWR_GET_CLASS(obj) \
    OBJECT_GET_CLASS(STM32PWRClass, (obj), TYPE_STM32_PWR)
#define STM32_PWR_CLASS(klass) \
    OBJECT_CLASS_CHECK(STM32PWRClass, (klass), TYPE_STM32_PWR)

typedef struct {
    /*< private >*/
    STM32PWRParentClass parent_class;
    /*< public >*/

    /* None, so far. */
} STM32PWRClass;

/* ------------------------------------------------------------------------- */

/* Instance definitions. */
#define STM32_PWR_STATE(obj) \
    OBJECT_CHECK(STM32PWRState, (obj), TYPE_STM32_PWR)

typedef struct {
    /*< private >*/
    STM32PWRParentState parent_obj;
    /*< public >*/

    MemoryRegion mmio;

    struct {
        /* F1 specific registers */
        struct {
            Object *cr;
            Object *csr;
        } reg;
        struct {
            struct {
                Object *lpds;
                Object *pdds;
                Object *cwuf;
                Object *csbf;
                Object *pvde;
                Object *pls;
                Object *dbp;
            } cr;
            struct {
                Object *wuf;
                Object *sbf;
                Object *pvdo;
                // Object *ewup;
            } csr;
        } fld;
    } f0;

    struct {
        /* F1 specific registers */
        struct {
            Object *cr;
            Object *csr;
        } reg;
        struct {
            struct {
                Object *lpds;
                Object *pdds;
                Object *cwuf;
                Object *csbf;
                Object *pvde;
                Object *pls;
                Object *dbp;
            } cr;
            struct {
                Object *wuf;
                Object *sbf;
                Object *pvdo;
                Object *ewup;
            } csr;
        } fld;
    } f1;
#if 0
    struct {
        /* F4 specific registers */
        struct {
            Object *cr;
            Object *csr;
        }reg;
        struct {
            struct {
                Object *lpds;
                Object *pdds;
                Object *cwuf;
                Object *csbf;
                Object *pvde;
                Object *pls;
                Object *dbp;
                Object *fpds;

                Object *lpuds; /* [23]xxx */
                Object *mruds; /* [23]xxx */
                Object *adcdc1; /* [23]xxx */

                Object *vos;

                /* [23]xxx */
                Object *oden;
                Object *odswen;
                Object *uden;
            }cr;
            struct {
                Object *wuf;
                Object *sbf;
                Object *pvdo;
                Object *brr;
                Object *ewup;
                Object *bre;
                Object *vosrdy;
                /* [23]xxx */
                Object *odrdy;
                Object *odswrdy;
                Object *udrdy;
            }csr;
        }fld;
    }f4;
#endif
    struct {
        // F4 PWR (Power control) registers.
        struct {
            Object *cr; // 0x0 Power control register
            Object *csr; // 0x4 Power control/status register
        } reg;

        struct {

            // CR (Power control register) bitfields.
            struct {
                Object *lpds; // [0:0] Low-power deep sleep
                Object *pdds; // [1:1] Power down deepsleep
                Object *cwuf; // [2:2] Clear wakeup flag
                Object *csbf; // [3:3] Clear standby flag
                Object *pvde; // [4:4] Power voltage detector enable
                Object *pls; // [5:7] PVD level selection
                Object *dbp; // [8:8] Disable backup domain write protection
                Object *fpds; // [9:9] Flash power down in Stop mode
            } cr;

            // CSR (Power control/status register) bitfields.
            struct {
                Object *wuf; // [0:0] Wakeup flag
                Object *sbf; // [1:1] Standby flag
                Object *pvdo; // [2:2] PVD output
                Object *brr; // [3:3] Backup regulator ready
                Object *ewup; // [8:8] Enable WKUP pin
                Object *bre; // [9:9] Backup regulator enable
                Object *vosrdy; // [14:14] Regulator voltage scaling output selection ready bit
            } csr;
        } fld;
    } f4;
    const STM32Capabilities *capabilities;
} STM32PWRState;

/* ------------------------------------------------------------------------- */

#endif /* STM32_PWR_H_ */
