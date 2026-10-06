from random import randint
import sys

def write_random_long_str(file_name: str):
  steps = randint(10, 100)
  letter = b"a"
  space = b" "
  with open(file_name, "wb") as data:
    for i in range(steps):
      letters = randint(steps, 1000)
      spaces = randint(steps, 1000)
      data.write(letter * letters)
      data.write(space * spaces)

if __name__ == "__main__":
  write_random_long_str(sys.argv[1])
