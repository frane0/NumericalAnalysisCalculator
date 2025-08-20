# Numerical Analysis Calculator

This project is a tool for making numerical calculations. It is made for the semester project of Numerical Analysis course at Yıldız Technical University. The project requirements can be found [here](https://drive.google.com/file/d/1Q2WFCe0GWdqJwzVzIHOXvKcb1HJzTQGi/view?usp=drive_link) (The file is in Turkish).

## How to Use?
The calculator asks for the numerical method first. User enters a number to choose the corresponding method. Implemented methods are:
1. Bisection
2. Regula-Falsi
3. Newton-Rapshon
4. Inverse of an NxN Matrix
5. Gauss Elimination
6. Gauss-Seidel
7. Numerical Differentiation
8. Simpson’s Rule (1/3 and 3/8 Rules)
9. Trapezoidal Rule
10. Gregory-Newton Interpolation without Variable Transformation

Then, depending on the selected method, the user is asked to enter a matrix or function. After that, program asks for needed parameters. And finally, the program starts the iterations. If it doesn't converge, it stops and prints final values to the user. (Convergence conditions are given by user so it can iterate endlessly.)
* ### How to enter the function?
1. Use only "x" for the variable, "+" for summation, "-" for subtraction, "*" for multiplication, "/" for division and "^" for power operations.
2. For example, $`3x^2+5x+8`$ has to be entered in a form like that:
`3*x^2+5*x+8`
3. If you are not sure, use brackets to indicate the priority of the terms.
4. DO NOT use the SPACE character.
5. You can use sin() for sine, cos() for cosine, tan() for tangent, cot() for cotangent, sec() for secant, csc() for cosecant. You can also use inverse trigonometric functions by adding arc at the beginning of the function. (e.g. arccos(), arctan()...)
7. You can use log_(base)() or ln() for logarithm.
8. You can use "pi" for $`\pi`$ and "e" for $`e`$.
9. Decimal numbers are supported. (1.25 etc.)
* Some Examples:

$3\sin^{5x}(x)$ : `3*sin^(5*x)(x)`

$2\log_{0.5}(\sin(x))$ : `2*log_(0.5)(sin(x))`

$-e^{2x+4}$ : `-e^(2*x+4)`

More detailed explanation can be found [here](https://drive.google.com/file/d/121iX2QlCVMSmyatAt8r1OqkUZmEPSFHV/view?usp=sharing) (The file is in Turkish).

## How Does It Work?
Parsing the string is being done in 3 steps. 

### 1. Split the String Into Terms
At this step, program splits the string by using "+" and "-" characters. It counts the opening and closing brackets to differentiate if it is a composite function or a new term. It creates an array of term strings without changing the order.

### 2. Determine the Types and Create the Tree
At this step, program determines the types of every term and creates the linked list of Term structs. Construction of the tree is explained below in the "Data Structure" part.

### 3. Parse the Composite Functions and Fill the Structs
At this step, program parses the string inside of every bracket couple. This is being done with recursion so the program runs these 3 steps for every couple of brackets. For each of them, it creates a new branch in the tree and fills every struct in this step.
