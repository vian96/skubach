import matplotlib.pyplot as plt

import sys

if len(sys.argv[1]) < 2:
    print('no file name')
    exit()

f_name = sys.argv[1]

print(f'opened {f_name}')

with open(f_name, 'r') as f_in:
    s = f_in.read()

lines = s.split('\n')
words = [i.split(' ') for i in lines]

# print(f'|{s}|', words)

y_vals = []
names = []
for line in words:
    names.append(line[0])
    y_vals.append([float(i) for i in line[1:-1]])

x_val = []
k = 4
for i in range(len(y_vals[0])):
    x_val.append(k)
    k = k + k//4

colors = 'bgrcmyk'

fig, ax = plt.subplots(figsize = (16, 9), dpi = 80)

# print(names)

for i in range(len(names)):
    ax.plot(x_val, y_vals[i], color = colors[i], label = names[i])

ax.grid(True, alpha = 1)
# ax.set_ylim(0.8 * min(y_val), 1.2 * max(y_val))

plt.legend(fontsize = 'x-large')

# plt.show()
plt.savefig(f_name + '.png')