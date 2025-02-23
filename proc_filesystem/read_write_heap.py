#!/usr/bin/python3

# GUIDELINES:
#
# find the ASCII string in the heap of the target process and replace it
# usage: `read_write_heap.py pid search_data replace_data`
#     ONLY look within the heap of the target process
# output is left at the programmer's discretion
# direct error messages to `stdout` and use an exit status of 1

# determine if the given pid is valid
#
# open the /proc/<pid>/maps file
# find the [heap] line
# from that line get the address lower and upper bounds
#
# go to and open the /proc/<pid>/mem file
# go to the lower address
# from there search for the string while within bounds
# if the string is found overwrite it with a new string
# if the string is not found do nothing
#!/usr/bin/python3

if __name__ == "__main__":
    from sys import argv

if (len(argv) < 4):
    print("{}: insuficient arguments given".format(argv[0]))
    print("usage: `read_write_heap.py pid search_data replace_data`")
    exit(1)

pid_dir = f"/proc/{argv[1]}/"
mapfile = open(pid_dir + "maps")

while (line := mapfile.readline()):
    if (line.find("[heap]") > -1):
        addr = line.split(" ")[0]
        addr = addr.split("-")
        addr_low = addr[0]
        addr_high = addr[1]
        print(f"high {addr_high}")
        print(f"low  {addr_low}")
