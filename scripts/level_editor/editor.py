import numpy as np
import pygame as pg

from renderer import Renderer
from room import Room
from side_panel.settings_panel import SettingsPanel
from canvas import Canvas


class Editor:

    def __init__(self):
        self.alive = True

        self.renderer = Renderer()
        self.settings_panel = SettingsPanel(self)
        self.canvas = Canvas(self)

        self.room = None
        self.selected_layer = -1
        self.selected_variant = 1  # aka brush

        self.down_in_canvas = False

    def load(self, path):
        self.room = Room(path)
        self.select_tile(1)
        self.select_all_layers()

    def paint_tile(self, x, y):
        if not self.room:
            print('Error: no room loaded')
            return

        if self.selected_layer < 0:
            print('can\'t paint all tiles')
            return

        self.room.set_tile(x, y, self.selected_layer, self.selected_variant)

    def pick_tile(self, x, y):
        if not self.room:
            print('Error: no room loaded')
            return

        if self.selected_layer < 0:
            print('can\'t paint all tiles')
            return

        self.select_tile(self.room.get_tile(x, y, self.selected_layer))
        print(f'picked tile {self.selected_variant}')

    def select_tile(self, variant_plus_one):
        self.selected_variant = variant_plus_one
        layer = self.room.layers[self.selected_layer]
        variant = variant_plus_one - 1
        #self.side_panel.set_brush(layer.tileset.get_variant(variant, layer.layer_index))

    def select_next_layer(self):
        if not self.room:
            print('Error: no room loaded')
            return

        self.selected_layer += 1
        if self.selected_layer >= len(self.room.layers):
            self.selected_layer = 0
        #self.side_panel.set_selected_layer(self.selected_layer, self.room.layers[self.selected_layer].tileset)
        self.select_tile(1)

    def select_prev_layer(self):
        if not self.room:
            print('Error: no room loaded')
            return

        self.selected_layer -= 1
        if self.selected_layer <= 0:
            self.selected_layer = len(self.room.layers) - 1
        #self.side_panel.set_selected_layer(self.selected_layer, self.room.layers[self.selected_layer].tileset)
        self.select_tile(1)

    def select_next_variant(self):
        if not self.room:
            print('Error: no room loaded')
            return

        if self.selected_layer < 0:
            print('can\'t paint on all layers')
            return

        self.selected_variant += 1
        if self.selected_variant >= self.room.layers[self.selected_layer].tileset.number_variants:
            self.selected_variant = 1
        self.select_tile(self.selected_variant)

    def select_prev_variant(self):
        if not self.room:
            print('Error: no room loaded')
            return

        if self.selected_layer < 0:
            print('can\'t paint on all layers')
            return

        self.selected_variant -= 1
        if self.selected_variant < 1:
            self.selected_variant = self.room.layers[self.selected_layer].tileset.number_variants - 1
        self.select_tile(self.selected_variant)

    def select_all_layers(self):
        self.selected_layer = -1

    def draw(self):
        self.renderer.reset_window()
        self.renderer.draw(self.canvas)
        self.renderer.draw(self.settings_panel)
        self.renderer.update()

    def check_input(self):
        for event in pg.event.get():
            if event.type == pg.MOUSEBUTTONDOWN:
                self.mouse_down(**event.dict)
            elif event.type == pg.MOUSEBUTTONUP:
                self.mouse_up(**event.dict)
            elif event.type == pg.MOUSEMOTION:
                self.mouse_moved(**event.dict)
            elif event.type == pg.KEYDOWN:
                self.key_down(**event.dict)

    def mouse_down(self, *, button, pos, **kwargs):
        if pos[0] > self.settings_panel.width:
            self.canvas.mouse_down(button, pos)
            self.down_in_canvas = True
        else:
            self.down_in_canvas = False
            self.settings_panel.mouse_down(button, pos)

    def mouse_up(self, *, button, pos, **kwargs):
        if self.down_in_canvas:
            self.canvas.mouse_up(button, pos)
        else:
            self.settings_panel.mouse_up(button, pos)

    def mouse_moved(self, *, pos, **kwargs):
        self.canvas.mouse_moved(pos)

    def key_down(self, key, **kwargs):
        if key == pg.K_ESCAPE:
            self.quit()
            return

        self.settings_panel.key_down(**kwargs)

    def quit(self):
        self.alive = False

    def run(self):
        self.alive = True
        while self.alive:
            self.draw()
            self.check_input()

