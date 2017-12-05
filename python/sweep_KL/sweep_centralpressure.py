## This file will do a sweep over the parameter space for the mechanical fracture  problem

from subprocess import call#,run,Popen,PIPE
import os
import psutil
num = 1 #field number
#call('mkdir test', shell=True)
#call('cd test && mkdir extras',shell=True)
os.chdir("/home/crhea/Dropbox/Research/Kidney-Stone/sheep/")
#call('mkdir extras',shell=True)
fieldnum = 'field'+str(num) #field number

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
    with open('input/Stochastic/pressurecentral/fixedBoundary/'+fieldnum+'.i', 'w') as file:
        file.writelines( data )

def run_program():
    #proc = Popen("mpiexec ")
    #proc.wait()
    #print("Running program")
    call('mpiexec -n 1 ./sheep-opt -i input/Stochastic/pressurecentral/fixedBoundary/'+fieldnum+'.i',shell=True)
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
#gc_list = [1.e-9,5.e-9,1.e-8,5.e-8,1.e-7,5.e-7,1.e-6,5.e-6]
#press_list = [0.001,0.005,0.01,0.05,0.1,0.5]
#press_list = [0.0001,0.0005,0.001,0.005,0.01,0.05,0.1,0.5,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09]
#----------Values needed to get better resolution for each GC level--------------#
#gc_list = [1.e-9]
#press_list = [0.0007,0.0008,0.009,0.02,0.03,0.04,0.05,0.06,0.07]
#press_list = [0.0082,0.0084,0.0086,0.0088]
#gc_list = [1.e-8]
#press_list = [0.003,0.005,0.007,0.009,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09]
#gc_list = [1.e-7]
#press_list = [0.007,0.009,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09]
#press_list = [0.0072,0.0074,0.0076,0.0078,0.008,0.0082,0.0084,0.0086,0.0088]
#press_list = [0.031,0.032,0.033,0.034,0.035,0.036,0.037,0.038,0.039]
gc_list = [1.e-6]
#press_list = [0.007,0.009,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09]
#press_list = [0.022,0.024,0.026,0.028]
press_list = [0.2,0.3,0.4,0.15,0.25,0.35,0.45]

#--------------------------------------------------------------------------------#
filename = 'input/Stochastic/pressurecentral/fixedBoundary/'+fieldnum+'.i'



for j in range(0,len(press_list)):
    press = press_list[j]
    press_string1 = '    value = '+str(press)
    press_string2 = '    const = '+str(press)
    for i in range(0,len(gc_list)):
        gc = gc_list[i]
        gc_string = "    constant_expressions ='"+str(gc)+" 1 1'"
        outputstring = '  file_base = output/Stoch_CP/fixedBoundary/Regime1/'+str(fieldnum)+'/gc'+str(gc)+'pr'+str(press)

        #line as starting from 1 -- Atom numbers
         #change_input(filename,[193,278,288,391],[gc_string,press_string2, press_string1,outputstring])
        change_input(filename,[222,307,398],[gc_string, press_string1,outputstring])
        run_program()
        #while check_program()==True:
        #    check_program()
        #else:
        #    print("Finished")
