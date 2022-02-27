from sys import stdin,stdout

def readln():
    return stdin.readline().rstrip()

def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def puzzle(pecas):
    a = 0
    
    #fazer rotacao da peca
    rotacao(pecas[0])
    print("Rotacao: ", pecas[0])

def rotacao(peca):
    aux = peca[len(peca) - 1]
    for i in range(len(peca) - 1, -1, -1):
        peca[i] = peca[i-1]
    peca[0] = aux

if __name__ == "__main__":
    n = readln()
    dim = readln()
    #while (dim != None and dim != ''):
    for i in range(int(n)):
        array = []
        for i in range(int(dim[0])):
            piece = readln().split()
            array.append(piece)
        print("array", array)
        dim = readln()
        puzzle(array)
