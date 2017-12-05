#Python file to create graphic from sweep results
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
pd.options.mode.chained_assignment = None  # default='warn'
csv_file = pd.read_csv("/home/crhea/Dropbox/Research/Kidney-Stone/sheep/output/Stoch_CP/10percentvar/branches_CP.csv")
total_gc = []
total_pressure = []
total_values = []
none_gc = []
none_pressure = []
two_gc = []
two_pressure = []
three_gc = []
three_pressure = []
four_gc = []
four_pressure = []
radial_gc = []
radial_pressure = []
bad_val_count = 0
for i in range(len(csv_file)):
    nbr = str(csv_file['Number of Branches'][i])#number of branches
    print(nbr)
    if nbr == '0':
        none_gc.append(csv_file['GC'][i])
        none_pressure.append(csv_file['Pressure'][i])
        total_gc.append(csv_file['GC'][i])
        total_pressure.append(csv_file['Pressure'][i])
        total_values.append(1.0)
        print("We found a zero")
    elif nbr == '2':
        two_gc.append(csv_file['GC'][i])
        two_pressure.append(csv_file['Pressure'][i])
        total_gc.append(csv_file['GC'][i])
        total_pressure.append(csv_file['Pressure'][i])
        total_values.append(2.0)
        print('We found a two')
    elif nbr == '3':
        three_gc.append(csv_file['GC'][i])
        three_pressure.append(csv_file['Pressure'][i])
        total_gc.append(csv_file['GC'][i])
        total_pressure.append(csv_file['Pressure'][i])
        total_values.append(3.0)
        print("We found a three")
    elif nbr == '4' or nbr == '4r':
        four_gc.append(csv_file['GC'][i])
        four_pressure.append(csv_file['Pressure'][i])
        total_gc.append(csv_file['GC'][i])
        total_pressure.append(csv_file['Pressure'][i])
        total_values.append(4.0)
    elif nbr == 'radial':
        radial_gc.append(csv_file['GC'][i])
        radial_pressure.append(csv_file['Pressure'][i])
        total_gc.append(csv_file['GC'][i])
        total_pressure.append(csv_file['Pressure'][i])
        total_values.append(5.0)
    else:
        print("Not a reasonable value")
        bad_val_count+=1
fig = plt.figure(figsize=(20,10))
ax = plt.gca()
none = ax.scatter(none_gc,none_pressure, c='red', label='None')
two = ax.scatter(two_gc,two_pressure,c='orange', label='Two')
three = ax.scatter(three_gc,three_pressure, c='blue', label='Three')
four = ax.scatter(four_gc,four_pressure, c='green', label='Four')
radial = ax.scatter(radial_gc,radial_pressure, c='purple', label='Radial')
plt.xscale('log')
plt.yscale('log')
plt.xlim(1e-9,1e-6)
plt.ylim(0.001,1.0)
plt.xlabel('Toughness')
plt.ylabel('Pressure')
print("Number of bad values is ",bad_val_count)
data = np.zeros((len(total_values),3))
for i in range(len(total_values)):
    data[i,0] = total_gc[i]
    data[i,1] = total_pressure[i]
    data[i,2] = total_values[i]
'''
gc = np.unique(total_gc)
pressure = np.unique(total_pressure)
X,Y = np.meshgrid(gc,pressure)
Z = np.array(total_values).reshape(len(pressure),len(gc))
plt.pcolormesh(X,Y,Z)
plt.xscale('log')
plt.yscale('log')

#ax = sns.heatmap(data, linewidths=.1)
'''
#ax.set_yscale('log')
#ax.set_xscale('log')
#ax.set_ylim(1e-5,1e1)
#ax.set_xlim(1e-9,1e-3)
#ax.set_xlabel('Toughness')
#ax.set_ylabel('Pressure')
#5plt.show()
plt.legend(handles=[none,two,three,four,radial],bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
           ncol=2, mode="expand", borderaxespad=0.)
plt.savefig('regimes_CP10varloc.png')
