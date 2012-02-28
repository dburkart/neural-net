import sys
import re

counties = []
f = open('DataSet.txt')
outfile = open('CountiesOnly.txt', 'w')

line = f.readline();
line = f.readline();

while (True):
    if (line == ''):
        break;

    m = re.findall('([\d.-]+)+', line)

    if int(m[0]) % 1000 != 0:
        outfile.write(line)

    line = f.readline()


