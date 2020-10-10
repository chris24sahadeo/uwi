# need to fix the random parameter generation 
# keep the bias (theta) negative
# PYTHON MULTIPLICATION GIVING WRONG round to 1 dp

import numpy as np
import sys


class Perceptron:

    def __init__(self, theta = -0.2, alpha = 0.1, error_threshold = 0, lower_bound = -0.5, upper_bound = 0.5):
        self.theta = theta
        self.alpha = alpha
        self.error_threshold = error_threshold
        self.lower_bound = lower_bound
        self.upper_bound = upper_bound

 
    def predict_1(self, x):
        # step activation function
        return 1 if np.dot(x, self.w) >= 0 else 0

    
    def dot(self, x, y):
        sum = 0
        for x_, y_ in zip(x, y):
            sum += x_*y_
        return np.around(sum, decimals=1)

    
    def predict_2(self, x):
        return 1 if self.dot(x, self.w) >= 0 else 0
    

    def generate_header(self, X):
        x = '\t'.join('x'+str(i) for i in range(1, np.size(X,1)))
        middle = '\tYd\tY\te\t'
        w = '\t'.join('w'+str(i) for i in range(1, np.size(X,1)))
        return x+middle+w

    
    def generate_row(self, x, yd, y, e, w):
        x = '\t'.join(str(xr) for xr in x[1:])
        middle = '\t'+str(yd)+'\t'+str(y)+'\t'+str(e)+'\t'
        w = '\t'.join(str(wr) for wr in w[1:])
        return x + middle + w

        
    def fit(self, X, y):
        # setting up weights array w[], one extra column for the theta term
        # w = np.concatenate(([self.theta], np.random.uniform(self.lower_bound, self.upper_bound, np.size(X, 1))), 0)
        self.w = np.array([self.theta, 0.3, -0.1])

        # appending extra column (column 0) to left X and setting value to 1 (for bias)
        X = np.concatenate((np.ones((len(X), 1)), X), 1) 

        largest_e = sys.float_info.min # error term, set to INF initially
        epoch = 1 # generation number
        print(self.generate_header(X))
        while abs(largest_e) > self.error_threshold: # repeat until error is zero
            print('Epoch: {}'.format(epoch))
            epoch += 1

            largest_e = 0
            for x, Yd in zip(X, y): # train
                # print('X = {}'.format(x))

                # print('dot = {}'.format(self.dot(x, self.w)))
                Y = self.predict_2(x) # actual output
                # print('Y = {}'.format(Y))

                e = Yd - Y # error
                # print('e = {}'.format(e))

                if abs(e) > abs(largest_e):
                    largest_e = e
                
                delta_w = np.around(self.alpha*e*x[1:], decimals=1) # weight correction
                # print('delta = {}'.format(delta_w))

                self.w[1:] += delta_w # delta rule
                self.w = np.around(self.w, decimals=1) # rounding is very important to get the same output as the sample data
                # print('w = {}'.format(self.w))
                
                print(self.generate_row(x, Yd, Y, e, self.w)) 
                   

    def predict(self, X):
        return self.predict_2(np.concatenate(([1],X),0)) # append the left column to X

            
    def score(self):
        pass






