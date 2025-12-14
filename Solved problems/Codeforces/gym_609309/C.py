def main():
    t = int(input())
    for _ in range(t):
        matrix = []
        for i in range(8):
            row = input().strip()
            matrix.append(row)
        for c in range(8):
            found_start = False
            for r in range(8):
                if 'a' <= matrix[r][c] <= 'z':
                    found_start = True
                    r_start = r
                    break
            if found_start:
                word = ''
                for r in range(r_start, 8):
                    if 'a' <= matrix[r][c] <= 'z':
                        word += matrix[r][c]
                    else:
                        break
                print(word)

if __name__ == "__main__":
    main()