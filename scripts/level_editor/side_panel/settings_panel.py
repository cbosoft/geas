from side_panel.room_settings import RoomSettings
from side_panel.layer_settings import LayerSettings
from side_panel.tile_palette import TilePalette
from side_panel.load_save_panel import LoadSavePanel

class SettingsPanel:

    def __init__(self, editor):
        self.editor = editor

        self.margin = 10
        self.brush_size = 64
        self.width = 100

        self.bg_colour = [50, 50, 50]
        self.text_colour = [200, 200, 200]


        self.panels = {
            'load_save': LoadSavePanel(self),
            'room_settings': RoomSettings(self),
            'layer_settings': LayerSettings(self),
            'tile_palette': TilePalette(self)
        }
        self.current_panel = self.panels['load_save']

    def set_brush(self, img):
        #self.brush = pg.transform.scale(img, [self.brush_size, self.brush_size])
        pass

    def set_selected_layer(self, layer_index, tileset):
        # if layer_index == 'all':
        #     self.brush = None
        #     self.selected_layer_index = -1
        # else:
        #     self.selected_layer_index = layer_index
        # self.selected_layer = self.font.render(f'Selected layer: {layer_index}', True, (255, 255, 255))
        # self.tileset = tileset
        pass

    def contains(self, pos):
        return self.panel.get_rect().collidepoint(np.subtract(pos, self.panel.get_abs_offset()))

    def mouse_down(self, button, pos):
        self.current_panel.mouse_down(button, pos)

    def mouse_up(self, button, pos):
        # if button == 1 and self.tileset:
        #     try:
        #         pos_relative_to_tileset = [pos[0] - self.margin, pos[1] - self.panel.get_height() + self.tileset_width]
        #         self.editor.select_tile(self.tileset.get_variant_from_coord(pos_relative_to_tileset)+1)
        #     except Exception as e:
        #         print(f'something went wrong: {e}')
        self.current_panel.mouse_up(button, pos)

    def key_down(self, **kwargs):
        self.current_panel.key_down(**kwargs)
