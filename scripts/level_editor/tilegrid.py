import numpy as np


class TileGrid:

    def __init__(self, tiles):
        self.positions = np.array(tiles, dtype=int)

    def expand_positions(self, x, y, w, h):
        # move grid so that what was the origin, is now at (x, y) and ensure the total width (from new origin) is $width
        # and the total height (from new origin) is $height.

        old_h, old_w = self.positions.shape

        if old_h >= h and old_w >= w:
            return

        if old_h > h:
            h = old_h
        if old_w > w:
            w = old_w

        old_positions = self.positions
        self.positions = np.zeros((h,w), dtype=int)
        if old_w != 0 and old_h != 0:
            self.positions[y:y+old_h,x:x+old_w] = old_positions

    def expand_to_encompass(self, x, y):
        new_origin = [0, 0]
        new_size = list(self.size())

        if x < 0:
            new_origin[0] = -x
        elif x >= new_size[0]:
            new_size[0] = x

        if y < 0:
            new_origin[1] = -y
        elif y >= new_size[1]:
            new_size[1] = y

        self.expand_positions(*new_origin, *new_size)

    def size(self):
        return self.positions.shape

    def __getitem__(self, coord: [list, tuple]) -> int:
        if not isinstance(coord, (list, tuple)):
            raise Exception('grid get expects coord (i.e. list or 2-tuple)')

        rowi = int(coord[0])
        coli = int(coord[1])

        return self.positions[rowi][coli]

    def __setitem__(self, coord: [list, tuple], value: int):
        if not isinstance(coord, (list, tuple)):
            raise Exception('grid get expects coord (i.e. list or 2-tuple)')

        if not isinstance(value, (int, np.int64)):
            raise Exception(f'grid value must be integer (got {type(value)})')

        rowi = int(coord[0])
        coli = int(coord[1])
        sr, sc = self.size()
        if rowi >= sr or coli >= sc:
            self.expand_to_encompass(rowi, coli)

        self.positions[rowi, coli] = value

    def __iter__(self):
        return self.positions.__iter__()

    def __len__(self):
        return self.positions.__len__()

    def as_list_of_lists(self):
        rv = list()
        for row in self.positions:
            rv.append(list(row))
        return rv
