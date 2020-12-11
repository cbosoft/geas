from side_panel.sub_panel import SubPanel
from side_panel.uielements.textbox import TextBox

class LoadSavePanel(SubPanel):

    def __init__(self, panel):
        super().__init__(panel)

        m = self.get_margin()
        self.filename_box = TextBox(m, m, self.get_width() - 2*m, 20, '<filename>')

    def key_down(self, **kwargs):
        if self.filename_box.active:
            self.filename_box.key_down(**kwargs)

    def mouse_up(self, button, pos):
        self.filename_box.mouse_up(button, pos)
