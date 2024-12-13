import pygame
from snake import Snake
from game import Game
pygame.init()

background_color = (104, 166, 67)

pygame.display.set_caption("Snake Game")
surface = pygame.display.set_mode((1080, 720))
surface.fill(background_color)

snake = Snake(surface, 7, background_color)
game = Game(surface, background_color)

game.run()
