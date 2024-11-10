import argparse
import os
import subprocess
import sys
import time

def main():
    # Read arguments
    parser = argparse.ArgumentParser()
    parser.add_argument('--executable_command', type=str, required=True)
    parser.add_argument('--inputs_folder', type=str, required=True)
    parser.add_argument('--outputs_folder', type=str, required=True)
    parser.add_argument('--time_limit', type=int, default=5)
    parser.add_argument('--dump_and_stop_with_wa', action='store_true')
    args = parser.parse_args()

    # Read input and output files
    if (args.inputs_folder == args.outputs_folder):
        # Special case: assume inputs have even indices and outputs have odd indices
        files = os.listdir(args.inputs_folder)
        n = len(files)
        input_files = [files[i] for i in range(n) if i % 2 == 0]
        output_files = [files[i] for i in range(n) if i % 2 == 1]
    else:
        input_files = os.listdir(args.inputs_folder)
        output_files = os.listdir(args.outputs_folder)
    
    assert len(input_files) == len(output_files)

    # Test each input-output pair
    for fin, fout in zip(input_files, output_files):
        print('%s: ' % fin, end='')
        with open(os.path.join(args.inputs_folder, fin)) as f:
            # Set a time limit of 5 seconds, otherwise interrupt the process
            try:
                start_time = time.time()
                main_answer = subprocess.run(args.executable_command, stdin=f, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=args.time_limit)
                end_time = time.time()
                elapsed_time = end_time - start_time
            except subprocess.TimeoutExpired:
                print("TLE")
                continue
        if main_answer.returncode != 0:
            print("Runtime Error.")
            print(main_answer.stderr)
        else:
            with open(os.path.join(args.outputs_folder, fout)) as f:
                expected_output = f.read().strip()
                generated_output = str(main_answer.stdout, encoding='utf8').strip()
                expected_output = expected_output.replace('\r', '').strip()
                generated_output = generated_output.replace('\r', '').strip()
                if generated_output != expected_output:
                    print(f"WA :( ({elapsed_time:.2f}s)")
                    print(f'len(expected_output) = {len(expected_output)}')
                    print(f'len(generated_output) = {len(generated_output)}')
                    # identify the chars that are different
                    for i in range(min(len(expected_output), len(generated_output))):
                        if expected_output[i] != generated_output[i]:
                            print(f'expected_output[{i}] = {expected_output[i]}')
                            print(f'generated_output[{i}] = {generated_output[i]}')
                            break
                    if args.dump_and_stop_with_wa:
                        # dump each output to temp files
                        with open('tmp_expected_output.txt', 'w') as f:
                            f.write(expected_output)
                            print(f'Expected output dumped to tmp_expected_output.txt')
                        with open('tmp_generated_output.txt', 'w') as f:
                            f.write(generated_output)
                            print(f'Generated output dumped to tmp_generated_output.txt')
                        sys.exit(0) # exit with error
                else:
                    print(f'AC ({elapsed_time:.2f}s)')

if __name__ == '__main__':
    main()
