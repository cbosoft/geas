from side_panel.sub_panel import SubPanel
from side_panel.uielements.textbox import TextBox
from side_panel.uielements.button import Button

class LoadSavePanel(SubPanel):

    def __init__(self, panel):
        super().__init__(panel)

        self.clickables = list()

        m = self.get_margin()
        self.filename_box = TextBox(m, m+40, self.get_width() - 2*m, 32, 'Room path:', '<filename>')

        self.load_button = Button(
            m, self.filename_box.pos[1]+45,
            self.get_width()/2 - 2*m, 32, 'Load', self.load)
        self.save_button = Button(
            m+self.get_width()/2,
            self.filename_box.pos[1]+45,
            self.get_width()/2 - 2*m, 32, 'Save', self.save)
        self.new_button = Button(
            m,
            self.save_button.pos[1]+45,
            self.get_width() - 2*m, 32, 'New', self.new)
        self.quit_button = Button(
            m, self.get_height() - m - 32,
            self.get_width()/2 - 2*m, 32, 'Quit', self.quit)
        self.edit_button = Button(
            m+self.get_width()/2,
            self.get_height() - m - 32,
            self.get_width()/2 - 2*m, 32, 'Edit Room', self.edit)

        self.typeables = [self.filename_box]
        self.clickables = [self.load_button, self.save_button, self.new_button, self.quit_button, self.edit_button]

    def load(self):
        path = self.filename_box.text
        try:
            self.panel.editor.load(path)
        except Exception as e:
            print(f'Encountered error: {e}')

    def save(self):
        path = self.filename_box.text
        print(f'would save to {path} but not implemented')

    def new(self):
        self.panel.editor.new()

    def quit(self):
        self.panel.editor.quit()

    def edit(self):
        self.panel.show_panel('room_settings')
