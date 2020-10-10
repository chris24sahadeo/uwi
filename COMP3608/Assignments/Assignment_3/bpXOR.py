import numpy as np 
from mlp import MLPClassifier


# training data
X = np.array(
    [
        [0, 0],
        [0, 1],
        [1, 0],
        [1, 1]
    ]
)

y = np.array(
    [[
        0,
        1,
        1,
        0,
    ]]
)
y = np.transpose(y)


mlp = MLPClassifier() # make object

mlp.fit(X, y, W_h=[[0.5, 0.9], [0.4, 1.0]], W_o=[-1.2, 1.1], t_h=[0.8, -0.1], t_o=[0.3]) # train model with specfic weights
# mlp.fit(X, y) # train model with random inits


# predicting
print('\n\nPrediction')
print('x1\tx2\ty')
for x in X:
    print('{}\t{}\t{}'.format(x[0], x[1], mlp.predict(x)[0]))