import pygame
from Utils import *


class InputBox:
    def __init__(self, position=(0, 0), size=(0, 0), text='', func=None):
        self.surf = pygame.Surface(size)
        self.initial_width = size[0]
        self.rect = self.surf.get_rect(center=position)
        self.color = COLOR_INACTIVE
        self.text = text
        self.font = pygame.font.SysFont("Segoe Print", 16)
        self.txt_surface = self.font.render(text, True, self.color)
        self.active = False
        self.func = func

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            # If the user clicked on the input_box rect.
            if self.rect.collidepoint(event.pos):
                # Toggle the active variable.
                self.active = not self.active
            else:
                self.active = False
            # Change the current color of the input box.
            self.color = COLOR_ACTIVE if self.active else COLOR_INACTIVE
        if event.type == pygame.KEYDOWN:
            if self.active:
                if event.key == pygame.K_RETURN:
                    self.call_back(self.text)
                    self.rect.w = self.initial_width
                    # self.text = ''
                elif event.key == pygame.K_BACKSPACE:
                    self.text = self.text[:-1]
                else:
                    self.text += event.unicode
                # Re-render the text.
                self.txt_surface = self.font.render(self.text, True, self.color)

    def update(self):
        # Resize the box if the text is too long.
        width = max(self.rect.w, self.txt_surface.get_width()+10)
        self.rect.w = width

    def draw(self, screen):
        # Blit the text.
        screen.blit(self.txt_surface, (self.rect.x+5, self.rect.y+5))
        # Blit the rect.
        pygame.draw.rect(screen, self.color, self.rect, 2)

    def call_back(self, *args):
        if self.func:
            return self.func(*args)
