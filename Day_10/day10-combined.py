""" https://adventofcode.com/2022/day/10 """

# parse data
all_signals = []
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
		all_signals.append(entry)

# initialize variables
x = 1
cycle = 1
important_cycles = [20, 60, 100, 140, 180, 220]
interesting_signals = []
sprite_center = 1
pixel = 0

print("\nanswer part 2:", end='')
for signal in all_signals:
	# save all interesting signals (part 1)
	cycle += signal["duration"]
	x += signal["x_change"]
	if cycle in important_cycles or cycle + 1 in important_cycles:
		interesting_signals = [signal for signal in interesting_signals if cycle - 1 not in signal]
		interesting_signals.append((cycle, x))

	# draw CRT (part 2)
	if (pixel % 40 == 0):
		print()
	sprite = sprite_center - 1, sprite_center, sprite_center + 1
	to_print = '#' if pixel % 40 in sprite else '.'
	print(to_print, end='')
	if (signal["instruction"] == "addx"):
		sub_pixel = pixel + 1
		if (sub_pixel % 40 == 0):
			print()
		to_print = '#' if sub_pixel % 40 in sprite else '.'
		print(to_print, end='')
	pixel += signal["duration"]
	sprite_center += signal["x_change"]

print()

# calculate signal strength (part 1)
signal_strength_sum = 0
for signal in interesting_signals:
	cycle, x = signal[0], signal[1]
	x = signal[1]
	if (cycle % 2 != 0):
		cycle += 1
	signal_strength_sum += cycle * x

print("\nanswer part 1: ", signal_strength_sum)
