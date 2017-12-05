'''
 This program is for converting exodus file information to textfiles containing the connectivity array and point information
'''


import netCDF4
import numpy as np

exodus_file = '/home/crhea/Dropbox/Research/Kidney-Stone/sheep/mesh/MechFrac.e'
element_type = 'T3' #'Q4' or 'T3'
nc = netCDF4.Dataset(exodus_file)
x = nc.variables['coord'][0]
y = nc.variables['coord'][1]
#z = nc.variables['coord'][2]
#print(nc.variables)
connect = nc.variables['connect1']

#connect2 = nc.variables['connect2']
#connect = np.zeros((len(connect1)+len(connect2),3))
#for i in range(len(connect1)):
#    connect[i] = connect1[i]
#for i in range(len(connect2)):
#    connect[len(connect1)+i] = connect2[i]
##output files

nodes_outputfile_name = '/home/crhea/Dropbox/Research/Kidney-Stone/sheep/mesh/MechFrac_nodes.txt'
connect_outputfile_name = '/home/crhea/Dropbox/Research/Kidney-Stone/sheep/mesh/MechFrac_connectivity.txt'
nodes_out = open(nodes_outputfile_name,'w') #file printout nodes
connect_out = open(connect_outputfile_name,'w') #file printout connectivity

num_nodes = len(x)
conn_num = len(connect)
print("There are " + str(num_nodes)+ " nodes in the mesh")
print("There are " + str(conn_num) + " connectivity elements in the mesh")
#nodes_out.write("X" + " " + "Y" + '\n')
for i in range(num_nodes):
    nodes_out.write(str(x[i]) + " " + str(y[i])+'\n')
if element_type == 'Q4':
    for j in range(conn_num):
        connect_out.write(str(connect[j][0])+" "+str(connect[j][1])+" "+str(connect[j][2])+'\n')
elif element_type == 'T3':
    for j in range(conn_num):
        connect_out.write(str(connect[j][0])+" "+str(connect[j][1])+" "+str(connect[j][2])+'\n')
