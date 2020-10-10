from max_heap import MaxHeap, Data

priority_queue = MaxHeap()
num_patients = 0
total_wait_time = 0

with open('data.txt') as events:
  for event in events:
    event_all_info = event.strip().split()
    event_type = event_all_info[0]
    if event_type == 'P':
      num_patients += 1
      arrival_time = event_all_info[1]
      priority_score = event_all_info[2]
      priority_queue.insert(Data(priority_score, arrival_time))
    else:
      attending_time = event_all_info[1]
      total_wait_time += float(attending_time) - float(priority_queue.remove().value)

average_wait_time = total_wait_time/num_patients

with open('solution.txt', 'w') as solution:
  solution.write(str(average_wait_time))


