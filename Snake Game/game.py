import time

import pygame
from snake import Snake
from food import Food


class Game:
    SIZE = 40

    def __init__(self, surface, background_color):
        self.background_color = background_color
        self.surface = surface
        self.snake = Snake(surface, 7, background_color)
        self.food = Food(surface)

    def check_game_over(self):
        for i in range(3, self.snake.length):

            if self.is_collision(self.snake.x[0], self.snake.y[0], self.snake.x[i], self.snake.y[i]):
                exit(0)

    def is_collision(self, x1, y1, x2, y2):
        if x2 <= x1 < x2 + self.SIZE and y2 <= y1 < y2 + self.SIZE:
            return True
        return False

    def play(self):
        self.snake.walk()
        self.food.draw()
        self.check_game_over()
        pygame.display.flip()

        if self.is_collision(self.snake.x[0], self.snake.y[0], self.food.x, self.food.y):
            self.snake.increase_length()
            self.food.move()

    def run(self):

        running = True
        while running:

            for event in pygame.event.get():

                if event.type == pygame.QUIT:
                    running = False

                elif event.type == pygame.KEYDOWN:

                    if event.key == pygame.K_RIGHT:
                        self.snake.move_right()

                    elif event.key == pygame.K_LEFT:
                        self.snake.move_left()

                    elif event.key == pygame.K_UP:
                        self.snake.move_up()

                    elif event.key == pygame.K_DOWN:
                        self.snake.move_down()

            self.play()
            time.sleep(0.09)
