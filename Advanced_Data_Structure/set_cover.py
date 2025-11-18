def greedy_set_cover(universe, subset):
    #initilase uncovered element
    uncovered = set(universe)
    # set to add cover element set
    covered = []
    
    while uncovered:
        # choose subset that cover most uncovered element
        best = max(subset,key=lambda s:len(uncovered & s))

        '''
        best = None
        max_covered = -1

        for s in subset:
            covered_count = len(uncovered & s)
            if covered_count > max_covered:
                max_covered = covered_count
                best = s
        '''
        uncovered -= best
        covered.append(best)

    return covered

# generate tan point
universe = set(range(1,13))

#define subset
subset = [
    {1,3,5,7,9,11},     #s1
    {2,4,6,8,10,12},    #s2
    {1,4,5},            #s3
    {2,3,6},            #s4
    {7,9,11},           #s5
    {8,10,12}           #s6
]

cover = greedy_set_cover(universe,subset)

print("Selected subset for set cover: ")

for i,subset in enumerate(cover):
    print(f"S{i+1} = {sorted(subset)}")
