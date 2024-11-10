import argparse
import subprocess
import time

def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Time a shell command.")
    parser.add_argument("--command", type=str, required=True, help="The command to execute.")
    args = parser.parse_args()

    # Capture the start time
    start_time = time.time()

    # Run the command
    try:
        result = subprocess.run(args.command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Command failed with exit code {e.returncode}")
        return

    # Capture the end time
    end_time = time.time()

    # Calculate and print the execution time
    elapsed_time = end_time - start_time
    print(f"Execution Time: {elapsed_time:.2f} seconds")

if __name__ == "__main__":
    main()
