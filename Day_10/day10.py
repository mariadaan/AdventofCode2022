instructions = []

# parse data
with open("realdata.txt", "r") as file:
	for line in file:
		parts = line.strip().split(" ")
		instruction = parts[0]
		if instruction == 'addx':
			x_change = int(parts[1])
			duration = 2
		else:
			x_change = 0
			duration = 1
		entry = {"instruction": instruction, "x_change": x_change, "duration": duration}
		instructions.append(entry)

# initialize variables
x = 1
cycle = 1
important_cycles = [20, 60, 100, 140, 180, 220]
interesting_signals = []

# save all interesting signals
for operation in instructions:
	cycle += operation["duration"]
	x += operation["x_change"]
	if cycle in important_cycles or cycle + 1 in important_cycles:
		interesting_signals = [signal for signal in interesting_signals if cycle - 1 not in signal]
		interesting_signals.append((cycle, x))

# calculate signal strength
signal_strength_sum = 0
for signal in interesting_signals:
	cycle, x = signal[0], signal[1]
	x = signal[1]
	if (cycle % 2 != 0):
		cycle += 1
	signal_strength_sum += cycle * x

print("answer part 1: ", signal_strength_sum)

x = 1
pixel = 0
# loop through all pixels
for operation in instructions:
	if (pixel % 40 == 0):
		print()
	# define position of sprite
	sprite = x - 1, x, x + 1
	to_print = '#' if pixel % 40 in sprite else '.'
	print(to_print, end='')
	if (operation["instruction"] == "addx"):
		sub_pixel = pixel + 1
		if (sub_pixel % 40 == 0):
			print()
		to_print = '#' if sub_pixel % 40 in sprite else '.'
		print(to_print, end='')

	# update values
	pixel += operation["duration"]
	x += operation["x_change"]
