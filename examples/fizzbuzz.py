i = 1
while i <= 100
    s = ''

    if i % 3 == 0
        s = s + 'Fizz'
    if i % 5 == 0
        s = s + 'Buzz'
    if not s
        s = i

    i = i + 1
    print s
