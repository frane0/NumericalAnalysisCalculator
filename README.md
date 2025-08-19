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
1. Use "+" for summation, "-" for subtraction, "*" for multiplication, "/" for division and "^" for power operations.
2. This ($`\sqrt{\$4}`$) function has to be in a form like that:
```c
3*x^2+5*x+8
```
## How Does It Work?
Parsing the string
