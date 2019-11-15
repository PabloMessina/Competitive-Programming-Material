import subprocess
import sys
import os

try:
    main_command = sys.argv[1]
    inputs_folder = sys.argv[2]
    outputs_folder = sys.argv[3]
except:
    print("Usage: python test_written_cases.py <program being tested> <inputs folder> <outputs folder>")
    sys.exit(0)


input_files = os.listdir(inputs_folder)
output_files = os.listdir(outputs_folder)
print("input_files = ", input_files, len(input_files))
print("output_files = ", output_files, len(output_files))
assert len(input_files) == len(output_files)
n = len(input_files)

for fin, fout in zip(input_files, output_files):
    assert (fin == fout)
    print('%s: ' % fin, end='')
    with open(os.path.join(inputs_folder, fin)) as f:
        main_answer = subprocess.run(main_command, stdin=f, stdout=subprocess.PIPE)
    if main_answer.returncode != 0:
        print("Main program crashed.")
        sys.exit(0)
    with open(os.path.join(outputs_folder, fout)) as f:
        expected_output = f.read()        
        if str(main_answer.stdout, encoding='utf8').strip() != expected_output.strip():
            print("WA :(")
            print("Expected Answer:")
            print(expected_output)
            print("Main Answer:")
            print(main_answer.stdout)
            sys.exit(0)
        print("OK!")
print("Accepted :)")
