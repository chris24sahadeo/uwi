'''
Full Name: Christopher Sahadeo
Student ID: 816000772
Email: christophersahadeo@gmail.com, christopher.sahadeo1@my.uwi.edu
Course Code: COMP3605
Assignment 1
'''


import pandas as pd
import numpy as np
from math import log


# loads the dataset from a csv file into a pandas dataframe and returns the dataframe
def loadDataSet(fileName = 'data.csv'):
    try:
        print('Loading dataset from {}...'.format(fileName))
        dataSet = pd.read_csv(fileName, index_col=0)
    except IOError:
        print('Error opening {}'.format(fileName))
        exit()
    else:
        print('Dataset loaded successfully!\n\n')
        return dataSet


# calculates the probability that a given tuple belongs to a given class in the dataset
def calProbability(C_i_D, D):
    return C_i_D/D


# calculates the entropy (Info) of a given dataSet
# the function is used to calculate the entroy of the entire set, D
# as well as partitions of D returned by the partition function during the calculation of info gains for individual attributes
def calEntropy(dataSet):
    classCounts = dataSet['Class'].value_counts()           # gets the number of tupules in each class in the set
    numberOfTuples = len(dataSet.index)                     # gets the total number of tuples (rows) in the set

    infoD = 0                                               # accumulates the info for a set
    for classCount in classCounts:                          # iterating through the number of tupules in each class
        p_i = calProbability(classCount, numberOfTuples)    # calculating the probability that a given tuple belongs to a particular class
        infoD += -p_i*log(p_i, 2)                           # accumulating the info gain for the given set

    return infoD


# partitions the dataset, returning all tuples corresponding to a particular value of a particular attribute
# dataSet.columns[attIdx] gets the name of a particular attribute in the set
# dataSet[dataSet.columns[attIdx]]==v checks if the attribute is of value 'v'
# .loc returns the requires tupules
def dataPartition(dataSet, attIdx, v):
    return dataSet.loc[dataSet[dataSet.columns[attIdx]]==v]


# computes the information gain of a single attribute
def computeInfoGain(dataSet, attIdx, dataSetEntropy):
    attributeName = dataSet.columns[attIdx]                                                     # gets the name of the attribute referened to by the index attIdx
    splittingAttributeValues = dataSet[attributeName].unique()                                  # gets the names of all the possibles values of the attribute
    informationGainOnAttribute = 0                                                              # acculuates the information gain on the attribute
    for v in splittingAttributeValues:                                                          # iterates through all splitting values
        partition = dataPartition(dataSet, attIdx, v)                                           # partitions the dataset, returning all tuples corresponding to a particular value of a particular attribute
        informationGainOnAttribute += (len(partition)/len(dataSet))*calEntropy(partition)       # performing the Info Gain calculation
    gain = dataSetEntropy - informationGainOnAttribute                                          # Gain calculation
    print('Gain({})\n= Info(D) - Info_{}(D)\n= {} - {}\n= {}\n\n'.format(attributeName, attributeName, dataSetEntropy, informationGainOnAttribute, gain))



# computes the info gain for all attributes in the dataset by calling the 'computeInfoGain' funtion
def computeInfoGains(dataSet):
    dataSetEntropy = calEntropy(dataSet)
    print('Info(D) = {}\n\n'.format(dataSetEntropy))
    numberOfSplittingAttributes = len(dataSet.columns)-1            # we minus one to ignore the 'Class' column in the dataframe (Class is not an attribute)
    for attidx in range(numberOfSplittingAttributes):               # iterates through all attributes
        computeInfoGain(dataSet, attidx, dataSetEntropy)            # computes the info gain of the attribute referenced by attIdx



def main():
    dataSet = loadDataSet()
    print('DataSet\n{}\n\n'.format(dataSet))
    computeInfoGains(dataSet)


if __name__ == '__main__':
    main()
