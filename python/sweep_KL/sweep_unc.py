## This file will do a sweep over the parameter space for the mechanical fracture  problem

from subprocess import call#,run,Popen,PIPE
import os
import psutil
num = 4 #field number
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
    with open('input/Stochastic/crackpressure/freeBoundary/'+fieldnum+'.i', 'w') as file:
        file.writelines( data )

def run_program():
    #proc = Popen("mpiexec ")
    #proc.wait()
    #print("Running program")
    call('mpiexec -n 2 ./sheep-opt -i input/Stochastic/crackpressure/freeBoundary/'+fieldnum+'.i',shell=True)
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
#gc_list = [1.e-8,1.e-7,1.e-6]
#press_list = [0.0001,0.0005,0.001,0.005,0.01,0.05,0.1,0.5,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09]
#press_list = [0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09]
#----------Values needed to get better resolution for each GC level--------------#
#gc_list = [1.e-7]
#press_list = [0.006,0.007,0.008,0.009,0.015,0.02,0.025,0.03,0.035,0.04,0.045]
#press_list = [0.011,0.0115,0.012,0.0125,0.013,0.0135,0.014,0.0145]
gc_list = [1.e-8]
press_list = [0.005]
#press_list = [0.0015,0.002,0.0025,0.003,0.0035,0.004,0.0045,0.0055,0.006,0.0065,0.007,0.0075,0.008,0.0085,0.009,0.0095]
#press_list = [0.0046,0.0047,0.0048,0.0049,0.0051,0.0052,0.0053,0.0054]
#press_list = [0.00491,0.00492,0.00493,0.00495,0.00496,0.00497,0.00498,0.00499]
#gc_list = [1.e-9]
#press_list = [0.0006,0.0007,0.0008,0.0009,0.0015,0.002,0.0025,0.003,0.0035,0.004,0.0045]
#----------Test values to induce different crack patterns -----------#
#gc_list = [1.e-5,1.e-4,1.e-3,1.e-2]
#press_list = [0.06]
#-------Values for Localized --------------------#
#gc_list = [5.e-08]
#press_list = [0.001,0.002,0.003,0.004,0.005,0.006,0.007,0.008,0.009,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.015,0.025,0.035,0.045,0.055,0.065,0.075,0.085,0.095]
#------------------------------------------------#
filename = 'input/Stochastic/crackpressure/freeBoundary/'+fieldnum+'.i'



for j in range(0,len(press_list)):
    press = press_list[j]
    press_string1 = '    value = '+str(press)
    press_string2 = '    const = '+str(press)
    for i in range(0,len(gc_list)):
        gc = gc_list[i]
        gc_string = "    constant_expressions ='"+str(gc)+" 1 1'"
        outputstring = '  file_base = output/Stoch_CP/freeBoundary/'+str(fieldnum)+'/gc'+str(gc)+'pr'+str(press)

        #line as starting from 1 -- Atom numbers
         #change_input(filename,[193,278,288,391],[gc_string,press_string2, press_string1,outputstring])
        change_input(filename,[223,320,419],[gc_string, press_string1,outputstring])
        run_program()
        #while check_program()==True:
        #    check_program()
        #else:
        #    print("Finished")