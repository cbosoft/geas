import json

import numpy as np

from layer import Layer


class Room:

    def __init__(self, path):
        with open(path) as f:
            data = json.load(f)
        self.name = data['name']
        self.layers = [Layer(l) for l in data['layers']]

    def screen_to_layer_coords(self, x, y, i):
        # x, y in screen coords
        tl = [x, y] # - offset
        layer = self.layers[i]
        tl = np.add(tl, np.multiply([layer.x_offset, -layer.y_offset], layer.tile_size))
        scaled_tile = layer.tile_size # * renderer.scale
        tl_i = [int(i) for i in np.divide(tl, scaled_tile)]

        # from x,y to r,c
        tl_i = (tl_i[1], tl_i[0])
        return tl_i

    def set_tile(self, x, y, i, value):
        layer = self.layers[i]
        pos = self.screen_to_layer_coords(x, y, i)
        layer.grid[pos] = value

    def get_tile(self, x, y, i):
        layer = self.layers[i]
        pos = self.screen_to_layer_coords(x, y, i)
        return layer.grid[pos]
