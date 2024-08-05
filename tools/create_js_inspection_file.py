import argparse
import jsbeautifier
import os
import sys

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("dir", type=str, help="The directory to find .js files in")
    args = parser.parse_args()

    with open("out.js", 'w') as log:
        for root, dirs, files in os.walk(args.dir):
            for file_name in files:
                if file_name.endswith(".js"):
                    with open(os.path.join(root, file_name), 'r') as f:
                        log.write(f"/* START {file_name}\n------------------------------------------------*/\n\n")
                        log.write(jsbeautifier.beautify(f.read()))
                        log.write(f"/* END {file_name}\n------------------------------------------------*/\n\n")


    return 0

if __name__ == "__main__":
    sys.exit(main())
