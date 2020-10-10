from bst import BinarySearchTree

# storing log data in bst 
server_logs = BinarySearchTree()
with open('log.txt') as log_file:
  for log in log_file:
    [timestamp, ip_address] = log.strip().split()
    server_logs.insert(timestamp, ip_address)

# processing queries
with open('queries.txt') as queries, open('solution.txt', 'w') as solutions:
  for query in queries:
    parsed_query = query.strip().split()
    query_type = parsed_query[0]
    timestamp_1 = parsed_query[1]
    if query_type == 'LTE':
      query_result = server_logs.lte_query(timestamp_1)      
      solutions.write((query_result.data.value if query_result is not None else 'NONE') + '\n')
    elif query_type == 'GTE':
      query_result = server_logs.gte_query(timestamp_1)      
      solutions.write((query_result.data.value if query_result is not None else 'NONE') + '\n')
    else:
      timestamp_2 = parsed_query[2]
      ips = [ip_node.data.value if ip_node is not None else 'NONE' for ip_node in server_logs.range_query(timestamp_1, timestamp_2)]
      solutions.write(' '.join(ips) + '\n') 