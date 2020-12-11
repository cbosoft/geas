from side_panel.sub_panel import SubPanel

class TilePalette(SubPanel):

    def __init__(self, panel):
        super().__init__(panel)

    def get_brush(self):
        # TODO: look up current brush in editor and get respective image from tileset
        return None
