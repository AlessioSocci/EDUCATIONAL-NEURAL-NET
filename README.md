# EDUCATIONAL-NEURA

EDUCATIONAL-NEURAL-NET

A simple implementation of a feed forward artificial neural net.

Training set is created and saved in a file by recalling a function that generate two random input number between 0 and 1, and an output number by squaring its, for two thousand times: this is the epochs for net training. In header is printed the topology of net, two neurons in input layer, four in hidden and one in output.

Main method recall a constructor defined in Net class to create the net. This constructor creates a Net object by instantiating a vector container with anothers vectors container four elements, rapresenting Neuron object, for each layer of the net. In other words, a "container" matrix for each the three layers, with number of neuron in row, and elements of Neuron object in columns.

Neuron object, in its turn, is created by the constructor defined in Neuron class; constructor instantiate a vector container with a simple struct as elements and an index natural number, for each of its output (number of its outputs is equal of number of neuron in next layer). The Struct as two double type elements: weights and delta-weights. Weight, for first time, is ranodm assigned, delta is not assinged.

In a main loop, repeated for two thousand times:

Call a method defined in training class, assings the training data set input value to a vector container, reading some specified string in the training file.

Execute forward propagation by appling a method defined in Net class. This recall the neuron beahviour: sum of each input mulpilied by each connection weight, passed through activation fucntion ("hyperbolic tangent" here).

Print on screen the result of propagation and, by reading the correct string in training file, the desired out ("target value").

Execute back propagation method to recalculate the weights of neuron connections.

Print on screen the error between target and output at this step.

During the loop error tends to zero and in the end, now net is trained.
