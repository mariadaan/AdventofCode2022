with open('testdata.txt', 'r') as f:
	trees = [list(map(int, line)) for line in f.read().splitlines()]

rows = len(trees)
columns = len(trees[0])

copy_trees = trees.copy()
for y, row in enumerate(copy_trees):
	copy_trees[y] = list(row)
	for x, tree in enumerate(row):
		if x == 0 or x == columns -1:
			copy_trees[y][x] = 1
		elif y == 0 or y == rows -1:
			copy_trees[y][x] = 1
		else:
			copy_trees[y][x] = 0

for row in trees:
	print(row)
print()

# pov left
for y in range(1, rows -1):
	tallest = trees[y][0]
	for x in range(1, columns - 1):
		if (trees[y][x] > tallest):
			copy_trees[y][x] = 1
			tallest = trees[y][x]

#pov right
for y in range(1, rows -1):
	tallest = trees[y][columns - 1]
	for x in range(columns - 2, 0, -1):
		if (trees[y][x] > tallest):
			copy_trees[y][x] = 1
			tallest = trees[y][x]

# pov up
for x in range(1, columns -1):
	tallest = trees[0][x]
	for y in range(1, rows - 1):
		if (trees[y][x] > tallest):
			copy_trees[y][x] = 1
			tallest = trees[y][x]

# pov down
for x in range(1, columns -1):
	tallest = trees[rows - 1][x]
	for y in range(rows - 2, 0, -1):
		if (trees[y][x] > tallest):
			copy_trees[y][x] = 1
			tallest = trees[y][x]


visible = 0
for row in copy_trees:
	visible += sum(row)

print(f"visible: {visible}\n")

# part 2
scenic_scores_left = trees.copy()
for y, row in enumerate(scenic_scores_left):
	scenic_scores_left[y] = list(row)
	for x, tree in enumerate(row):
		scenic_scores_left[y][x] = 0

for y, row in enumerate(scenic_scores_left):
	for x, tree in enumerate(row):
		tallest = trees[y][x]
		# print("\nme:               ", tallest)

		# looking left
		for x_left in range(x, -1, -1):
			# print("tallest:          ", tallest)
			# print("trees[y][x_left]: ", trees[y][x_left])

			if trees[y][x_left] < tallest:
				scenic_scores_left[y][x] += 1
				tallest = trees[y][x_left]
for row in scenic_scores_left:
	print(row)
