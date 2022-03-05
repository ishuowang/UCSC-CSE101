#------------------------------------------------------------------------------
#  RandomInput2.py
#  Creates random input file for cmps 101 pa2. To run this progam on Linux:
#
#        python3 RandomInput2.py 
#
#------------------------------------------------------------------------------

import random

# get user input and initialize local variables
filename = input("Enter name of file to create: " )
n = int( input("Enter number of vertices n (must be positive): " ) )
max = n*(n-1)//2
m = int( input("Enter number of edges m (0<=m<="+str(max)+"): " ) )
p = int( input("Enter number of shortest paths: " ) )
f = open(filename, 'w')

# create random graph input file
f.write(str(n)+'\n')
adj = dict()
edge = [];
for i in range(m):
   u = random.randint(1,n)
   v = random.randint(1,n)
   while (u,v) in adj or u==v:
      if u != v: v = random.randint(1,n)
      u = random.randint(1,n)
   adj[(u,v)] = 1
   adj[(v,u)] = 1
   if u<v: 
      edge.append( (u, v) )
   else: 
      edge.append( (v, u) );
edge.sort();
for i in range(m):
   f.write(str(edge[i][0])+' '+str(edge[i][1])+'\n')   
f.write("0 0\n")
for i in range(p):
   u = random.randint(1,n)
   v = random.randint(1,n)
   f.write(str(u)+' '+str(v)+'\n')
f.write("0 0\n")
f.close()
