from sys import stdin, stdout


def readln():
    return stdin.readline().rstrip()


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")


def puzzle(pecas, nlin, ncol):
    solucao = [[[0 for i in range(4)] for j in range(ncol)] for k in range(nlin)]

    print("solucao", solucao)
    solucao[0][0] = pecas[0]
    #print("solucao", solucao)
    # print("pecas:", len(pecas))
    for i in range(1, len(pecas)):
        nlin = 0
        ncol = 0
        # direita
        if (pecas[i][1] == solucao[ncol][nlin][0] and pecas[i][2] == solucao[ncol][nlin][3]):
            nlin += 1
            ncol += 1
            solucao[ncol][nlin] = pecas[i]

    print(solucao)
    # 0 1    0 1
    # 3 2    3 2

    # 1 2    2 1
    # 4 3    3 4


def rotacao(peca):
    aux = peca[len(peca) - 1]
    for i in range(len(peca) - 1, -1, -1):
        peca[i] = peca[i - 1]
    peca[0] = aux


if __name__ == "__main__":
    n = readln()
    dim = readln().split()
    print("DIMENSAO:", dim)
    print(int(dim[1]))
    print(int(dim[2]))

    # while (dim != None and dim != ''):
    for i in range(int(n)):
        array = []
        for i in range(int(dim[0])):
            piece = readln().split()
            array.append(piece)
        print("array", array)
        puzzle(array, int(dim[1]), int(dim[2]))
        dim = readln().split()
