#------------------------------------------------------------------------------
#  RandomInput7.py
#  Creates a random input file for CSE 101 pa7. Selects a random set of n 
#  lines from file 'English.txt' (containing 194,000 English language words), 
#  then copies them to file2. 
#  
#  To run this program, do 
#
#            python3 RandomInput7.py 
#     
#------------------------------------------------------------------------------
from random import sample

# open file to randomize
file1 = open('English.txt','r')

# get file to write to
file2 = open( input('Enter name of file to create: '),'w')

# get number of lines to write to file
n = int( input('Enter the number of lines to write: ') )

# select n lines from file1 (with replacement)
R = file1.readlines()
W = sample(R, n)

# write random lines to file2
for line in W:
   file2.write(line)
   
# close files   
file1.close()
file2.close()
