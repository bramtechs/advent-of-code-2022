def read_input(name) -> str:
    # why would you even need more lines for reading a file
    return map(lambda l: l.strip(),open(name,"r").read().split("\n"))



