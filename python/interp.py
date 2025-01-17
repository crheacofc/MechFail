from scipy.interpolate import griddata
import numpy as np
import math



def compare(x1, y1, x2, y2):
    x_diff = pow(x2 - x1, 2.0)
    y_diff = pow(y2 - y1, 2.0)
    dist = x_diff + y_diff
    true_dist = np.sqrt(dist)
    if (true_dist < 0.0001):
        return True

    else:
        return False



def PFInterpolation(input_path_mesh, input_path_pf, output_path_pf, nnodes, nnodes_old):
    Nodes = np.zeros((nnodes, 2))
    file1 = open(input_path_mesh + ".txt", "r")
    count = 0
    lines = file1.read().split('\n')
    for line in lines:
        line = line.split(' ')
        if count < nnodes:
            for j in range(0, 2):
                    Nodes[count, j] = float(line[j])
            count += 1
    file1.close()
    print("Read in mesh")

    OldPF = np.zeros((nnodes_old, 3))
    file2 = open(input_path_pf + ".txt", "r")
    count = 0
    lines = file2.read().split('\n')
    for line in lines:
        line = line.split(' ')
        if count < nnodes_old:
            for j in range(0, 3):
                OldPF[count, j] = float(line[j])
            count += 1
    print("Read in packing fraction information")
    file2.close()

    print("Begging interpolation")
    # Old_x,Old_y = np.meshgrid(OldNodes[:,0],OldNodes[:,1])

    PF_new = griddata((OldPF[:, 0], OldPF[:, 1]), OldPF[:, 2], (Nodes[:, 0], Nodes[:, 1]), method="cubic", fill_value=0.303)




    # plt.contourf(OldNodes[:, 0], OldNodes[:, 1],PF_new)

    FinalPF = PF_new
    for i in range(len(FinalPF)):
        print(str(FinalPF[i])+" "+str(i))
    # write out to new packing fraction file
    output = open(output_path_pf+".txt",'w')
    for i in range(nnodes):
        output.write(str(Nodes[i,0])+ " " + str(Nodes[i,1]) + " " + str(FinalPF[i])+"\n")
    output.close()

def main():
    input_path_mesh = "/home/crhea/Dropbox/Research/Kidney-Stone/sheep/mesh/MechFrac_nodes"
    input_path_pf = "/home/crhea/Dropbox/Research/Kidney-Stone/sheep/mesh/MechFrac_E_KLmesh"
    output_path_pf =  "/home/crhea/Dropbox/Research/Kidney-Stone/sheep/mesh/MechFrac_E"
    nnodes = 280795 #new nodes
    nnodes_old = 719 #old nodes
    PFInterpolation(input_path_mesh, input_path_pf, output_path_pf, nnodes, nnodes_old)

    return 0


main()
