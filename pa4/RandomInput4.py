#------------------------------------------------------------------------------
#
#  RandomInput4.py
#
#  Creates random input file for cse 101 pa4.  Run this program by doing
#
#        python3 RandomInput4.py
#
#------------------------------------------------------------------------------
import random

# get user input and initialize local variables
filename = input("Enter name of file to create: " )
n = int( input("Enter matrix size (number of rows and columns): " ) )
a = int( input("Enter the number of non-zero entries in matrix A: " ) )
b = int( input("Enter the number of non-zero entries in matrix B: " ) )
min = -10000
max = +10000
f = open(filename, 'w')

# create first two lines of file
f.write(str(n)+' '+str(a)+' '+str(b)+'\n\n')

# create random matrix A and write to file
usedA = dict()
for k in range(a):
   i = random.randint(1,n)
   j = random.randint(1,n)
   while (i,j) in usedA:
      i = random.randint(1,n)
      j = random.randint(1,n)
   usedA[(i,j)] = 1
   x = round( random.uniform(min, max), 1)
   f.write(str(i)+' '+str(j)+' '+str(x)+'\n')
f.write('\n')

# create random matrix B and write to file
usedB = dict()
for k in range(b):
   i = random.randint(1,n)
   j = random.randint(1,n)
   while (i,j) in usedB:
      i = random.randint(1,n)
      j = random.randint(1,n)
   usedB[(i,j)] = 1
   x = round( random.uniform(min, max), 1)
   f.write(str(i)+' '+str(j)+' '+str(x)+'\n')
f.close()
