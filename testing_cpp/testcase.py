import sys
import random

sys.stdout = open("testcase.txt", "w")


class RandomGenerator():
  def __init__(self):
    pass

  def integer(self, lower_bound, upper_bound):
    ret = random.randint(lower_bound, upper_bound)
    return ret
  
  def double(self, lower_bound, upper_bound):
    ret = random.uniform(lower_bound, upper_bound)
    return ret

  def array_int(self, array_size, lower_bound, upper_bound):
    l = [0]*array_size
    for index, element in enumerate(l):
      l[index] = self.integer(lower_bound, upper_bound)
    return l
  
  def array_double(self, array_size, lower_bound, upper_bound):
    l = [0]*array_size
    for index, element in enumerate(l):
      l[index] = self.double(lower_bound, upper_bound)
    return l
  

class ListOperation():
  def __init__(self):
    pass

  def print_array_space(self, l):
    for element in l:
      print(element, end=" ")
    print()

  def print_array_csv(self, l):
    for element in l:
      print(element, end=", ")
    print()


if __name__ == "__main__":
  rand = RandomGenerator()
  lops = ListOperation()
  t = rand.integer(1, 1000000)
  print(t)
  for __ in range(t):
    print(rand.integer(1, 1000), end=' ')