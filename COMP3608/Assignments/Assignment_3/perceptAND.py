import numpy as np 
from perceptron import Perceptron

X = np.array(
    [
        [0, 0],
        [0, 1],
        [1, 0],
        [1, 1]
    ]
)

y = np.array(
    [
        0,
        0,
        0,
        1,
    ]
)

p = Perceptron() # make object
p.fit(X, y) # train

# predicting
print('Prediction')
print('x1\tx2\ty')
for x in X:
    print('{}\t{}\t{}'.format(x[0], x[1], p.predict(x)))