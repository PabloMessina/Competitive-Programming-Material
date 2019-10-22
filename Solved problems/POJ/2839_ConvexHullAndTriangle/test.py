import subprocess
import sys
import tqdm

try:
    n = int(sys.argv[1])
    generator = sys.argv[2]
    canonical_command = sys.argv[3]
    main_command = sys.argv[4]
except:
    print("Usage: python test.py <n> <generator> <canonical> <program being tested>")
    sys.exit(0)

for _ in tqdm.trange(n):
    test = subprocess.run(generator.split(), stdout=subprocess.PIPE).stdout
    canonical_answer = subprocess.run(canonical_command.split(), input=test, stdout=subprocess.PIPE)
    main_answer = subprocess.run(main_command.split(), input=test, stdout=subprocess.PIPE)
    if canonical_answer.returncode != 0:
        print()
        print("Canonical program crashed.")
        print("Test:")
        print(test)
        with open("failed_input", "wb") as outfile:
            outfile.write(test)
        sys.exit(0)
    if main_answer.returncode != 0:
        print()
        print("Main program crashed.")
        print("Test:")
        print(test)
        with open("failed_input", "wb") as outfile:
            outfile.write(test)
        sys.exit(0)
    if canonical_answer.stdout != main_answer.stdout:
        print()
        print("Test:")
        print(test)
        print("Canonical Answer:")
        print(canonical_answer.stdout)
        print("Main Answer:")
        print(main_answer.stdout)
        with open("failed_input", "wb") as outfile:
            outfile.write(test)
        sys.exit(0)
