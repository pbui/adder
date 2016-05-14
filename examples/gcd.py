a = input "A?"
b = input "B?"

while b != 0
    t = b
    b = a % b
    a = t

print a
