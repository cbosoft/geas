class Button:

    def __init__(self, x, y, w, h, text, callback):
        self.pos = x, y
        self.size = w, h
        self.text = text
        self.callback = callback
        self.bg_colour = [0, 0, 0]
        self.text_colour = [255, 255, 255]
        self.pushed_colour = [155, 155, 155]
        self.pushed = False

    def mouse_up(self, button, pos):
        if button == 1 and self.pushed:
            x_okay = self.pos[0] < pos[0] < (self.pos[0] + self.size[0])
            y_okay = self.pos[1] < pos[1] < (self.pos[1] + self.size[1])
            if x_okay and y_okay:
                self.callback()
        self.pushed = False

    def mouse_down(self, button, pos):
        if button == 1:
            x_okay = self.pos[0] < pos[0] < (self.pos[0] + self.size[0])
            y_okay = self.pos[1] < pos[1] < (self.pos[1] + self.size[1])
            if x_okay and y_okay:
                self.pushed = True
