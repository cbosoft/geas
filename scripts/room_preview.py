import json
import sys

import pygame as pg
import numpy as np


class PreviewRenderer:

    def __init__(self, width=1920, height=1080):
        self.width = width
        self.height = height
        self.centre = self.width*0.5, self.height*0.5
        self.win = pg.display.set_mode([width, height])
        self.win.fill([0, 0, 0])

    def add_image(self, path, at, rect=None):
        at = np.add(at, self.centre)
        img = pg.image.load(path)
        if rect:
            img = img.subsurface(rect)
        self.win.blit(img, at)

    def save(self):
        pg.image.save(self.win, "output.png")


class Layer:

    def __init__(self, data):
        self.tileset = data['tileset']
        with open(self.tileset+'.json') as f:
            tdata = json.load(f)

        self.number_frames = tdata['number_frames']
        self.s = data['size']
        self.x_offset = data['x_offset']*self.s
        self.y_offset = data['y_offset']*self.s
        self.tiles = data['tiles']
        self.img = pg.image.load(self.tileset)

    def get_variant_position(self, i):
        # position measured FROM THE TOP LEFT
        x = 0
        y = 0
        if isinstance(self.number_frames, (list,tuple)):
            wpf = self.img.get_width()/self.number_frames[0]
            hpf = self.img.get_height()/self.number_frames[1]
            xf = i % self.number_frames[0]
            yf = i // self.number_frames[1]
            x = wpf*xf
            y = hpf*yf
        else:
            wpf = self.img.get_width()/self.number_frames
            hpf = self.img.get_height()
            x = wpf*i

        y = self.img.get_height() - y - hpf
        return x, y

    def draw(self, prev):
        y = -self.y_offset
        for row in self.tiles:
            x = self.x_offset
            for cell in row:
                if cell:
                    pos = self.get_variant_position(cell-1)
                    prev.add_image(self.tileset,
                                 at=[x, y],
                                 rect=[*pos, self.s, self.s])
                x += self.s
            y += self.s




class Room:
    
    def __init__(self, data):
        self.name = data['name']
        self.layers = [Layer(l) for l in data['layers']]

    def draw(self):
        prev = PreviewRenderer()
        for layer in self.layers:
            layer.draw(prev)
        prev.save()



if __name__ == '__main__':
    fname = sys.argv[1]
    with open(fname) as f:
        data = json.load(f)
    room = Room(data)
    room.draw()
