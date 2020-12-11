class TextBox:

    def __init__(self, x, y, w, h, title, text,
                 text_colour=(255, 255, 255),
                 bg_colour=(0, 0, 0)):
        self.pos = x, y
        self.size = w, h
        self.title = title
        self.text = text
        self.active = False
        self.text_colour = text_colour
        self.bg_colour = bg_colour

    def mouse_up(self, button, pos):
        if button == 1:
            x_okay = self.pos[0] < pos[0] < (self.pos[0] + self.size[0])
            y_okay = self.pos[1] < pos[1] < (self.pos[1] + self.size[1])
            self.active = x_okay and y_okay

    def mouse_down(self, button, pos):
        pass

    def key_down(self, *, unicode, mod, **kwargs):
        if not self.active:
            return

        if not unicode and self.text:
            self.text = self.text[:-1]
        else:
            self.text = self.text + unicode
