from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.tabbedpanel import TabbedPanelItem
from kivy.lang import Builder
from kivy.graphics import Color 
from kivy.graphics import RoundedRectangle
from kivy.properties import ColorProperty
from kivy.core.text import LabelBase

class Tab(TabbedPanelItem):

    def on_active(self):
        print('ativo')

class InterfaceButton(Button):
    bg_color = ColorProperty("#697565")

    def alter_color_button(self, color):
        self.bg_color = color

class MainLayout(BoxLayout):
    ratio = 0.3

    def __init__(self, **args):
        super(MainLayout, self).__init__(**args)
    
    def generate(self):
        print('gerar')
    
class Generator(App):

    def build(self):
        return self.root
    
LabelBase.register(name='Roboto-Black', fn_regular='Roboto-Black.ttf')
LabelBase.register(name='Roboto-Bold', fn_regular='Roboto-Bold.ttf')

Generator().run()