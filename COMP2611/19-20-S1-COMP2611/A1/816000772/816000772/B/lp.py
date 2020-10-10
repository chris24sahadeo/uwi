class LinearProbingHashtable:
  # author: Inzamam Rahaman
  # modified by: 

  def __init__(self, n, input_file_path):
    self.table = [None] * n   
    self.n = n 

    print('Reading from {}...'.format(input_file_path))
    with open(input_file_path) as input_file:
      line = input_file.readline().strip()
      while line:
        # print(line)
        line = line.split(' ')
        key = line[0]
        if len(line) > 1:
          value = line[1]
        else:
          value = 'blacklisted'
        self.insert(key, value)
        print('{} {}'.format(key, value))
        line = input_file.readline().strip()
  
  def insert(self, key, value):
    i = hash(key) % self.n
    misses = 0
    new_i = (i + misses) % self.n 
    while self.table[new_i] is not None:
      key_p, value_p = self.table[new_i]
      if key_p == key:
        break
      misses += 1
      new_i = (i + misses) % self.n 
    self.table[new_i] = (key, value)

  def search(self, key):
    i = hash(key) % self.n
    misses = 0
    new_i = (i + misses) % self.n 
    while self.table[new_i] is not None:
      k_prime, v_prime = self.table[new_i]
      if k_prime == key:
        return v_prime 
      misses += 1
      new_i = (i + misses) % self.n
    return None

  def delete(self, key):
    i = hash(key) % self.n
    misses = 0
    new_i = (i + misses) % self.n 
    while self.table[new_i] is not None:
      k_prime, v_prime = self.table[new_i]
      if k_prime == key:
        self.table[new_i] = None 
        prev_i = new_i
        curr = misses + 1
        new_i = (i + curr) % self.n 
        while self.table[new_i] is not None:
          self.table[prev_i] = self.table[new_i]
          prev_i = new_i
          curr += 1
          new_i = (i + curr) % self.n
      misses += 1
      new_i = (i + misses) % self.n
      

    
# hashtable = LinearProbingHashtable(100)
# hashtable.insert('Inzamam', 9)
# hashtable.insert('Nicholas', 1)
# hashtable.insert('Alice', 10)
# print(hashtable.search('Inzamam'))
# hashtable.delete('Alice')
# print(hashtable.search('Alice'))
