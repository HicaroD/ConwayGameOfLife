from random import randint

WIDTH = 64
HEIGHT = 32

def generate_random_pair_of_numbers():
    x = randint(1, WIDTH)
    y = randint(1, HEIGHT)
    return x, y

def main():
    number_of_coordinates = int(input("How many coordinates do you want? "))

    with open("seed.txt", "w") as f:
        for _ in range(number_of_coordinates):
            x, y = generate_random_pair_of_numbers()
            f.write(f"{x} {y}\n")



if __name__ == "__main__":
    main()
