import sys

ln= input()
T = int(ln[0])

for z in range(T):    
    print(6)
    sys.stdout.flush()
    d6=int(input())  
    
    print(7)
    sys.stdout.flush()
    d7=int(input())
    
    print(5)
    sys.stdout.flush()
    d5=int(input())
    
    print(12)
    sys.stdout.flush()
    d12=int(input())
    
    print(11)
    sys.stdout.flush()
    d11=int(input())

    print(8)
    sys.stdout.flush()
    d8=int(input())

    R1=(d7-d6)/64    
    R5=(-d12+2*d11)/4
    R4=-(d6-2*d5+2*R5)/2

    d5m=d5-32*R1-2*R4-2*R5           #d5m=4*R2+2*R3+R6
    d11m=d11-(2**11)*R1-4*R4-4*R5    #d11m=32*R2+8*R3+2*R6

    eq1=d11m-2*d5m                   #eq1=24*R2+4*R3

    R2=(d8-d7-128*R1-2*R4)/8
    R3=(eq1-24*R2)/4
    
    R6=d5-32*R1-4*R2-2*R3-2*R4-2*R5

    print(str(int(R1))+" "+str(int(R2))+" "+str(int(R3))+" "+str(int(R4))+" "+str(int(R5))+" "+str(int(R6)))
    
    ver=input()
    if (ver==-1):
        break