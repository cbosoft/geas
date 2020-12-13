from side_panel.room_settings import RoomSettings
from side_panel.layer_settings import LayerSettings
from side_panel.tile_palette import TilePalette
from side_panel.load_save_panel import LoadSavePanel
from side_panel.new_layer_panel import NewLayerPanel

class SettingsPanel:

    def __init__(self, editor):
        self.editor = editor

        self.margin = 10
        self.brush_size = 64
        self.width = 300
        self.height = 500

        self.bg_colour = [50, 50, 50]
        self.text_colour = [200, 200, 200]

        self.panels = {
            'load_save': LoadSavePanel(self),
            'room_settings': RoomSettings(self),
            'layer_settings': LayerSettings(self),
            'tile_palette': TilePalette(self),
            'new_layer': NewLayerPanel(self),
        }
        self.current_panel = self.panels['load_save']

    def mouse_down(self, button, pos):
        self.current_panel.mouse_down(button, pos)

    def mouse_up(self, button, pos):
        self.current_panel.mouse_up(button, pos)

    def key_down(self, **kwargs):
        self.current_panel.key_down(**kwargs)

    def show_panel(self, name):
        self.current_panel.on_hide()
        self.current_panel = self.panels[name]
        self.current_panel.on_show()
