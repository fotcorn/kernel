import unicodecsv
import sys

f = open('scancodes.csv')
reader = unicodecsv.reader(f)


d = {}

for line in reader:
    if line[0] and not ',' in line[0]:
        d[line[0]] = line[1]

x = {}
for k,v in d.items():
    x[int(k.strip(), 16)] = v

d = x
x = {}

for k,v in d.items():
    key = v.split(' ')[0]
    if len(key) == 1:
        x[k] = key

for i in range(0, 256):
    if i in x:
        sys.stdout.write("'{}', ".format(x[i]))
    else:
        sys.stdout.write('0,   ')
    if (i + 1) % 16 == 0:
        print

