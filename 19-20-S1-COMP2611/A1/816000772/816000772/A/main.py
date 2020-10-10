from chaining import ChainingHashtable

# get text from input file
text_file_name = 'dna.txt'
with open(text_file_name) as text_file:
  text = text_file.read().strip()
# print(text)

# get length of a given pattern from patterns.txt (assuming all patterns have the same length)
patterns_file_name = 'patterns.txt'
with open(patterns_file_name) as patterns_file:
  pattern_length = len(patterns_file.readline().strip())
# print(pattern_length)

# get all sub-strings of length 'pattern_length' and store in hashtable
hash_table_size = 1000
hash_table = ChainingHashtable(hash_table_size)
for i in range(len(text)-pattern_length+1):
  substring = text[i:i+pattern_length]
  # print(substring)
  hash_table.insert(substring, i)
hash_table.print_table_pretty()

# searching 'hash_table' for patterns in 'patterns.txt'
output_file_name = 'solutions.txt'
with open(output_file_name, 'w') as output_file, open(patterns_file_name) as patterns_file:
  for pattern in patterns_file:
    output_file.write(hash_table.search(pattern.strip()))
