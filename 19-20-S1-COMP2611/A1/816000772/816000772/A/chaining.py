import pprint

class ChainingHashtable:
  '''
    Author: Inzamam Rahaman
    Modified by 
  '''

  def __init__(self, n):
    # create blank list with n elements
    self.table = [None] * n  
    self.n = n
  
  def insert(self, key, value):
    i = hash(key) % self.n

    # if bucket is empty
    if self.table[i] is None:
      self.table[i] = [(key, [value])]

    # if bucket is used
    else:
      for j, (key_prime, value_list) in enumerate(self.table[i]):
        # if key is found previously then append value to the list
        if key == key_prime:
          self.table[i][j][1].append(value) 
          return
      # if key was not found
      self.table[i].append((key, [value]))

  def search(self, key):
    i = hash(key) % self.n
    if self.table[i] is None:
      return 'NONE'
    for (key_prime, value_list) in self.table[i]:
      if key == key_prime:
        return ' '.join(str(value) for value in value_list) + '\n'
    return 'NONE' 

  def delete(self, key):
    i = hash(key) % self.n
    if self.table[i] is not None:
      for j, (k_prime, v_prime) in enumerate(self.table[i]):
        if key == k_prime:
          # Python remove element from index j 
          # moves all other elements up accordingly
          self.table[i].pop(j)
  
  def print_table(self):
    for i, row in enumerate(self.table):
      print('{} {}'.format(i, row))
  
  def print_table_pretty(self):
    pp = pprint.PrettyPrinter(indent=4)
    pp.pprint([{index: value} for index, value in enumerate(self.table)])


# hashtable = ChainingHashtable(100)
# hashtable.insert('Inzamam', 9)
# hashtable.insert('Nicholas', 1)
# hashtable.insert('Alice', 10)
# print(hashtable.search('Inzamam'))
# hashtable.delete('Alice')
# print(hashtable.search('Alice'))
# hashtable.insert('Nicholas', 2)
# print(hashtable.search('Nicholas'))
