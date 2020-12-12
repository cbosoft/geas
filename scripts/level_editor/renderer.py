import numpy as np
import pygame as pg

from tileset import Tileset
from tilegrid import TileGrid
from room import Room
from layer import Layer
from canvas import Canvas
from side_panel.settings_panel import SettingsPanel, RoomSettings, LayerSettings, TilePalette, LoadSavePanel
from side_panel.uielements.textbox import TextBox
from side_panel.uielements.button import Button
from side_panel.layerlist import LayerButtonSet


class Renderer:

    def __init__(self, view_width=1000, view_height=500):
        pg.init()
        self.width = view_width
        self.height = view_height
        self.centre = view_width*0.5, view_height*0.5
        self.win = pg.display.set_mode([view_width, view_height])
        self.reset_window()
        self.font = pg.font.Font('freesansbold.ttf', 16)

    def reset_window(self):
        self.win.fill([200, 0, 200])

    def add_image(self, img, at, final_size):
        fs = [int(i) for i in final_size]
        img = pg.transform.scale(img, fs)
        self.win.blit(img, at)

    def update(self):
        pg.display.update()

    def draw(self, obj, *args, **kwargs):
        if isinstance(obj, Tileset):
            self.draw_tileset(obj, *args, **kwargs)
        elif isinstance(obj, TileGrid):
            self.draw_tilegrid(obj, *args, **kwargs)
        elif isinstance(obj, Room):
            self.draw_room(obj, *args, **kwargs)
        elif isinstance(obj, Layer):
            self.draw_layer(obj, *args, **kwargs)
        elif isinstance(obj, Canvas):
            self.draw_canvas(obj)
        elif isinstance(obj, SettingsPanel):
            self.draw_settings_panel(obj)
        elif isinstance(obj, RoomSettings):
            self.draw_roomsettings(obj, *args, **kwargs)
        elif isinstance(obj, LayerSettings):
            self.draw_layersettings(obj, *args, **kwargs)
        elif isinstance(obj, LoadSavePanel):
            self.draw_loadsave_panel(obj, *args, **kwargs)
        elif isinstance(obj, TilePalette):
            self.draw_tile_palette(obj, *args, **kwargs)
        elif isinstance(obj, TextBox):
            self.draw_textbox(obj)
        elif isinstance(obj, LayerButtonSet):
            self.draw_layer_button_set(obj)
        elif isinstance(obj, Button):
            self.draw_button(obj)

    def draw_room(self, room: Room, selected_layer: int, offset, scale):
        if selected_layer < 0:
            for layer in room.layers:
                self.draw(layer, offset, scale)
        else:
            self.draw(room.layers[selected_layer], offset, scale)

    def draw_layer(self, layer: Layer, offset, scale):
        self.draw_tilegrid(layer.grid, layer.tileset, offset, scale,
                           layer.tile_size, layer.offset, layer.tile_layer_index)

    def draw_tilegrid(self, grid: TileGrid, tileset: Tileset, offset, scale, tile_size, layer_offset, tile_layer_index):
        h = len(grid)*tile_size[1]
        y = h+layer_offset[1]
        # float y = h + y_offset, x;
        for row in grid:
            x = layer_offset[0]
            for cell in row:
                if cell:
                    img = tileset.get_variant(cell-1, tile_layer_index)
                    pt = [x, self.height - y]
                    pt = np.multiply(pt, scale)
                    pt = np.add(pt, offset)
                    ts = np.multiply(tile_size, scale)
                    self.add_image(img, at=pt, final_size=ts)
                x += tile_size[0]
            y -= tile_size[1]

    def draw_canvas(self, canvas: Canvas):
        self.draw(canvas.editor.room, canvas.editor.selected_layer, canvas.offset, canvas.scale)

    def draw_settings_panel(self, settings_panel):
        bg = pg.surface.Surface([settings_panel.width, self.height])
        bg.fill(settings_panel.bg_colour)
        x = 0
        y = 0
        self.win.blit(bg, [x, y])

        x += settings_panel.margin
        y += settings_panel.margin

        self.draw(settings_panel.current_panel, x, y)

    def draw_tile_palette(self, tile_palette, x, y):
        self.win.blit(self.font.render('Selected Brush:', True, tile_palette.get_text_colour()), [x, y])

        y += tile_palette.get_margin() + self.font.get_height()

        if tile_palette.get_brush():
            self.win.blit(tile_palette.get_brush(), [x, y])
        y += tile_palette.get_margin() + tile_palette.get_brush_size()

        #if settings_panel.selected_layer:
        #    self.win.blit(settings_panel.selected_layer, [x, y])

        #if settings_panel.tileset and room and self.selected_layer_index >= 0:
        #    self.tileset.draw((self.margin, self.panel.get_height()-self.margin), renderer, room.layers[self.selected_layer_index].layer_index, self.tileset_width)

    def draw_loadsave_panel(self, loadsave_panel, x, y):
        for widget in loadsave_panel.clickables:
            self.draw(widget)

    def draw_textbox(self, textbox: TextBox):
        title_text = self.font.render(textbox.title, True, [255, 255, 255])
        title_text_pos = np.subtract(textbox.pos, [0, 20])
        self.win.blit(title_text, title_text_pos)

        txt = textbox.text
        if textbox.active:
            txt += '|'
        text = self.font.render(txt, True, textbox.text_colour)
        bg_size = list(textbox.size)
        if textbox.active:
            bg_size[0] = max([text.get_width() + 10, textbox.size[0]])

        text_pos = [5, (textbox.size[1] - text.get_height())/2]
        bg = pg.surface.Surface(bg_size)
        bg.fill(textbox.bg_colour)
        if textbox.active:
            pg.draw.rect(bg, textbox.text_colour, [0, 0, *bg_size], width=1)
        bg.blit(text, text_pos)
        self.win.blit(bg, textbox.pos)

    def draw_button(self, button: Button):
        bg = pg.surface.Surface(button.size)
        bgcolor = button.bg_colour if not button.pushed else button.pushed_colour
        bg.fill(bgcolor)
        text = self.font.render(button.text, True, button.text_colour)
        text_pos = [
            (button.size[0] - text.get_width())/2,
            (button.size[1] - text.get_height())/2
        ]
        bg.blit(text, text_pos)
        self.win.blit(bg, button.pos)

    def draw_roomsettings(self, panel: RoomSettings, x, y):
        for widget in panel.clickables:
            self.draw(widget)
        for buttonset in panel.layer_buttons:
            self.draw(buttonset)

    def draw_layersettings(self, panel: LayerSettings, x, y):
        for widget in panel.clickables:
            self.draw(widget)

        layer = panel.panel.editor.get_selected_layer()
        if layer:
            self.draw(layer.tileset, *panel.tileset_position, *panel.scaled_tileset_size, layer.tile_layer_index,
                      selected=panel.panel.editor.selected_variant-1)

    def draw_layer_button_set(self, buttonset):
        for button in buttonset.buttons:
            self.draw(button)

    def draw_tileset(self, tileset: Tileset, x, y, scaled_w, scaled_h, layer, selected=None):
        layer_offset = tileset.layer_height*layer
        surf = pg.surface.Surface([tileset.img.get_width(), tileset.layer_height])
        surf.fill([200, 0, 200])
        layerimg = tileset.img.subsurface(
            [0, layer_offset,
             tileset.img.get_width(),
             tileset.layer_height])
        surf.blit(layerimg, [0, 0])

        for hi in range(1,tileset.number_frames[0]):
            y1 = 0
            y2 = tileset.layer_height
            xx = hi*tileset.tile_size[0]
            pg.draw.line(surf, (150, 150, 150), (xx, y1), (xx, y2))

        for vi in range(1,tileset.number_frames[0]):
            x1 = 0
            x2 = tileset.img.get_width()
            yy = vi*tileset.tile_size[1]
            pg.draw.line(surf, (150, 150, 150), (x1, yy), (x2, yy))

        if selected is not None:
            rw, rh = tileset.tile_size
            rx = (selected % tileset.number_frames[0])*rw
            ry = tileset.layer_height - rh - (selected // tileset.number_frames[1])*rh
            pg.draw.rect(surf, (255, 255, 255), (rx, ry, rw, rh), width=5)

        surf = pg.transform.scale(surf, [scaled_w, scaled_h])
        self.win.blit(surf, [x, y])
