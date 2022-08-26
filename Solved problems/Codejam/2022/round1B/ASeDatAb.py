def main():    
    T = int(input())
    for _ in range(1, T+1):
        i = 0
        query = list("00000000")
        print(''.join(query))
        feedback = int(input())
        while feedback != -1 and feedback != 0:
            n_ones = feedback
            query = list("00000000")
            for i in range(n_ones):
                query[i] = '1'
            print(''.join(query))
            feedback = int(input())

main()