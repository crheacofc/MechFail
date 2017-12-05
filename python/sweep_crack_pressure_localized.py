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
    with open('input/static/crackpressure/loc.i', 'w') as file:
        file.writelines( data )

def run_program():
    #proc = Popen("mpiexec ")
    #proc.wait()
    #print("Running program")
    call('mpiexec -n 2 ./sheep-opt -i input/static/crackpressure/loc.i',shell=True)
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


gc_list = [5.e-08]
#press_list = [0.001,0.002,0.003,0.005,0.006,0.007,0.008,0.009,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.015,0.025,0.035,0.045,0.055,0.065,0.075,0.085,0.095]
press_list=[0.004]
filename = 'input/static/crackpressure/loc.i'



for j in range(0,len(press_list)):
    press = press_list[j]
    press_string1 = '    value = '+str(press)
    press_string2 = '    const = '+str(press)
    for i in range(0,len(gc_list)):
        gc = gc_list[i]
        gc_string = "    constant_expressions ='"+str(gc)+" 1 1'"
        outputstring = '  file_base = output/AlOx_CP_loc/gc'+str(gc)+'pr'+str(press)

        #line as starting from 1 -- Atom numbers
         #change_input(filename,[193,278,288,391],[gc_string,press_string2, press_string1,outputstring])
        change_input(filename,[210,307,404],[gc_string, press_string1,outputstring])
        run_program()
        #while check_program()==True:
        #    check_program()
        #else:
        #    print("Finished")

