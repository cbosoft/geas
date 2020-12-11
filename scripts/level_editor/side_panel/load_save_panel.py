from side_panel.sub_panel import SubPanel
from side_panel.uielements.textbox import TextBox
from side_panel.uielements.button import Button

class LoadSavePanel(SubPanel):

    def __init__(self, panel):
        super().__init__(panel)

        self.clickables = list()

        m = self.get_margin()
        self.filename_box = TextBox(m, m+40, self.get_width() - 2*m, 32, 'Room path:', '<filename>')
        self.clickables.append(self.filename_box)

        self.load_button = Button(
            m, self.filename_box.pos[1]+45,
            self.get_width()/2 - 2*m, 32, 'Load', self.load)
        self.clickables.append(self.load_button)
        self.save_button = Button(
            m+self.get_width()/2,
            self.filename_box.pos[1]+45,
            self.get_width()/2 - 2*m, 32, 'Save', self.save)
        self.clickables.append(self.save_button)

        self.quit_button = Button(
            m, self.get_height() - m - 32,
            self.get_width()/2 - 2*m, 32, 'Quit', self.quit)
        self.clickables.append(self.quit_button)
        self.edit_button = Button(
            m+self.get_width()/2,
            self.get_height() - m - 32,
            self.get_width()/2 - 2*m, 32, 'Edit Room', self.edit)
        self.clickables.append(self.edit_button)

    def key_down(self, **kwargs):
        if self.filename_box.active:
            self.filename_box.key_down(**kwargs)

    def mouse_up(self, button, pos):
        for clickable in self.clickables:
            clickable.mouse_up(button, pos)

    def mouse_down(self, button, pos):
        for clickable in self.clickables:
            clickable.mouse_down(button, pos)

    def load(self):
        path = self.filename_box.text
        try:
            self.panel.editor.load(path)
        except Exception as e:
            print(f'Encountered error: {e}')

    def save(self):
        path = self.filename_box.text
        print(f'would save to {path} but not implemented')

    def quit(self):
        self.panel.editor.quit()

    def edit(self):
        self.panel.current_panel = self.panel.panels['room_settings']
