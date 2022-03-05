#------------------------------------------------------------------------------
#
#  RandomInput6.py
#  Creates a random pair of matched input/output files for CSE 101 pa6.  
#  Run this program by doing
#
#     python3 RandomInput6.py
#
#------------------------------------------------------------------------------
import random

def random_integer(length):
    decimal_digits  = '0123456789'
    sign = ['', '+', '-']
    integer = random.choice(sign);
    for i in range(0,length):
        integer += random.choice(decimal_digits)
    return integer
# end random_integer

# get user input and initialize local variables
filename1 = input("Enter name of input file to create: " )
filename2 = input("Enter name of output file to create: " )
a = int( input("Enter the number of decimal digits in A: " ) )
b = int( input("Enter the number of decimal digits in B: " ) )

# create random integers as strings
strA = random_integer(a) 
strB = random_integer(b) 

# open files
f1 = open(filename1, 'w')
f2 = open(filename2, 'w')

# write lines to f1
f1.write(strA+'\n\n'+strB+'\n')

# write lines to f2
A = int(strA)
B = int(strB)
f2.write(str(A)+'\n\n')
f2.write(str(B)+'\n\n')
f2.write(str(A+B)+'\n\n')
f2.write(str(A-B)+'\n\n')
f2.write(str(A-A)+'\n\n')
f2.write(str(3*A-2*B)+'\n\n')
f2.write(str(A*B)+'\n\n')
f2.write(str(A**2)+'\n\n')
f2.write(str(B**2)+'\n\n')
f2.write(str(9*A**4+16*B**5)+'\n\n')

# close files
f1.close()
f2.close()
