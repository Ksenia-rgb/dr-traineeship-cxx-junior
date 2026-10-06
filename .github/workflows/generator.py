if __name__ == "__main__":
  head = 100040005
  tail = 10003
  with open("long.txt", "wb") as data:
    data.write(b"a" * head)
    data.write(b" " * tail)
