import math
import sys

def kmeans(K, input_data, iter = 200):

    points = []
    epsilon = 0.001

    with open(input_data, 'r') as file:
        for line in file:
            line = line.replace("\n", "")
            arr = line.split(",")
            for i in range(len(arr)):
                arr[i] = float(arr[i])
            points.append(arr)
    
    N = len(points)

    # Validate number of clusters (K)
    if K >= N:
        print("Invalid number of clusters!")
        sys.exit()
    

    d = len(points[0])
    CurKmeans = [points[i][:] for i in range(K)] #deep clone
    
    numIter = 0

    while numIter < iter:

        NextKmeans = [[0]*d for i in range(K)]
        counter = [0] * K
        for i in range(N):
            minDistance = math.inf
            minK = 0
            for j in range(K):
                eucdisfromcurk = euclideanDistance(points[i], CurKmeans[j])
                if minDistance > eucdisfromcurk:
                    minDistance = eucdisfromcurk
                    minK = j
            for j in range(d):
                NextKmeans[minK][j] += points[i][j]
            counter[minK] += 1
        for i in range(K):
            if counter[i] != 0:
                for j in range(d):
                    NextKmeans[i][j] = (NextKmeans[i][j] / counter[i])

        cnt = 0
        for i in range(K):
            if euclideanDistance(NextKmeans[i], CurKmeans[i]) < epsilon:
                cnt += 1
        if cnt == K:
            break
        
        CurKmeans = NextKmeans
        numIter += 1
    
    return [[format(round(i, 4), ".4f") for i in vector] for vector in CurKmeans]


def euclideanDistance(p, q):
    sum_sq = sum((a - b) ** 2 for a, b in zip(p, q))
    return math.sqrt(sum_sq)



if len(sys.argv) >= 3:
        try:
                K = sys.argv[1]
                if '.' in K:
                    float_value = float(K)
                    if not K.endswith('.0'):
                        raise ValueError
                    K = int(float_value)
                else:
                    K = int(K)
        except (IndexError, ValueError):
                print("Invalid number of clusters!")
                sys.exit()
        if K <= 1:
            print("Invalid number of clusters!")
            sys.exit()
        if len(sys.argv) == 3:        
              Kmeans = kmeans(K, sys.argv[2])
        
        else: 
            try:
                iter = sys.argv[2]
                if '.' in iter:
                    float_value = float(iter)
                    if not iter.endswith('.0'):
                        raise ValueError
                    iter = int(float_value)
                else:
                    iter = int(iter)
            except (IndexError, ValueError):
                print("Invalid maximum iteration!")
                sys.exit()
            
            if iter <= 1 or iter >=1000:
                print("Invalid maximum iteration!")
                sys.exit()
            Kmeans = kmeans(K, sys.argv[3],iter)

for arr in Kmeans:
            st = ""
            for i in range(len(arr)-1): st += str(arr[i]) + ","
            st += str(arr[len(arr)-1])
            print(st)



             
                