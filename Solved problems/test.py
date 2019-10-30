import subprocess
import sys
import tqdm

try:
    n = int(sys.argv[1])
    folder = sys.argv[2]
    generator = sys.argv[3]
    canonical = sys.argv[4]
    main = sys.argv[5]
    generator_command = "python %s/%s" % (folder, generator)
    canonical_command = "%s/%s" % (folder, canonical)
    main_command = "%s/%s" % (folder, main)
except:
    print("Usage: python test.py <n> <folder> <generator> <canonical> <program being tested>")
    sys.exit(0)

for _ in tqdm.trange(n):
    test = subprocess.run(generator_command.split(), stdout=subprocess.PIPE).stdout
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
        with open("%s/failed_input" % folder, "wb") as outfile:
            outfile.write(test)
        sys.exit(0)
