import numpy as np 
import matplotlib.pyplot as plt


class GeneticAlgorithm:

    '''constants'''
    NUM_BITS = 4
    NUM_PARENTS = 2
    NUM_GENERATIONS = 50


    def __init__(self, N = 6, p_c = 0.7, p_m = 0.001, lb = 0, ub = 15, max_epochs = 500):
        '''constructor'''
        self.N = N # number of chromosomes in population
        self.p_c = p_c # crossover probability
        self.p_m = p_m # mutation probability
        self.lb = lb # lower fitness bound
        self.ub = ub # upper fitness bound
        self.max_epochs = max_epochs # number of epoches for the GA

    
    def print_header(self):
        '''prints header for results table'''
        print('Chromosome\tString\t\tInteger\tFitness\tFitness Ratio')
    

    def print_table(self, population):
        '''prints results table'''
        self.print_header()
        population_fitness = self.get_population_fitness(population)
        population_fitness_ratios = self.get_population_fitness_ratios(population_fitness)
        for i, (chromosome, fitness, fitness_ratio) in enumerate(zip(population, population_fitness, population_fitness_ratios)):
            print('{}\t\t{}\t{}\t{}\t{}\t'.format(i+1, chromosome, self.decoded_int(chromosome), fitness, fitness_ratio))
        
        print('Average population fitness: {}'.format(self.average_population_fitness(population_fitness)))
        pass


    def plot(self, x, y):
        '''plots results graph'''
        plt.plot(x, y)
        plt.xlabel('Generations')
        plt.ylabel('Fitness')
        plt.title('Fitness vs Generations')
        plt.show()

    
    def fitness_function(self, x):
        '''fitness function'''
        return 15*x - x**2

    
    def get_population_fitness_ratios(self, population_fitness):
        fitness_sum = np.sum(population_fitness)
        fitness_ratios = [fitness/fitness_sum for fitness in population_fitness]
        return fitness_ratios

    
    def get_population_fitness(self, population):
        '''returns the fitness of each chromosome in the population in a 1D numpy array'''
        all_decoded_ints = [self.decoded_int(chromosome) for chromosome in population]
        all_fitnesses = [self.fitness_function(decoded_int) for decoded_int in all_decoded_ints]
        return all_fitnesses
        # pass

    
    def average_population_fitness(self, population_fitness):
        return np.average(population_fitness)
        # pass

    
    def decoded_int(self, chromosome):
        '''converting binary bitstring stored as ints (1 or 0) in numpy array to decimal by bitshifting'''
        decoded = 0
        for gene in chromosome:
            decoded = (decoded << 1) | gene
        return decoded


    def generate_population(self, random=False):
        '''either randomly generated or hardcoded initial parents'''

        if random:
            return np.random.randint(2, size=(self.N, self.NUM_BITS))
        else:
            return np.array([
                [1,1,0,0],
                [0,1,0,0],
                [0,0,0,1],
                [1,1,1,0],
                [0,1,1,1],
                [1,0,0,1]
            ])
        # pass
    

    def select(self, population, population_fitness_ratios):
        '''selects 2 parents based on fitness ratios'''
        # p is an array of indices referring to the rows of the population 2d array
        p = np.random.choice(a=self.N, size=self.NUM_PARENTS, p=population_fitness_ratios) 
        return [population[p[0]], population[p[1]]]

    
    def crossover(self, parents):
        '''swaps genes of two parents after a random crossover_index'''
        # get crossover point
        crossover_index = np.random.randint(low=0, high=self.NUM_BITS)

        # swapping
        parents[0][crossover_index:], parents[1][crossover_index:] = parents[1][crossover_index:], parents[0][crossover_index:]
        return parents
        # pass
    

    def mutate(self, parent):
        '''flips a randonly selected bit in a single chromosome'''
        mutation_index = np.random.randint(low=0, high=self.NUM_BITS)
        if parent[mutation_index] == 0:
            parent[mutation_index] = 1
        else:
            parent[mutation_index] = 0
        return parent
        # pass
    

    def epoch(self, population):
        '''a single epoch (selection, crossover, mutation, new population)'''

        # getting population fitness and ratios
        population_fitness = self.get_population_fitness(population)
        population_fitness_ratios = self.get_population_fitness_ratios(population_fitness)

        # empty np.array for new population
        new_population = np.empty((0,self.NUM_BITS))

        # until we have enough chromosomes in the new population
        while len(new_population) < self.N:

            # select
            parents = self.select(population, population_fitness_ratios)

            # crossover probability
            if np.random.uniform() <= self.p_c:
                children = self.crossover(parents)

                # mutation probability
                if np.random.uniform() <= self.p_m:
                    children = [self.mutate(children[0]), self.mutate(children[1])]
            
            # if no crossover then just clone
            else:
                children = parents
            
            # add to new population
            new_population = np.append(new_population, children, axis=0)

        return new_population
        # pass


    def run(self):
        '''all the epochs'''

        self.population = self.generate_population(random=False) # generate initial population

        epoch = 1 # keep track of generation number
        graph_gen = [] # for graph plotting
        graph_fitness = [] # for graph plotting
        self.print_table(self.population) # print initial table of values

        # until constraint is met
        while epoch < self.NUM_GENERATIONS:

            self.population = self.epoch(self.population).astype(int) # select, crossover, mutate

            # results after each generation
            print('Epoch: {}'.format(epoch))
            self.print_table(self.population)
            # print('Average population fitness: {}'.format(self.average_population_fitness(self.get_population_fitness(self.population))))
            
            # graph data
            graph_fitness.append(self.average_population_fitness(self.get_population_fitness(self.population)))
            graph_gen.append(epoch)
            
            epoch += 1
        
        # final results
        self.print_table(self.population)

        # graph fitness vs generations
        self.plot(graph_gen, graph_fitness)

        pass
        



