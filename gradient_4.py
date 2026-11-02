
# Function
def f(x):
    return (x + 3)**2

# Derivative
def df(x):
    return 2 * (x + 3)

# Initial values
x = 2
learning_rate = 0.1
iterations = 50

# Gradient Descent
for i in range(iterations):
    x = x - learning_rate * df(x)

print("Minimum x:", x)
print("Minimum y:", f(x))
