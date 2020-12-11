from side_panel.uielements.button import Button

class LayerButtonSet:

    def __init__(self, panel, layername, i, miny):
        self.panel = panel
        self.name = layername
        self.layer_edit_button = Button(0, 0, 10, 10, self.name, self.edit)
        self.layer_delete_button = Button(0, 0, 10, 10, '-', self.delete)
        self.buttons = [self.layer_edit_button, self.layer_delete_button]
        self.index = i
        self.update_position(miny)

    def update_position(self, miny):
        x = self.panel.get_margin()
        w = self.panel.get_width() - x*3
        w1 = w*0.9
        w2 = w - w1
        h = 40
        y = miny + (h+5)*self.index
        self.layer_edit_button.pos = [x, y]
        self.layer_edit_button.size = [w1, h]
        self.layer_delete_button.pos = [x+w1+x, y]
        self.layer_delete_button.size = [w2, h]

    def edit(self):
        self.panel.edit_layer(self.index)

    def delete(self):
        self.panel.delete_layer(self.index)

    def mouse_up(self, button, pos):
        for clickable in self.buttons:
            clickable.mouse_up(button, pos)

    def mouse_down(self, button, pos):
        for clickable in self.buttons:
            clickable.mouse_down(button, pos)
