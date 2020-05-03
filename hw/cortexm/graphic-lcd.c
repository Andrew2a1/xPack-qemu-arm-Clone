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

#include <hw/cortexm/graphic-lcd.h>
#include <hw/cortexm/helper.h>

#include "exec/address-spaces.h"
#include "qapi/error.h"

#define LCD_MEMORY_ADDR 0xD0000000
#define LCD_BUFFER_SIZE 1024UL*1024UL

static void graphic_lcd_init_memory(Object *parent, void *lcd_mem_buffer, uint64_t mem_size)
{
    MemoryRegion *sysmem = get_system_memory();
    MemoryRegion *lcd_data = g_new(MemoryRegion, 1);
    MemoryRegion *lcd_buffer_data = g_new(MemoryRegion, 1);

    memory_region_init_ram_device_ptr(lcd_data, parent, "lcd-tft.ram", 
            mem_size, lcd_mem_buffer);
    vmstate_register_ram_global(lcd_data);
    memory_region_init_ram(lcd_buffer_data, parent, "lcd-tft-buffer.ram",
            mem_size, &error_fatal);
    vmstate_register_ram_global(lcd_buffer_data);

    memory_region_add_subregion(sysmem, LCD_MEMORY_ADDR, lcd_data);
    memory_region_add_subregion(sysmem, LCD_MEMORY_ADDR + mem_size, lcd_buffer_data);
}

static void graphic_lcd_load_rect_info(GraphicLCD *graphic_lcd, GraphicLCDInfo *info)
{
    SDL_Rect real_size = {
        .x = info->x,
        .y = info->y,
        .w = info->res_x,
        .h = info->res_y
    };

    SDL_Rect texture_size = {
        .x = info->x,
        .y = info->y,
        .w = info->w,
        .h = info->h
    };

    graphic_lcd->real_size = real_size;
    graphic_lcd->texture_size = texture_size;
}

Object *graphic_lcd_create_from_info(Object *parent, GraphicLCDInfo *info,
        BoardGraphicContext *graphic_context)
{
    Object *lcd = cm_object_new(parent, info->name, TYPE_GRAPHIC_LCD);
    GraphicLCD *graphic_lcd = GRAPHIC_LCD_STATE(lcd);

    graphic_lcd->graphic_context = graphic_context;
    graphic_lcd->pixels = malloc(LCD_BUFFER_SIZE);
    graphic_lcd->lcd_texture = NULL;

    graphic_lcd_init_memory(lcd, graphic_lcd->pixels, LCD_BUFFER_SIZE);
    graphic_lcd_load_rect_info(graphic_lcd, info);

    cortexm_graphic_enqueue_event(GRAPHIC_EVENT_LCD_INIT, graphic_lcd, NULL);
    return lcd;
}

void graphic_lcd_init_graphics(GraphicLCD *state)
{
    if (state->graphic_context)
    {
        state->lcd_texture = SDL_CreateTexture(state->graphic_context->renderer,
                                                     GRAPHIC_LCD_PIXEL_FORMAT, SDL_TEXTUREACCESS_STATIC,
                                                     state->real_size.w, state->real_size.h);
    }

    SDL_AddTimer(LCD_UPDATE_TIME_MS,
                 graphic_lcd_reload_callback,
                 state);
}

void graphic_lcd_reload(GraphicLCD *state)
{
    if(state->graphic_context != NULL && state->graphic_context->renderer != NULL) {
        cortexm_graphic_enqueue_event(GRAPHIC_EVENT_LCD_RELOAD, state, NULL);
    }
}

uint32_t graphic_lcd_reload_callback(uint32_t interval, void *param)
{
    graphic_lcd_reload(param);
    return interval;
}

static void graphic_lcd_destructor(Object *obj)
{
    GraphicLCD *graphic_lcd = GRAPHIC_LCD_STATE(obj);

    free(graphic_lcd->pixels);
    SDL_DestroyTexture(graphic_lcd->lcd_texture);
}

static const TypeInfo graphic_lcd_info = 
{
    .name = TYPE_GRAPHIC_LCD,
    .parent = TYPE_OBJECT,
    .instance_size = sizeof(GraphicLCD),
    .instance_finalize = graphic_lcd_destructor,
};

static void graphic_lcd_register_types(void)
{
    type_register_static(&graphic_lcd_info);
}

type_init(graphic_lcd_register_types);