from side_panel.widget_collection import WidgetCollection

class SubPanel(WidgetCollection):

    def __init__(self, panel):
        self.panel = panel
        super().__init__()

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

    def on_show(self):
        pass

    def on_hide(self):
        pass
