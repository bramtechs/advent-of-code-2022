import utils

import itertools

# functional programming is so much easier to read and understand, trust me
# good luck if want to debug this!

lines = utils.read_input("inputs/input13_sample.txt")

compact_lines  = [x for x in lines if x != ""]

evaled_lines = map(lambda l: eval(l),compact_lines)

pairs = itertools.permutations(evaled_lines,2)

right = len(compact_lines)/2

def traverse(first, second):
    global right

    print(first,second)

    if isinstance(first,list):
        traverse(first,second)
    else:
        first = [first]
    
    if isinstance(second,list):
        traverse(first,second)
    else:
        second = [second]

    for x, y in zip(first,second):
        if x > y:
            right -= 1;

for first, second in pairs:
    for x, y in zip(first,second):
        traverse(x,y)

print(right)
