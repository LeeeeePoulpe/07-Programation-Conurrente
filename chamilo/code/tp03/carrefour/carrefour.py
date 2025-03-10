import pygame
import sys
import random
from enum import Enum
import time

# Constants
WINDOW_SIZE = (800, 600)
ROAD_WIDTH = 60
CAR_SIZE = (40, 20)
LIGHT_RADIUS = 10
FPS = 60

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
YELLOW = (255, 255, 0)

# Set random seed for consistent colors
random.seed(42)

class Direction(Enum):
    PRINCIPALE = "PRINCIPALE"
    SECONDAIRE = "SECONDAIRE"

class TrafficLight:
    def __init__(self):
        self.principale = "VERT"
        self.secondaire = "ROUGE"
    
    def update(self, road, color):
        if road == Direction.PRINCIPALE.value:
            self.principale = color
        else:
            self.secondaire = color

class Car:
    def __init__(self, direction, number):
        self.direction = direction
        self.number = number
        self.color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
        self.state = "ARRIVE"
        
        # Position initialization
        if direction == Direction.PRINCIPALE:
            self.x = 0
            self.y = WINDOW_SIZE[1]//2 - CAR_SIZE[1]//2
            self.target_x = WINDOW_SIZE[0]//2 - ROAD_WIDTH
        else:
            self.x = WINDOW_SIZE[0]//2 - CAR_SIZE[0]//2
            self.y = 0
            self.target_y = WINDOW_SIZE[1]//2 - ROAD_WIDTH

    def move(self):
        speed = 5
        if self.direction == Direction.PRINCIPALE:
            if self.state == "ARRIVE" and self.x < self.target_x:
                self.x += speed
            elif self.state == "TRAVERSE":
                self.x += speed
        else:
            if self.state == "ARRIVE" and self.y < self.target_y:
                self.y += speed
            elif self.state == "TRAVERSE":
                self.y += speed

    def is_in_intersection(self):
        if self.direction == Direction.PRINCIPALE:
            return (WINDOW_SIZE[0]//2 - ROAD_WIDTH <= self.x <= WINDOW_SIZE[0]//2 + ROAD_WIDTH)
        else:
            return (WINDOW_SIZE[1]//2 - ROAD_WIDTH <= self.y <= WINDOW_SIZE[1]//2 + ROAD_WIDTH)

class Simulation:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode(WINDOW_SIZE)
        pygame.display.set_caption("Carrefour Simulation")
        self.clock = pygame.time.Clock()
        
        self.cars = {}
        self.traffic_light = TrafficLight()
        self.running = True
        self.error_message = None

    def draw_roads(self):
        # Main road
        pygame.draw.rect(self.screen, BLACK, 
                        (0, WINDOW_SIZE[1]//2 - ROAD_WIDTH, WINDOW_SIZE[0], ROAD_WIDTH*2))
        # Secondary road
        pygame.draw.rect(self.screen, BLACK,
                        (WINDOW_SIZE[0]//2 - ROAD_WIDTH, 0, ROAD_WIDTH*2, WINDOW_SIZE[1]))

    def draw_traffic_lights(self):
        # Main road light
        color = GREEN if self.traffic_light.principale == "VERT" else \
                YELLOW if self.traffic_light.principale == "ORANGE" else RED
        pygame.draw.circle(self.screen, color,
                         (WINDOW_SIZE[0]//2 - ROAD_WIDTH - 20, WINDOW_SIZE[1]//2 - ROAD_WIDTH - 20),
                         LIGHT_RADIUS)
        
        # Secondary road light
        color = GREEN if self.traffic_light.secondaire == "VERT" else \
                YELLOW if self.traffic_light.secondaire == "ORANGE" else RED
        pygame.draw.circle(self.screen, color,
                         (WINDOW_SIZE[0]//2 - ROAD_WIDTH - 20, WINDOW_SIZE[1]//2 - ROAD_WIDTH - 40),
                         LIGHT_RADIUS)

    def draw_cars(self):
        for car in self.cars.values():
            if car.state != "QUITTE" or (car.direction == Direction.PRINCIPALE and car.x < WINDOW_SIZE[0]) or \
               (car.direction == Direction.SECONDAIRE and car.y < WINDOW_SIZE[1]):
                rect = pygame.Rect(car.x, car.y, CAR_SIZE[0], CAR_SIZE[1])
                pygame.draw.rect(self.screen, car.color, rect)

    def check_collision(self):
        cars_in_intersection = [car for car in self.cars.values() if car.is_in_intersection()]
        if len(cars_in_intersection) > 1:
            self.error_message = "ERROR: Multiple cars in intersection!"
            self.running = False

    def check_traffic_rules(self, car):
        if car.state == "TRAVERSE":
            if (car.direction == Direction.PRINCIPALE and self.traffic_light.principale == "ROUGE") or \
               (car.direction == Direction.SECONDAIRE and self.traffic_light.secondaire == "ROUGE"):
                self.error_message = f"ERROR: Car {car.direction.value} {car.number} crossed on red light!"
                self.running = False

    def process_input(self, line):
        parts = line.strip().split()
        if len(parts) < 2:
            return

        direction = parts[0]
        if parts[1] == "FEU":
            self.traffic_light.update(direction, parts[2])
        else:
            car_num = int(parts[1])
            action = parts[2]
            
            if action == "ARRIVE":
                self.cars[f"{direction}_{car_num}"] = Car(Direction[direction], car_num)
            elif action == "TRAVERSE":
                if f"{direction}_{car_num}" in self.cars:
                    self.cars[f"{direction}_{car_num}"].state = "TRAVERSE"
            elif action == "QUITTE":
                if f"{direction}_{car_num}" in self.cars:
                    self.cars[f"{direction}_{car_num}"].state = "QUITTE"

    def run(self):
        while self.running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    return

            # Process input
            if not sys.stdin.isatty():  # Check if there's input available
                line = sys.stdin.readline()
                if not line:  # EOF
                    time.sleep(2)  # Wait to see final state
                    return
                self.process_input(line)

            # Update
            for car in self.cars.values():
                car.move()
                self.check_traffic_rules(car)
            self.check_collision()

            # Draw
            self.screen.fill(WHITE)
            self.draw_roads()
            self.draw_traffic_lights()
            self.draw_cars()
            
            if self.error_message:
                font = pygame.font.Font(None, 36)
                text = font.render(self.error_message, True, RED)
                self.screen.blit(text, (10, 10))

            pygame.display.flip()
            self.clock.tick(FPS)

        # Keep window open for a moment after error
        time.sleep(2)

if __name__ == "__main__":
    simulation = Simulation()
    simulation.run()
    pygame.quit()
