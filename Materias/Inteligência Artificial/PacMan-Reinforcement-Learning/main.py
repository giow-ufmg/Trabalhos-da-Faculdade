import numpy as np
import sys

# Programando o Pacman
ghost_char = '&'
pill_char = '0'
wall_char = '#'
terrain_char = '-'
CAN_MOVE = 1
CANNOT_MOVE = 0
UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3


class Pacmaze:
    map = None
    rewards = None
    q_values = {}

    possible_mov = []

    width = None
    height = None

    ghost = []
    pill = []

    def inside_map(self, x, y):
        if x > 0 and y > 0:
            if x < self.width and y < self.height:
                return True
        return False

    def valid_movement(self, x, y):
        if self.inside_map(x, y):
            return True
        else:
            return False

    def get_poss_next_states(self, x, y):
        poss_next_states = []

        if self.valid_movement(x, y - 1):  # LEFT
            poss_next_states.append((x, y - 1, LEFT))
        if self.valid_movement(x, y + 1):  # RIGHT
            poss_next_states.append((x, y + 1, RIGHT))
        if self.valid_movement(x - 1, y):  # UP
            poss_next_states.append((x - 1, y, UP))
        if self.valid_movement(x + 1, y):  # DOWN
            poss_next_states.append((x + 1, y, DOWN))
        return poss_next_states

    def get_rnd_next_state(self, x, y):
        poss_next_states = self.get_poss_next_states(x, y)
        next_state = poss_next_states[np.random.randint(0, len(poss_next_states))]
        return next_state

    def init_map(self):
        self.map = np.zeros(shape=[self.width, self.height], dtype=np.int)
        self.rewards = np.zeros(shape=[self.width, self.height], dtype=np.int)

    # I'm going to make a dict
    #           up down left right
    # (x,y) =  (Q)  (Q)  (Q)   (Q)

    """ Le o mapa do Pacman """

    def read_from_file(self, rel_filepath):
        # Abrindo o arquivo
        with open(rel_filepath) as file:
            self.width, self.height = [int(x) for x in next(file).split()]
            self.init_map()
            # Seta os valores no mapa
            for i, line in enumerate(file):
                line = line.strip("\n")
                for j, obj in enumerate(line):
                    self.q_values[(i, j)] = [0.0, 0.0, 0.0, 0.0]

                    if obj == ghost_char:
                        print("Fantasma em: ", "[", i, "]", "[", j, "]")
                        self.ghost.append((i, j))  # adiciona aos goals
                        self.map[i][j] = CAN_MOVE  # pode mover
                        self.rewards[i][j] = -10  # reward do estado
                    elif obj == pill_char:
                        print("Pilula em: ", "[", i, "]", "[", j, "]")
                        self.pill.append((i, j))
                        self.map[i][j] = CAN_MOVE
                        self.rewards[i][j] = 10

                    elif obj == terrain_char:
                        self.map[i][j] = CAN_MOVE
                        self.rewards[i][j] = -1
                        self.possible_mov.append((i, j))
                    else:
                        self.map[i][j] = CANNOT_MOVE
                        self.rewards[i][j] = -1

    def visualize_state(self, x, y):
        print("*" * 10)
        for i, row in enumerate(self.map):
            for j, col in enumerate(row):
                if i == x and j == y:
                    print("[" + str(col) + "]", end=" ")
                else:
                    print(col, end=" ")
            print('\n')
        print("*" * 10)

    def train(self, gamma, lrn_rate, max_epochs):
        for i in range(0, max_epochs):
            # print(i)
            rnd_state = np.random.randint(0, len(self.possible_mov))  # random start state
            curr_s = self.possible_mov[rnd_state]
            # self.visualize_state(curr_s[0], curr_s[1])
            while True:
                next_s = self.get_rnd_next_state(curr_s[0], curr_s[1])
                if self.map[next_s[0], next_s[1]] == 0:
                    self.q_values[curr_s[:2]][next_s[2]] = ((1 - lrn_rate) * self.q_values[curr_s[:2]][next_s[2]]) + \
                                                           (lrn_rate * (self.rewards[next_s[0]][next_s[1]] + (
                                                                   gamma * -1)))
                    continue

                poss_next_next_states = self.get_poss_next_states(next_s[0], next_s[1])

                # print("NEXT STATE:")
                # self.visualize_state(next_s[0], next_s[1])
                # print("NEXT NEXT STATE:")
                # self.visualize_state(next_s[0], next_s[1])
                max_Q = -9999.99
                for j in range(len(poss_next_next_states)):
                    nn_s = poss_next_next_states[j]
                    q = self.q_values[next_s[:2]][nn_s[2]]
                    if q > max_Q:
                        max_Q = q

                # Q = [(1-a) * Q]  +  [a * (rt + (g * maxQ))]
                self.q_values[curr_s[:2]][next_s[2]] = ((1 - lrn_rate) * self.q_values[curr_s[:2]][next_s[2]]) + \
                                                       (lrn_rate * (self.rewards[next_s[0]][next_s[1]] + (
                                                               gamma * max_Q)))

                # If it is a wall
                if self.map[next_s[0], next_s[1]] == 0:
                    self.q_values[curr_s[:2]][next_s[2]] = ((1 - lrn_rate) * self.q_values[curr_s[:2]][next_s[2]]) + \
                                                           (lrn_rate * (self.rewards[next_s[0]][next_s[1]] + (
                                                                   gamma * -1)))
                    continue
                curr_s = next_s
                if curr_s[:2] in self.pill or curr_s[:2] in self.ghost:
                    break

    def walk(self, x, y):
        # go to goal from start using Q
        curr = (x, y)
        print(str(curr) + "->", end="")
        while (1):
            # print("UP\tDOWN\tLEFT\tRIGHT")
            # print(self.q_values[curr])
            index = np.argmax(self.q_values[curr])
            if index == UP:
                next = (curr[0] - 1, curr[1])
            elif index == DOWN:
                next = (curr[0] + 1, curr[1])
            elif index == LEFT:
                next = (curr[0], curr[1] - 1)
            else:
                next = (curr[0], curr[1] + 1)
            print(str(next) + "->", end="")
            curr = next
            if curr in self.pill:
                break
            if curr in self.ghost:
                break

        print("done")

    def print_direction_map_to_file(self):
        with open("pi.txt", 'w') as file:
            for i, row in enumerate(self.map):
                for j, col in enumerate(row):
                    if self.map[i, j] == 0:
                        print("#", end="", file=file)
                        continue
                    if (i, j) in self.pill:
                        print("0", end="", file=file)
                        continue
                    if (i, j) in self.ghost:
                        print("&", end="", file=file)
                        continue

                    index = np.argmax(self.q_values[(i, j)])
                    if index == UP:
                        print("U", end="", file=file)
                    elif index == DOWN:
                        print("D", end="", file=file)
                    elif index == LEFT:
                        print("L", end="", file=file)
                    else:
                        print("R", end="", file=file)
                print(file=file)

    def print_states_to_file(self):
        direction = None
        with open("q.txt", 'w') as file:
            for i, row in enumerate(self.map):
                for j, col in enumerate(row):
                    if self.map[i, j] == 0:
                        continue
                    if (i, j) in self.pill:
                        continue
                    if (i, j) in self.ghost:
                        continue

                    index = np.argmax(self.q_values[(i, j)])

                    if index == UP:
                        direction = "U"
                    elif index == DOWN:
                        direction = "D"
                    elif index == LEFT:
                        direction = "L"
                    else:
                        direction = "R"

                    file.write(
                        str(i) + "," + str(j) + "," + direction + str(round(self.q_values[(i, j)][index], 3)) + "\n")


def read_arguments():
    gamma = None
    lrn_rate = None
    max_epochs = None
    file = None
    print(len(sys.argv[1:]))
    if len(sys.argv[1:]) < 4:
        print("Not enough arguments")
        print("Try: file pacmaze arg arg arg")
        exit()
    for i, arg in enumerate(sys.argv[1:]):
        if i == 0:
            print("arg", arg)
            file = arg
            print(file)
        elif i == 1:
            print("arg", arg)
            gamma = float(arg)
            print(gamma)
        elif i == 2:
            print("arg", arg)
            lrn_rate = float(arg)
            print(lrn_rate)
        else:
            max_epochs = int(arg)
    return file, gamma, lrn_rate, max_epochs


def main(argv):
    gamma = 0.9
    lrn_rate = 0.9
    max_epochs = 10000
    file_path = "pacmaze-01-tiny.txt"

    print("Reading Arguments")
    file_path, gamma, lrn_rate, max_epochs = read_arguments()

    print("Reading file")
    pacmaze = Pacmaze()
    pacmaze.read_from_file(file_path)

    print("Training")
    pacmaze.train(gamma, lrn_rate, max_epochs)

    print("Printing to files")
    pacmaze.print_direction_map_to_file()
    pacmaze.print_states_to_file()


if __name__ == "__main__":
    main(sys.argv[1:])
