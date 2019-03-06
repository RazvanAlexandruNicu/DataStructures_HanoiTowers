This program implementes Hanoi Towers problem using Data Structures.
In this implementation I used Generic Data Structures such as Generic Stacks to
simulate the rod, Generic Queues to store the further moves to solve the
problem described,  and different struct types to simulate the disks and
the Hanoi Systems. A Hanoi System is a particular Hanoi Towers problem
described by 3 rods and a color. There can exist more Hanoi Systems at
the same time in the execution of the programs, the difference between them
beeing the color of the disks used in the system.
The program takes 2 params:
	- the input file name
	- the output file name
The program supports the following commands:
	- add [disk_color] [disk_dimension]
	- play [system_color] [nr_moves]
	- show [system_color]
	- show_moves [system_color] [nr_moves]
