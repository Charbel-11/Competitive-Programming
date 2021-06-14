T = int(input())

for z in range(T):
    lin1 = input()
    lin1 = lin1.split()
    swordsTypes = int(lin1[0])
    maxSkillDif = int(lin1[1])
    
    C=[]
    D=[]
    l2 = input().split()
    l3 = input().split()
    for i in range(swordsTypes):
        C.append(int(l2[i]))
        D.append(int(l3[i]))
        
    Cmax=[[-1 for i in range(swordsTypes)] for j in range(swordsTypes)]
    Dmax=[[-1 for i in range(swordsTypes)] for j in range(swordsTypes)]
    
    for i in range(swordsTypes):
        Cmax[i][i]=C[i]
        Dmax[i][i]=D[i]
    
    for i in range(swordsTypes):
        for j in range(i, swordsTypes):
            if Cmax[i][j-1]!=-1:
                Cmax[i][j]=max(Cmax[i][j-1],C[j])
            else:                
                Cmax[i][j]=max(C[i:j+1])
            
            if Dmax[i][j-1]!=-1:
                Dmax[i][j]=max(Dmax[i][j-1],D[j])
            else:                
                Dmax[i][j]=max(D[i:j+1])
       
    fair=0         
    for i in range(swordsTypes):
        for j in range(i, swordsTypes):
            if abs(Cmax[i][j]-Dmax[i][j])<=maxSkillDif:
                fair+=1
    
    print("Case #"+str(z+1)+": "+str(fair))