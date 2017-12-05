## This file will do a sweep over the parameter space for the mechanical fracture  problem

from subprocess import call,run,Popen,PIPE
import os
import psutil

#call('mkdir test', shell=True)
#call('cd test && mkdir extras',shell=True)
os.chdir("/home/crhea/Dropbox/Research/Kidney-Stone/sheep/")
#call('mkdir extras',shell=True)


#this function will handle the changing of parameters and names
def change_input(filename,lines,new):
    with open(filename, 'r') as file:
        # read a list of lines into data
        data = file.readlines()

    # now change the desired line, note that you have to add a newline
    num_count = 0
    for val in lines:
        data[val-1] = new[num_count]+'\n'
        num_count += 1
    # and write everything back
    with open('input/static/crackpressure/test.i', 'w') as file:
        file.writelines( data )

def run_program():
    #proc = Popen("mpiexec ")
    #proc.wait()
    #print("Running program")
    call('mpiexec -n 2 ./sheep-opt -i input/static/crackpressure/test.i',shell=True)
    #Popen(['mpiexec -n 2 ./sheep-opt -i input/static/staticpressure/test.i'],shell=True)
    #os.system('mpiexec -n 2 ./sheep-opt -i input/static/staticpressure/test.i')
def check_program():
    if "sheep-opt" in (p.name() for p in psutil.process_iter()):
        print("YES")
        return True
    else:
        print("Program Not Found")
        return False

#Run through various different values for the toughness and pressure

#gc_list = [1.e-9,2.5e-9,5.e-9,7.5e-9,1.e-8,2.5e-8,5.e-8,7.5e-8,1.e-7,2.5e-7,5.e-7,7.5e-7,1.e-6,2.5e-6,5.e-6,7.5e-6]
gc_list = [7.5e-7]
press_list = [0.0001,0.0005,0.001,0.005,0.01,0.05,0.1,0.5]
#press_list = [0.0025,0.0075,0.025,0.075]
#gc_list=[0.000001]
#press_list=[0.001]
filename = 'input/static/crackpressure/test.i'



for j in range(0,len(press_list)):
    press = press_list[j]
    press_string1 = '    value = '+str(press)
    press_string2 = '    const = '+str(press)
    for i in range(0,len(gc_list)):
        gc = gc_list[i]
        gc_string = "    constant_expressions ='"+str(gc)+" 1 1'"
        outputstring = '  file_base = output/AlOx_CP/gc'+str(gc)+'pr'+str(press)

        #line as starting from 1 -- Atom numbers
         #change_input(filename,[193,278,288,391],[gc_string,press_string2, press_string1,outputstring])
        change_input(filename,[210,307,404],[gc_string, press_string1,outputstring])
        run_program()
        #while check_program()==True:
        #    check_program()
        #else:
        #    print("Finished")

