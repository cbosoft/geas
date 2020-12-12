import numpy as np

from side_panel.sub_panel import SubPanel
from side_panel.uielements.textbox import TextBox
from side_panel.uielements.button import Button


class PalettePicker:

    def __init__(self, panel):
        self.panel = panel

    def mouse_down(self, button, pos):
        if button != 1:
            return

        sx, sy = np.subtract(pos, self.panel.tileset_position)
        layer = self.panel.panel.editor.get_selected_layer()
        i = layer.tile_layer_index
        w = layer.tileset.img.get_width()
        h = layer.tileset.layer_height
        sw, sh = self.panel.scaled_tileset_size
        x = sx/sw*w
        y = sy/sh*h
        variant = layer.tileset.get_variant_from_coord([x, y])
        self.panel.panel.editor.selected_variant = variant+1

    def mouse_up(self, *args, **kwargs):
        pass



class LayerSettings(SubPanel):

    def __init__(self, panel):
        super().__init__(panel)
        m = self.get_margin()
        w = self.get_width()
        self.layer_name_box = TextBox(m, m+40, w-2*m, 32, 'Layer name:', '<name>', on_edit=self.on_layername_edit)
        self.tileset_path_box = TextBox(m, m+100, w-2*m, 32, 'Tileset path:', '<path>', on_deactivate=self.on_tilepath_edit)
        self.back_button = Button(m, 500 - 32 - m, w/2-m, 32, 'Back', self.back)
        self.picker = PalettePicker(self)
        self.clickables = [self.layer_name_box, self.tileset_path_box, self.back_button, self.picker]
        self.typeables = [self.layer_name_box, self.tileset_path_box]
        s = w -m*2
        self.tileset_position = (m, m+150)
        self.scaled_tileset_size = (s, s)

    def key_down(self, **kwargs):
        for typeable in self.typeables:
            if typeable.active:
                typeable.key_down(**kwargs)

    def mouse_up(self, button, pos):
        for clickable in self.clickables:
            clickable.mouse_up(button, pos)

    def mouse_down(self, button, pos):
        for clickable in self.clickables:
            clickable.mouse_down(button, pos)

    def on_show(self):
        i = self.panel.editor.selected_layer
        layer = self.panel.editor.room.layers[i]
        self.layer_name_box.text = layer.name
        self.tileset_path_box.text = layer.tileset.path

    def on_layername_edit(self, name):
        i = self.panel.editor.selected_layer
        self.panel.editor.room.layers[i].name = name

    def on_tilepath_edit(self, path):
        i = self.panel.editor.selected_layer
        self.panel.editor.room.layers[i].set_tileset(path)

    def back(self):
        self.panel.show_panel('room_settings')
