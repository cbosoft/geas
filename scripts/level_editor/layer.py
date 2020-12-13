from tileset import Tileset
from tilegrid import TileGrid

class Layer:

    def __init__(self, data):
        defaults = {
            'size': [32.0, 32.0],
            'x_offset': 0.0,
            'y_offset': 0.0,
            'tile_layer': 0,
            'tiles': [[]]
        }
        data = {**defaults, **data}
        self.tileset = Tileset(data['tileset'])
        self.name = data['name']
        self.tile_size = data['size']
        if isinstance(self.tile_size, (float, int)):
            self.tile_size = [self.tile_size, self.tile_size]
        self.offset = (data['x_offset']*self.tile_size[0], data['y_offset']*self.tile_size[1])
        self.tile_layer_index = data['tile_layer']
        self.grid = TileGrid(data['tiles'])

    def set_tileset(self, path):
        try:
            newtileset = Tileset(path)
            self.tileset = newtileset
        except Exception as e:
            print(f'error creating tileset: {e}')

    def to_object(self):
        return {
            'name': self.name,
            'tileset': self.tileset.path,
            'size': self.tile_size,
            'x_offset': self.offset[0],
            'y_offset': self.offset[1],
            'tile_layer': self.tile_layer_index,
            'tiles': self.grid.as_list_of_lists()
        }
