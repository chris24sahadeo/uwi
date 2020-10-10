from lp import LinearProbingHashtable

hashtable_size = 100

# building the dns table (url to ip mappings)
dns_file_path = 'dns.txt'
dns = LinearProbingHashtable(hashtable_size, dns_file_path)

# building the blacklist set (url to ip mappings)
blacklist_file_path = 'blacklist.txt'
blacklist = LinearProbingHashtable(hashtable_size, blacklist_file_path)

# processing queries
queries_file_path = 'queries.txt'
output_file_name = 'solutions.txt'
print('Processing queries from {}...'.format(queries_file_path))
print('Writing output to {}...'.format(output_file_name))
with open(queries_file_path) as queries_file, open(output_file_name, 'w') as output_file:
  url = queries_file.readline().strip()
  while url:
    # print(query)
    ip = dns.search(url)
    if ip is None:
      output = 'N'
    else:
      blacklist_check = blacklist.search(ip)
      if blacklist_check is None:
        output = 'N'
      else:
        output = 'Y'
    
    output_file.write(output + '\n')      

    url = queries_file.readline().strip()

print('Done.')
