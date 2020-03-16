import sys

def main():
    lines = sys.stdin.readlines()
    lines = [line.strip() for line in lines]
    maxlen = max(len(line) for line in lines)
    print('*' * (maxlen + 2))
    left = True
    for line in lines:
        space = maxlen - len(line)
        if space % 2 == 0:
            lpad = rpad = space // 2
        elif left:
            lpad = space // 2
            rpad = space - lpad
            left = False
        else:
            rpad = space // 2
            lpad = space - rpad
            left = True
        print('*%s%s%s*' % (' ' * lpad, line, ' ' * rpad))
    print('*' * (maxlen + 2))

main()