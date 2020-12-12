import json

import pygame as pg # only to be used for image loading
import numpy as np


class Tileset:

    def __init__(self, path):
        default_meta = {'number_frames': 1, 'number_layers': 1}
        with open(path+'.json') as f:
            meta_data = json.load(f)
        meta_data = {**default_meta, **meta_data}

        number_frames = meta_data['number_frames']
        if isinstance(number_frames, (float, int)):
            number_frames = [number_frames, 1]
        self.number_frames = number_frames
        self.number_layers = meta_data['number_layers']
        self.number_variants = self.number_frames[0]*self.number_frames[1]
        self.path = path
        self.img = pg.image.load(self.path)
        self.tile_size = [
            self.img.get_width()//self.number_frames[0],
            self.img.get_height()//self.number_layers//self.number_frames[1]
        ]
        self.layer_height = self.img.get_height()//self.number_layers

    def get_variant(self, variant, layer):
        # position measured FROM THE TOP LEFT
        wpf, hpf = self.tile_size
        xf = variant % self.number_frames[0]
        yf = variant // self.number_frames[1]
        x = wpf*xf
        y = hpf*yf

        layer_offset = self.layer_height*layer

        y = self.img.get_height()//self.number_layers - y - hpf + layer_offset
        rect = (x, y, wpf, hpf)
        return self.img.subsurface(rect)

    def get_variant_from_coord(self, pos):
        # TODO error checking
        pos = list(pos)
        pos[1] = self.layer_height - pos[1]
        row = pos[1]//self.tile_size[1]
        col = pos[0]//self.tile_size[0]
        variant = int(row*self.number_frames[0] + col)
        return variant
