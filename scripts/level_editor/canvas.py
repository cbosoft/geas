import numpy as np


class Canvas:

    def __init__(self, editor):
        self.editor = editor

        self.is_panning = False
        self.has_panned = False
        self.mouse_old_position = [0, 0]

        self.offset = [0, 0]
        self.scale = [1, 1]
        self.scales = [2.0, 1.5, 1.25, 1.0, 0.75, 0.5, 0.25]
        self.scale_index = 3

    def mouse_down(self, button, pos):
        if button == 1:
            self.is_panning = True
            self.has_panned = False
            self.mouse_old_position = pos

    def mouse_up(self, button, pos):
        if button == 1:
            self.is_panning = False
            if not self.has_panned:
                self.paint_tile(*pos)
        elif button == 3:
            self.pick_tile(*pos)
        elif button > 3:
            self.mouse_wheel(button % 2 == 0)

    def mouse_wheel(self, forward):
        if forward:
            self.zoom_in()
        else:
            self.zoom_out()

    def mouse_moved(self, pos):
        if self.is_panning:
            dr = np.subtract(pos, self.mouse_old_position)
            self.mouse_old_position = pos
            self.pan(dr)

    def pan(self, dr):
        self.offset = np.add(self.offset, dr)
        self.has_panned = True

    def zoom_in(self):
        self.scale_index = min([self.scale_index+1, len(self.scales)-1])
        s = self.scales[self.scale_index]
        self.scale = [s,s]

    def zoom_out(self):
        self.scale_index = max([self.scale_index-1, 0])
        s = self.scales[self.scale_index]
        self.scale = [s,s]

    def paint_tile(self, *args, **kwargs):
        pass
