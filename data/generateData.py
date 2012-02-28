import sys
import re

f = open('CountiesOnly.txt')

line = f.readline()

counties = []

while (True):
    if (line == ''):
        break

    m = re.findall('([\d.-]+)+', line);
    counties.append(int(m[0]))
    line = f.readline();

print counties

f = open('2008results.txt')
outfile = open('CountiesOnly_ans.txt', 'w')

line = f.readline()

oTotal, mTotal = 0.0, 0.0
n = 0

while(True):
    if (line == ''):
        break

    m = re.findall('([a-zA-Z\s\d.-]+)+', line)
    
    for c in counties:
        if m[2].isdigit() and c == int(m[2]):
            i = counties.index(int(m[2]));
            total = float(m[4])
            obama, mccain = float(m[5]) / total, float(m[6]) / total
            counties[counties.index(c)] = str(obama) + ' ' + str(mccain) + '\n';
            oTotal, mTotal = oTotal + obama, mTotal + mccain
            n = n + 1
            #outfile.write(str(obama) + ' ' + str(mccain) + '\n')
        
    line = f.readline()

for c in counties:
    outfile.write(str(c))

oTotal, mTotal = oTotal / n, mTotal / n
print(str(oTotal) + " " + str(mTotal))
    
outfile.close()
