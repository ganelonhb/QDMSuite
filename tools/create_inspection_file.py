import argparse
import jsbeautifier
import os
import subprocess
import sys

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("dir", type=str, help="The directory to find .js files in")
    parser.add_argument("--test", action="store_true", help="test the js files")
    args = parser.parse_args()

    with open("out.js", 'w') as log:
        for root, dirs, files in os.walk(args.dir):
            for file_name in files:
                if file_name.endswith(".js"):
                    with open(os.path.join(root, file_name), 'r') as f:
                        log.write(f"/* START {file_name}\n------------------------------------------------*/\n\n")
                        script = jsbeautifier.beautify(f.read())
                        log.write(script)
                        if args.test:
                            process = subprocess.Popen(['node', '-'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

                            stdout, stderr = process.communicate(input=f"{script}console.log(nameGen())")

                            print(f"{os.path.join(root, file_name)} : {stdout}")
                            with open("logtest.out", 'a') as f:
                                f.write(f"{os.path.join(root, file_name)} : {stdout}\n\n")


                        log.write(f"/* END {file_name}\n------------------------------------------------*/\n\n")


    return 0

if __name__ == "__main__":
    sys.exit(main())
