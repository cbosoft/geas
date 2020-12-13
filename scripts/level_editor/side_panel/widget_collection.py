class WidgetCollection:

    def __init__(self):
        self.clickables = list()
        self.typeables = list()

    def key_down(self, **kwargs):
        for typeable in self.typeables:
            if typeable.active:
                typeable.key_down(**kwargs)

    def mouse_up(self, button, pos):
        for clickable in [*self.clickables, *self.typeables]:
            clickable.mouse_up(button, pos)

    def mouse_down(self, button, pos):
        for clickable in [*self.clickables, *self.typeables]:
            clickable.mouse_down(button, pos)

    def get_widgets(self):
        return [*self.clickables, *self.typeables]
