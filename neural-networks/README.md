# neural-networks

## Modelling neural networks using Clojure. 

At the moment this produces a quil animation, which shows a single perceptron with three inputs (two coordinates and a bias) learning how to recognise whether a point is above or below a given line. 

A filled dot means the perceptron guesses that the point is below the line, and an empty dot means the perceptron guesses that the point is above the line. Every time the app starts a new perceptron is generated, with random weights between -1 and 1.

Every 300 points the screen gets refreshed to show the learning process better, and the applet runs for 2000 learning points.

The activation algorithm is a simple sign function, and it is learning using supervised learning.

## Installation

Download from https://github.com/ioannad/experiments/tree/master/neural-networks/

## Usage

Build with `./build.sh`

Run applet with `./perceptron.sh`

## License

Distributed under the Eclipse Public License version 1.0
