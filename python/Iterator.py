import  sys



class my_Iterator:
    def __init__(self, start, end):
        self.current_value = start
        self.end = end

    def __iter__(self):
        return self
    def __next__(self):
        if self.current_value >= self.end:
            raise StopIteration
        val = self.current_value
        self.current_value += 1
        return val



for i in my_Iterator(1, 5):
    print(i)

gt_1 = (i for i in range(1, 1000))
print(type(gt_1))
list1 = [1,2,3,4,5,6,1,1,3,4,5]
print(sys.getsizeof(list1))

print(sys.getsizeof(gt_1))