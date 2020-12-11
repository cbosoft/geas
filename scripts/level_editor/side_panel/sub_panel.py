class SubPanel:

    def __init__(self, panel):
        self.panel = panel

    def get_font_name(self):
        return self.panel.font_name

    def get_font_size(self):
        return self.panel.font_size

    def get_text_colour(self):
        return self.panel.text_colour

    def get_height(self):
        return self.panel.height

    def get_width(self):
        return self.panel.width

    def get_brush_size(self):
        return self.panel.brush_size

    def get_margin(self):
        return self.panel.margin

    def key_down(self, **kwargs):
        pass

    def mouse_down(self, button, pos):
        pass

    def mouse_up(self, button, pos):
        pass
