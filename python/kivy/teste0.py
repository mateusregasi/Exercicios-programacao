import kivy

from kivy.app import App
from kivy.uix.label import Label

# Como funciona um app simples em kivy?

# 1) Você faz uma subclasse de App
# 2) Implementa o método build que retorna uma instância de Widget (que vai ser a raiz do seu projeto, a classe que vai conter a estrutura do app em si)
# 3) Chama o método run() da classe

class Aplicativo(App):

    def build(self):
        return Label(text='Hello world')

meuapp = Aplicativo()
meuapp.run()