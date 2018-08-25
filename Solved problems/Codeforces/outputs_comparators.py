with open('./output_mio.out') as f:
    my_ouput = list(map(float, f.readlines()))
with open('./output_chino.out') as f:
    his_ouput = list(map(float, f.readlines()))
assert(len(my_ouput) == len(his_ouput))
for i, (x1, x2) in enumerate(zip(my_ouput, his_ouput)):
    if abs(x1 - x2) > 1e-6:
        print('test %d: yo=%.8lf chino=%.8lf' % (i+1, x1, x2))