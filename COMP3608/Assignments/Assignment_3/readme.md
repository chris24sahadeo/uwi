# Assignment 3

> 816000772

## Question 1: Perceptron
-**Note:** Python has rounding errors. Must use `numpy.around()` to get the same output as [Dr Kieu's backpropagation notes](https://drive.google.com/file/d/1sNgPj750QpbAAFMif8oEUYHkBP6Sz1iJ/view)  

`perceptronAND.py` and `perceptronOR.py` both import the `perceptron.py` module.


## Question 2: Multilayer Perceptron

Multilayer Perception with 1 hidden layer trained with backpropagation (vectorized batch gradient descent)
Code based loosely on [Dr Kieu's backpropagation notes](https://drive.google.com/file/d/16erGrxD0JBa4YXfwU-1F6Kfv2O3KxTq_/view) but also incorportating a vectorized approached.

Output identical to lecture notes.

SSE converges after about 60000 epochs. This is not uncommon for MLPs, however the textbook said it should take only 250 epochs. Is the vast disparity in epochs required due to my using a batch update approach?

`bpXOR.py` imports the `mlp.py` module

Graph output shows the decrease of SSE over time (epochs)


## Question 3: Genetic Algorithms
Algorithm closely follows [Dr Kieu's GA notes](https://drive.google.com/file/d/1N2yghRfR1rOeC2BDlrzluJ74vWuophyt/view)

Tested with the recommended crossover and mutation probabilities and 50 generations. This typically results in the accurate maximum fitness ($56$) for the function $15x-x^2$

Graph output shows the increase of population fitness over time (generations).

`GA_runner.py` imports the `GA.py` module
