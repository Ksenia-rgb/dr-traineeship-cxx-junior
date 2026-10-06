from random import randint
import sys

def write_random_long_str(file_name: str):
  steps = randint(90, 100)
  letter = b"a"
  space = b" "
  with open(file_name, "wb") as data:
    for i in range(steps):
      letters = randint(900, 1000)
      spaces = randint(900, 1000)
      data.write(letter * letters)
      data.write(space * spaces)
    data.write(space * 1000)

if __name__ == "__main__":
  write_random_long_str(sys.argv[1])
