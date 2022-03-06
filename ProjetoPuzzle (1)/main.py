from sys import stdin, stdout


def readln():
    return stdin.readline().rstrip()


def outln(n):
    stdout.write(str(n))
    stdout.write("\n")

# ter a solucao como variavel global para não ser preciso passar os parametros das linhas e colunas

def puzzle(pecas, nlin, ncol):
    solucao = [[[0 for i in range(4)] for j in range(ncol)] for k in range(nlin)]

    auxlin = 0
    auxcol = 0
    pecaPosta = 0 # nao foi colocada, 1 se for

    print("solucao", solucao)
    solucao[0][0] = pecas[0]
    #print("solucao", solucao)
    # print("pecas:", len(pecas))

    while(pecaPosta == 0):
        for i in range(1, len(pecas)):

            # direita
            if (pecas[i][1] == solucao[auxcol][auxlin][0] and pecas[i][2] == solucao[auxcol][auxlin][3]):
                auxlin += 1
                auxcol += 1
                solucao[auxcol][auxlin] = pecas[i]


            #fazer para acrescentar na linha
            # nlin++

            #tentar colocar a peça na mesma
            if (auxlin <= nlin):
                if (pecas[i][1] == solucao[auxcol][auxlin][0] and pecas[i][2] == solucao[auxcol][auxlin][3]):
                    auxlin += 1
                    auxcol += 1
                    solucao[auxcol][auxlin] = pecas[i]
                    pecaPosta = 1
                else:
                    pecaR = rotacao(pecas[i])
                    pecaPosta = 0


            #fazer para acrescentar na coluna
            # ncol++
            # tentar com todas as pecas
            # senao rodar 1 a 1 e experimentar todas até alguma dar ou até ao fim



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

    return peca


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
