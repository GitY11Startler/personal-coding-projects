import pygame
from food import Food


class Snake:
    SIZE = 40

    def __init__(self, surface, length, background_color):
        self.background_color = background_color
        self.length = length
        self.surface = surface
        self.food = Food(self.surface)

        self.image = pygame.image.load("C:\\Users\\DELL\\PycharmProjects\\pythonProject\\New App\\Assets\\Snake Block.png")
        self.image = pygame.transform.scale(self.image, (self.SIZE, self.SIZE))

        self.x = [self.SIZE] * length
        self.y = [self.SIZE] * length
        self.direction = "down"

    def increase_length(self):
        self.length += 1
        self.x.append(-1)
        self.y.append(-1)

    def walk(self):
        for i in range(self.length - 1, 0, -1):
            self.x[i] = self.x[i - 1]
            self.y[i] = self.y[i - 1]

        if self.direction == "down":
            self.y[0] += self.SIZE

        elif self.direction == "up":
            self.y[0] -= self.SIZE

        elif self.direction == "right":
            self.x[0] += self.SIZE

        elif self.direction == "left":
            self.x[0] -= self.SIZE

        self.draw()

    def draw(self):
        self.surface.fill(self.background_color)
        for i in range(self.length):
            self.surface.blit(self.image, (self.x[i], self.y[i]))
        pygame.display.flip()

    def move_up(self):
        self.direction = "up"

    def move_down(self):
        self.direction = "down"

    def move_left(self):
        self.direction = "left"

    def move_right(self):
        self.direction = "right"
