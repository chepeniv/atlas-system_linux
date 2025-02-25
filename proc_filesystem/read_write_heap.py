#!/usr/bin/python3
'''
definition and execution of a heap data overwrite program
'''


def overwrite_heap(argv):
    '''
    analyzes the heap of a given process pid currently running and overwrites
    the target string within the heap with the source string data
    '''

    # HOLBERTON CHECKER:
    #
    # case: normal replace
    # case: replace by shortest string ??
    # determine if the given pid is valid
    # if the string is not found do nothing

    if (len(argv) < 4):
        print("usage: `read_write_heap.py <pid> <search> <target>`")
        exit(1)

    target = bytes(argv[2], "ASCII")
    source = bytes(argv[3], "ASCII")
    len_target = len(target)
    len_source = len(source)

    if len_target < len_source:
        source = source[:len_target]
    if len_target > len_source:
        len_target -= len_source
        source += bytes(len_target)

    pid_dir = f"/proc/{argv[1]}/"
    mapfile = open(pid_dir + "maps")
    while (line := mapfile.readline()):
        if (line.find("[heap]") > -1):
            addr = line.split(" ")
            addr = addr[0]
            addr = addr.split("-")
            addr_low = addr[0]
            addr_high = addr[1]
            addr_low = int(addr_low, 16)
            addr_high = int(addr_high, 16)
    mapfile.close()

    memfile = open(pid_dir + "mem", "rb+")
    memfile.seek(addr_low)

    heap_data = memfile.read(addr_high - addr_low)
    pos = heap_data.find(target)
    if pos < 0:
        memfile.close()
        return 1

    memfile.seek(addr_low + pos, 0)
    memfile.write(source)
    memfile.close()


if __name__ == "__main__":
    from sys import argv
    overwrite_heap(argv)
