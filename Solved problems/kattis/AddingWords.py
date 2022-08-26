import sys

def main():
    word2val = dict()
    val2word = dict()
    for line in sys.stdin:
        line = line.strip()
        tokens = line.split()
        command = tokens[0]
        if command == 'clear':
            word2val.clear()
            val2word.clear()
        elif command == 'def':
            w = tokens[1] # word
            v = int(tokens[2]) # value
            if w in word2val: # caso borde
                old_v = word2val[w]
                # del word2val[w] # overkill, pero por si las moscas
                del val2word[old_v] # sí o sí
                # del val
            word2val[w] = v
            val2word[v] = w
        else:
            assert command == 'calc' # paranoico
            try:
                res = word2val[tokens[1]]
                for i in range(2, len(tokens)-1, 2):
                    if (tokens[i] == '+'):
                        res += word2val[tokens[i+1]]
                    else:
                        res -= word2val[tokens[i+1]]
                res = val2word[res]
            except KeyError:
                res = 'unknown'
            print(line[5:], res)

main()