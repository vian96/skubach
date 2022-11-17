import matplotlib.pyplot as plt

with open('out.txt', 'r') as f_in:
    s = f_in.read()

lines = s.split('\n')[:-1]
words = [i.split(' ') for i in lines]
x_val = [float(i[0]) for i in words]
y_val = [float(i[1]) for i in words]

fig, ax = plt.subplots(figsize = (16, 9), dpi = 80)

ax.plot(x_val, y_val, lw = 6)
ax.grid(True, alpha = 0.5)
ax.set_ylim(0.8 * min(y_val), 1.2 * max(y_val))

# plt.savefig(file_name)
plt.show()
