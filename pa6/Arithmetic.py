#------------------------------------------------------------------------------
#
#  Arithmetic.py
#  Produces the same output (given the same input) as Arithmetic.cpp for 
#  CSE 101 pa6.  Run this program by doing
#
#     python3 Arithmetic.py <input file> <output file>
#
#------------------------------------------------------------------------------
import sys

# check number of command line arguments
if len(sys.argv)!=3:
   print("Usage: "+sys.argv[0]+" <input file> <output file>")
   quit()
# end if

# open files
f1 = open(sys.argv[1], 'r')
f2 = open(sys.argv[2], 'w')

# read from f1
A = int( f1.readline() ) # line 1
f1.readline()            # line 2
B = int( f1.readline() ) # line 3

# write lines to f2
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
