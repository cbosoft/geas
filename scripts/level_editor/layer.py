from tileset import Tileset
from tilegrid import TileGrid

class Layer:

    def __init__(self, data):
        self.tileset = Tileset(data['tileset'])
        self.name = data['name']
        self.tile_size = data['size']
        if isinstance(self.tile_size, (float, int)):
            self.tile_size = [self.tile_size, self.tile_size]
        self.offset = (data['x_offset']*self.tile_size[0], data['y_offset']*self.tile_size[1])
        self.tile_layer_index = 0 if 'tile_layer' not in data else data['tile_layer']
        print(self.tile_layer_index, self.offset)
        self.grid = TileGrid(data['tiles'])

    def set_tileset(self, path):
        try:
            newtileset = Tileset(path)
            self.tileset = newtileset
        except Exception as e:
            print(f'error creating tileset: {e}')
