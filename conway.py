bits = [0]*512

for i in range(512):
    tobin = format(i,'b')
    neighbors = len([x for x in tobin if (x == '1')])

    if i%2 == 1:
        # we are alive
        if neighbors == 4 or neighbors == 3:
            # we have 2 or 3 neighboring live cells
            bits[i] = 1
        else:
            # otherwise, we die by overpopulation or underpopulation
            bits[i] = 0
    else:
        # we are dead
        if neighbors == 3:
            # we live by reproduction
            bits[i] = 1
        else:
            bits[i] = 0
    


ruleset = "ruleset = [" +("".join([str(i)+"," for i in bits]))[:-1] + "];"
print(ruleset)
