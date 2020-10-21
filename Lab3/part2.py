i = 1 
j = 1 
n = 6 # Size of the grid
mont=0 

routefound = 0 # counter for number of cases where the final point is reached
gotStuck = 0 # counter for number of cases where no valid optionions found
coordList = [[i, j]]

while mont < 10000:
    while True:
        validchoices = []

        option1 = [i - 1, j]
        option2 = [i, j + 1]
        option3 = [i + 1, j]
        option4 = [i, j - 1]

        # Check 4 possible optionions out of bound and re-visited coordinates are
        # discarded:

        if option1[0] != 0 and option1[0] <= n and option1[1] != 0 and option1[1] <= n:
            if not option1 in coordList:
                validchoices.append(option1)

        if option2[0] != 0 and option2[0] <= n and option2[1] != 0 and option2[1] <= n:
            if not option2 in coordList:
                validchoices.append(option2)

        if option3[0] != 0 and option3[0] <= n and option3[1] != 0 and option3[1] <= n:
            if not option3 in coordList:
                validchoices.append(option3)

        if option4[0] != 0 and option4[0] <= n and option4[1] != 0 and option4[1] <= n:
            if not option4 in coordList:
                validchoices.append(option4)

        # Break loop if there are no valid optionions
        if len(validchoices) == 0:
            gotStuck = gotStuck + 1
            coordList = [[1,1]]
            i,j = (1,1)
            break

        # Get random coordinate among current valid optionions
        new_coord = random.choice(validchoices)

        # Append new coordinate to the list of grid points visited (to be used
        # for checks)
        coordList.append(new_coord)

        # Break loop if lower right corner of the grid is reached
        if new_coord == [n, n]:
            routefound = routefound + 1
            coordList = [[1,1]]
            i,j = (1,1)
            break
        # If the loop is not broken, assign new coordinates
        i = new_coord[0]
        j = new_coord[1]
    mont = mont + 1




print float(routefound) / float(routefound+gotStuck)