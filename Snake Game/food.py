import random
import pygame


class Food:
    SIZE = 40

    def __init__(self, surface):
        self.surface = surface
        self.image = pygame.image.load("C:\\Users\\DELL\\PycharmProjects\\pythonProject\\New App\\Assets\\Food.jpg")

        self.x = random.randint(1, 26) * self.SIZE
        self.y = random.randint(1, 17) * self.SIZE

    def draw(self):
        self.surface.blit(self.image, (self.x, self.y))
        pygame.display.flip()

    def move(self):
        self.x = random.randint(1, 26) * self.SIZE
        self.y = random.randint(1, 17) * self.SIZE
