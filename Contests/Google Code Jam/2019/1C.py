T = int(input())

for z in range(T):
    adv = int(input())
    letters=[0]*502
    inputs=[]
    imp = False
    res=""
    maxL=0
    
    for i in range(adv):
        cur = input()
        inputs.append(cur)
        
        if len(cur)>maxL:
            maxL=len(cur)
        
        if (cur==""):
            break
        
        if letters[0]==0:
                letters[0]=[cur[0]]
        else:
            if cur[0] not in letters[0]:
                if len(letters[0])==2:
                    imp = True
                else:
                    letters[0].append(cur[0])
    
    if imp:
        print("Case #"+str(z+1)+": IMPOSSIBLE")
    else:
        i = 0            
        if len(letters[i])==1:
                if letters[i][0]=="P":
                    res+="S"
                elif letters[i][0]=="S":
                    res+="R"
                else:
                    res+="P"
        else:
                if (letters[i][0]=="P" or letters[i][1]=="P") and (letters[i][0]=="R" or letters[i][1]=="R"):
                    res+="P"
                elif (letters[i][0]=="P" or letters[i][1]=="P") and (letters[i][0]=="S" or letters[i][1]=="S"):
                    res+="S"
                elif (letters[i][0]=="S" or letters[i][1]=="S") and (letters[i][0]=="R" or letters[i][1]=="R"):
                    res+="R"
        
        for j in range(adv):
            if inputs[j][0]=="P" and res[0]=="S": 
                inputs[j]=False
            elif inputs[j][0]=="S" and res[0]=="R":
                inputs[j]=False
            elif inputs[j][0]=="R" and res[0]=="P":
                inputs[j]=False
           
        i=1
        while(i<=adv):
            for j in range(adv):
                if inputs[j]!=False:
                    cur = inputs[j]
                    if i>=len(cur):
                        continue

                    if letters[i]==0:
                        letters[i]=[cur[i]]
                    else:
                        if cur[i] not in letters[i]:
                            if len(letters[i])==2:
                                imp = True
                                break
                            else:
                                letters[i].append(cur[i])
                 
            if imp==True:
                break
            if letters[i]!=0 and len(letters[i])==1:
                    if letters[i][0]=="P":
                        res+="S"
                    elif letters[i][0]=="S":
                        res+="R"
                    else:
                        res+="P"
            elif letters[i]!=0:
                    if (letters[i][0]=="P" or letters[i][1]=="P") and (letters[i][0]=="R" or letters[i][1]=="R"):
                        res+="P"
                    elif (letters[i][0]=="P" or letters[i][1]=="P") and (letters[i][0]=="S" or letters[i][1]=="S"):
                        res+="S"
                    elif (letters[i][0]=="S" or letters[i][1]=="S") and (letters[i][0]=="R" or letters[i][1]=="R"):
                        res+="R"
            
            if letters[i]!=0:
                for j in range(adv):
                    if inputs[j]==False or i>=len(inputs[j]) or i>=len(res):
                        continue
                    if inputs[j][i]=="P" and res[i]=="S": 
                        inputs[j]=False
                    elif inputs[j][i]=="S" and res[i]=="R":
                        inputs[j]=False
                    elif inputs[j][i]=="R" and res[i]=="P":
                        inputs[j]=False
            i+=1

        
        if imp:
            print("Case #"+str(z+1)+": IMPOSSIBLE") 
        else:
            
            while res in inputs:
                if res[0]=="P":
                    res+="S"
                elif res[0]=="S":
                    res+="R"
                else:
                    res+="P"
                    
            len2=len(res)       
            for j in range(adv):
                if (inputs[j]==0):
                    break
                if inputs[j]==False:
                    continue
                cur = inputs[j]
                len1=len(cur)
                if len1<len2:
                    win=False
                    temp = len1
                    while temp<len2:
                        modT = temp%len1
                        if res[temp]=="R":
                            if cur[modT]=="S":
                                win=True
                                break
                            elif cur[modT]=="P":
                                imp=True
                                break
                        elif res[temp]=="P":
                            if cur[modT]=="R":
                                win=True
                                break
                            elif cur[modT]=="S":
                                imp=True
                                break
                        else:
                            if cur[modT]=="P":
                                win=True
                                break
                            elif cur[modT]=="R":
                                imp=True
                                break
                        temp+=1
                    if not win:
                        imp=True
                        break
                        
                if imp:
                    print("Case #"+str(z+1)+": IMPOSSIBLE")
                    break
            
            if imp or len(res)>adv:
                print("Case #"+str(z+1)+": IMPOSSIBLE")
            else:    
                print("Case #"+str(z+1)+": "+res)