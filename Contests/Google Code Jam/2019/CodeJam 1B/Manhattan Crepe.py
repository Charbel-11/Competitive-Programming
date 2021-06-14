T = int(input())

for z in range(T):
    lin1 = input()
    lin1 = lin1.split()
    people = int(lin1[0])
    maxCoord = int(lin1[1])
    
    X=[]
    Y=[]
    Dir=[]
    for i in range(people):
        l = input().split()
        X.append(int(l[0]))
        Y.append(int(l[1]))
        Dir.append(l[2])
                
    NorthArr=[0 for i in range(maxCoord+1)]
    SouthArr=[0 for i in range(maxCoord+1)]
    EastArr=[0 for i in range(maxCoord+1)]
    WestArr=[0 for i in range(maxCoord+1)]
    
    for i in range(people):
        if Dir[i]=="N":
            NorthArr[Y[i]+1]+=1
        elif Dir[i]=="S":
            SouthArr[Y[i]-1]+=1
        elif Dir[i]=="E":
            EastArr[X[i]+1]+=1
        else:
            WestArr[X[i]-1]+=1
     
    for i in range(1, maxCoord+1):
        NorthArr[i]+=NorthArr[i-1]
        EastArr[i]+=EastArr[i-1]
    for i in range(maxCoord-1, -1, -1):
        SouthArr[i]+=SouthArr[i+1]
        WestArr[i]+=WestArr[i+1]
        
    finalX=0
    finalY=0
    maxWantedN=0
    maxWantedE=0
    for i in range(maxCoord+1):
        NorthArr[i]+=SouthArr[i]
        EastArr[i]+=WestArr[i]
        if NorthArr[i]>maxWantedN:
            maxWantedN=NorthArr[i]
            finalY=i
        if EastArr[i]>maxWantedE:
            maxWantedE=EastArr[i]
            finalX=i
         
    print("Case #"+str(z+1)+": "+str(finalX)+" "+str(finalY))