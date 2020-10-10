'''

==========================================
Multilayer Perception with 1 hiddent layer
------------------------------------------
trained with backpropagation
(vectorized batch gradient descent)
==========================================


dr kieu's backpropagation notes: https://drive.google.com/file/d/16erGrxD0JBa4YXfwU-1F6Kfv2O3KxTq_/view
code tags: https://www.python.org/dev/peps/pep-0350/#mnemonics
scikit learn implementaion: https://scikit-learn.org/stable/modules/neural_networks_supervised.html

'''


import numpy as np
import matplotlib.pyplot as plt
# import math
import sys


print(__doc__)


class MLPClassifier:

    # class variables
    DEFAULT_LEARNING_RATE = 0.1
    DEFAULT_SSE_THRESHOLD = 0.001
    DEFAULT_BIAS_CORRECTION = -1
    RAND_LOWER_BOUND = -2.4
    RAND_UPPER_BOUND = 2.4
    NUM_HIDDEN_LAYER_NEURONS = 2


    def __init__(self, a = None, SSE_threshold = None):
        # constructor

        # init learning rate (defaults loaded if no parameters passed)
        if a is None:                           # if no alpha (learning rate) is specified
            self.a = self.DEFAULT_LEARNING_RATE     # then set to default learning rate
        else:                                   # else
            self.a = a                              # set to user defined alpha

        # init sse threshold (defaults loaded if no parameters passed)
        if SSE_threshold is None:
            self.SSE_threshold = self.DEFAULT_SSE_THRESHOLD
        else:
            self.SSE_threshold = SSE_threshold

    
    def generate_header(self, X):
        # generates results table header

        x = '\t'.join('x'+str(i) for i in range(1, np.size(X,1)+1))
        middle = '\tYd\t\tY\t\t\te'
        # w = '\t'.join('w'+str(i) for i in range(1, np.size(X,1)))
        return x + middle # omit weights

    
    def plot(self, x, y):
        plt.xscale('log')
        plt.plot(x, y)
        plt.xlabel('Generations')
        plt.ylabel('SSE')
        plt.title('Fitness vs Generations')
        plt.show()


    def print_epoch(self, x, yd, y, e):
        # prints the results of a single epoch   

        for (x_, yd_, y_, e_) in zip(x, yd, y, e):
            print('{}\t{}\t{}\t{}\t{}'.format(x_[0], x_[1], yd_[0], y_[0], e_[0]))


    def logistic(self, X, derivative=False):
        # non linear sigmoid function

        if derivative:
            return X*(1-X)
        else:
            return 1/(1+np.exp(-X))
    

    def initialize(self, X, y, W_h = None, W_o = None, t_h = None, t_o = None):
        '''init weights and biases'''

        # check dimensions of X and y
        # X_num_rows = X.shape[0]
        # X_num_cols = X.shape[1]
        # y_num_rows = y.shape[0]
        try:
            y_num_cols = y.shape[1]
        except IndexError:
            y_num_cols = 1

        # function can accept the following optional arguements:
        #     W_h: weights for hidden layer
        #     W_o: wights for output layer
        #     t_h: biases for the hidden layer
        #     t_o: biases for the output layer 

        # if any one of these arguements are not passed then the function will randomly generate weights and biases
        F_i = 1 # number of inputs of neuron i, default to 1
        if W_h is None or W_o is None or t_h is None or t_o is None:
            self.W_h = np.random.uniform(low=self.RAND_LOWER_BOUND/F_i, high=self.RAND_UPPER_BOUND/F_i, size = (X.shape[1], self.NUM_HIDDEN_LAYER_NEURONS))
            self.W_o = np.random.uniform(low=self.RAND_LOWER_BOUND/F_i, high=self.RAND_UPPER_BOUND/F_i, size = (self.NUM_HIDDEN_LAYER_NEURONS, y_num_cols))
            self.t_h = np.random.uniform(low=self.RAND_LOWER_BOUND/F_i, high=self.RAND_UPPER_BOUND/F_i, size = (self.NUM_HIDDEN_LAYER_NEURONS))
            self.t_o = np.random.uniform(low=self.RAND_LOWER_BOUND/F_i, high=self.RAND_UPPER_BOUND/F_i, size = (y_num_cols))
        else:
            self.W_h = W_h # (2,2)
            self.W_o = np.transpose([W_o]) # (2,1)
            # self.t_h = np.transpose([t_h]) # (2,1)
            self.t_h = t_h # (1,2)
            self.t_o = t_o # (1)
        
        self.X = X
        self.y = y


    def activate(self):
        # activation step

        # hidden layer output
        self.O_h = self.logistic(np.dot(self.X, self.W_h) - self.t_h) # (4,2)

        # output layer output
        self.O_o = self.logistic(np.dot(self.O_h, self.W_o) - self.t_o) # (4,1)
        # self.O_o = np.transpose([self.O_o]) # transpose to maintain dimensionality

    
    def weight_training(self):
        # learning step
        
        '''Output layer'''
        # output error: desired - actual
        self.O_e = self.y - self.O_o # (4,1)
        self.SSE = np.sum(self.O_e**2) # (1)

        # ouput layer error gradient
        del_O_e = self.O_e*self.logistic(self.O_o, derivative=True) # (4,1)

        # output layer weight corrections
        delta_W_o = self.a*np.dot(np.transpose(self.O_h),del_O_e) # (2,1)

        # update output layer weights
        self.W_o += delta_W_o

        # update output layer bias
        delta_t_o = self.a*self.DEFAULT_BIAS_CORRECTION*np.sum(del_O_e)
        self.t_o += delta_t_o
        
        '''Hidden Layer'''
        # hidden error gradient
        del_H_e = self.logistic(self.O_h, derivative=True)*np.dot(del_O_e,np.transpose(self.W_o))

        # hidden weight corrections
        delta_W_h = self.a*np.dot(np.transpose(self.X),del_H_e)

        # update hidden layer weights
        self.W_h += delta_W_h

        # update hidden layer baises
        delta_t_h = self.a*self.DEFAULT_BIAS_CORRECTION*np.sum(del_H_e, axis=0)
        self.t_h += delta_t_h 
    

    def epoch(self):
        '''training for a single epoch'''     

        self.activate()
        self.weight_training()

    
    def fit(self, X, y, W_h = None, W_o = None, t_h = None, t_o = None): 
        '''training until sum of squared errors < threshold'''
       
        self.initialize(X, y, W_h, W_o, t_h, t_o)
        
        print('Training...')
        epoch = 1
        graph_epoch = []
        graph_SSE = []
        self.SSE = 1
        while self.SSE >= self.SSE_threshold:
            self.epoch()
            if epoch%10000 == 0:
                print('Epoch {}, SSE: {}'.format(epoch, self.SSE))
            graph_epoch.append(epoch)
            graph_SSE.append(self.SSE)            
            epoch += 1

            # print(self.generate_header(self.X))
            # self.print_epoch(self.X, self.y, self.O_o, self.O_e)
            # print()

        
        print('\n\nFINAL RESULTS AFTER {} EPOCHS: '.format(epoch-1))
        print(self.generate_header(self.X))
        self.print_epoch(self.X, self.y, self.O_o, self.O_e)
        print('SSE: {}'.format(self.SSE))

        self.plot(graph_epoch, graph_SSE)


    def predict(self, X):
        # prediction based on the trained model

        # hidden layer output
        O_h = self.logistic(np.dot(X, self.W_h) - self.t_h) # (4,2)

        # output layer output
        O_o = self.logistic(np.dot(O_h, self.W_o) - self.t_o) # (4,1)

        return np.around(O_o)
    

    def score(self):
        pass
