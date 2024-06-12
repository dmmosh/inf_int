
from math import *

def sum(base, num_bits):
    out = 0

    print('BASE', base, sep='\t')
    print('BIT', 'VAL', 'SUM', sep='\t')
    for i in range(0,num_bits-1):
        out += pow(base, i)        
        print(i, int(pow(base,i)), int(out), sep='\t')
    print(int(out), '\n')


sum(2,8)
sum(3,8)
sum(4,8)
sum(5,8)
sum(6,8)

