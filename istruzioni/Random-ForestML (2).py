import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import find_peaks as fp

N_FILE=417
FOLDER='D:\\Ulde\\'



#Aprire i file in maniera ricorrente

for index in range(0,N_FILE+1):
    if index not in [21,24,54,64,65,76,104,111,116,119,145,146,171]:
        print(index)
        df=None
        df=pd.read_csv(FOLDER+'Test#'+str(index)+'.txt',sep='\t',header=None)
        
        plt.title('Test#'+str(index)+'.txt')
        plt.plot(df[df.columns[-1]])
        plt.show()
        
        #get interesting columns for each file
        
        
        #Find interesting columns for each file
        
        #do plot
        
        #Find the peaks!!!!!
        
        #write in DB 
        #
        #
        #
        #
