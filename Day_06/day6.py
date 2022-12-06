string = open("realdata.txt", "r").read()

def get_marker(num_len):
	for i in range(0, len(string) - 3):
		stringset = string[i : i + num_len]
		if (len(set(stringset)) == len(stringset)):
			return i + num_len

print(get_marker(4), get_marker(14))