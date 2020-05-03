/*
 * Graphic LCD emulation.
 *
 * Copyright (c) 2020 Adam Brzakala.
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

#ifndef GRAPHIC_LCD_H_
#define GRAPHIC_LCD_H_

#include "qemu/typedefs.h"
#include "qemu/osdep.h"

#include "hw/qdev.h"
#include "hw/sysbus.h"
#include "hw/cortexm/graphic.h"

#define GRAPHIC_LCD_PIXEL_SIZE 2
#define GRAPHIC_LCD_PIXEL_FORMAT SDL_PIXELFORMAT_RGB565
#define LCD_UPDATE_TIME_MS 20

#define TYPE_GRAPHIC_LCD "graphic-lcd"

// Parent Definition
typedef ObjectClass GraphicLCDParentClass;

// Class definitions.
#define GRAPHIC_LCD_GET_CLASS(obj) \
    OBJECT_GET_CLASS(GraphicLCDParentClass, (obj), TYPE_GRAPHIC_LCD)
#define GRAPHIC_LCD_CLASS(klass) \
    OBJECT_CLASS_CHECK(GraphicLCDParentClass, (klass), TYPE_GRAPHIC_LCD)

// Instance definitions.
#define GRAPHIC_LCD_STATE(obj) \
    OBJECT_CHECK(GraphicLCD, (obj), TYPE_GRAPHIC_LCD)

typedef struct {
    const char *name;

    uint32_t x, y;  /* Left-top of lcd. */
    uint32_t w, h;  /* Dimensions of the rectangle to fill */
    uint32_t res_x, res_y; /* real resolution */

    void *pixels;

} GraphicLCDInfo;

typedef struct {
    GraphicLCDParentClass parent_class;
} GraphicLCDClass;

typedef struct GraphicLCD {
    DeviceState parent;

    SDL_Rect real_size;
    SDL_Rect texture_size;
    SDL_Texture *lcd_texture;

    BoardGraphicContext *graphic_context;
    void *pixels;
    
} GraphicLCD;

Object *graphic_lcd_create_from_info(Object *parent, GraphicLCDInfo *info,
        BoardGraphicContext *graphic_context);

void graphic_lcd_init_graphics(GraphicLCD *state);
void graphic_lcd_reload(GraphicLCD *state);
uint32_t graphic_lcd_reload_callback(uint32_t interval, void *param);

#endif // GRAPHIC_LCD_H_