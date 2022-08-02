from random import randint

WIDTH = 100
HEIGHT = 70

def generate_random_pair_of_numbers():
    x = randint(0, WIDTH)
    y = randint(0, HEIGHT)
    return x, y

def main():
    number_of_coordinates = int(input("How many coordinates do you want? "))

    with open("seed.txt", "w") as f:
        for _ in range(number_of_coordinates):
            x, y = generate_random_pair_of_numbers()
            f.write(f"{x} {y}\n")



if __name__ == "__main__":
    main()
