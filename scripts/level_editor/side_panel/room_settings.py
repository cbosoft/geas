from side_panel.sub_panel import SubPanel
from side_panel.uielements.textbox import TextBox
from side_panel.layerlist import LayerButtonSet
from side_panel.uielements.button import Button

class RoomSettings(SubPanel):

    def __init__(self, panel):
        super().__init__(panel)
        m = self.get_margin()
        w = self.get_width()
        self.room_name_box = TextBox(m, m+40, w-2*m, 32, 'Room name:', '<name>')
        self.back_button = Button(m, 500 - 32 - m, w/2-m, 32, 'Back', self.back)
        self.clickables = [self.room_name_box, self.back_button]
        self.layer_buttons = []

    def back(self):
        self.panel.current_panel = self.panel.panels['load_save']

    def key_down(self, **kwargs):
        if self.room_name_box.active:
            self.room_name_box.key_down(**kwargs)

    def mouse_up(self, button, pos):
        for clickable in [*self.clickables, *self.layer_buttons]:
            clickable.mouse_up(button, pos)

    def mouse_down(self, button, pos):
        for clickable in [*self.clickables, *self.layer_buttons]:
            clickable.mouse_down(button, pos)

    def set_room_name(self, name):
        self.panel.editor.room.name = name

    def update_layers(self):
        layers = self.panel.editor.room.layers
        for i, layer in enumerate(layers):
            self.layer_buttons.append(LayerButtonSet(self, layer.name, i, 100))

    def edit_layer(self, i):
        # TODO check i is a valid layer index
        self.panel.editor.selected_layer = i
        self.panel.current_panel = self.panel.panels['layer_settings']
        name = self.panel.editor.room.layers[i].name
        print(f'selected_layer = {i}:{name}')

    def delete_layer(self, i):
        print(f'Tried to delete {i}, not sure I want to include delete in editor so no doing anything')
