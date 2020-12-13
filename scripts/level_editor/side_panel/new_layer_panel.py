from side_panel.sub_panel import SubPanel
from side_panel.uielements.button import Button
from side_panel.uielements.textbox import TextBox


class NewLayerPanel(SubPanel):

    def __init__(self, panel):
        super().__init__(panel)

        m = self.get_margin()
        w = self.get_width()

        self.name_box = TextBox(m, m+50, 200, 32, 'Name:', '')
        self.path_box = TextBox(m, m+100, 200, 32, 'Path:', '')
        self.cancel_button = Button(m, m+200, w/2-2*m, 50, 'Cancel', self.cancel)
        self.accept_button = Button(m+w/2, m+200, w/2-2*m, 50, 'Accept', self.accept)
        self.typeables = [self.name_box, self.path_box]
        self.clickables = [self.cancel_button, self.accept_button]

        self.accepted = False

    def on_show(self):
        self.name_box.text = ''
        self.path_box.text = ''

    def accept(self):
        self.accepted = True
        self.panel.show_panel('room_settings')

    def cancel(self):
        self.accepted = False
        self.panel.show_panel('room_settings')

    def on_hide(self):
        if self.accepted:
            self.panel.editor.new_layer(self.name_box.text, self.path_box.text)

