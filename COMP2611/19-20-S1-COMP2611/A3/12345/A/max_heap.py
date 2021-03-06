
class Data:
    def __init__(self, key, value):
        self.key = key
        self.value = value

    def __repr__(self):
        return f'Data({self.key}, {self.value})'
    

def parent(i):
    return i // 2 

def left_child(i):
    return i * 2 

def right_child(i):
    return i * 2 + 1


def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]


class MaxHeap:

    def __init__(self):
        self.n = 0
        self.arr = [None]

    def __len__(self):
        return self.n 

    def is_empty(self):
        return self.n == 0

    def __bool__(self):
        return not self.is_empty()

    def insert(self, data):
        self.arr.append(data)
        index = len(self.arr) - 1
        self.n += 1
        self._sift_up(index)

    def _should_move(self, loc1, loc2):
        return self.arr[loc1].key < self.arr[loc2].key
        

    def _sift_up(self, index):
        while index > 1 and self._should_move(parent(index), index):
            swap(self.arr, index, parent(index))
            index = parent(index)

    def remove(self):
        index = len(self.arr) - 1
        swap(self.arr, 1, index)
        ans = self.arr.pop(index)
        self._sift_down(1)
        self.n -= 1
        return ans

    def _sift_down(self, index):
        n = len(self.arr) - 1
        child1 = left_child(index)
        while child1 <= n:
            curr_child = child1
            child2 = right_child(index)
            if(child2 <= n and self._should_move(child1, child2)):
                curr_child = child2
            if (not self._should_move(index, curr_child)):
                break
            swap(self.arr, index, curr_child)
            index = curr_child
            child1 = left_child(index)


# def main():
#     filename = 'data.csv'
#     passed_header = False

#     heap = MinHeap()

#     fp = open(filename, 'r')
#     for line in fp:
#         if passed_header:
#             priority, fname, lname = line.strip().split()
#             data = Data(int(priority), fname + ' ' + lname)
#             heap.insert(data)
#             print(f'{priority}, ', end='')
#         passed_header = True
#     fp.close()
#     print()
#     #print(heap.arr)

#     while heap:
#         res = heap.remove()
#         print(res)
    
        
      
# if __name__ == '__main__':
#     main()

