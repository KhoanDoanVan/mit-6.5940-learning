import argparse
import sys
from pathlib import Path

# add root path để import utils
sys.path.append(str(Path(__file__).resolve().parents[1]))

from utils.utils import rename_images

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("path", type=str, help="Path to image folder")
    args = parser.parse_args()

    count = rename_images(args.path)
    print(f"Renamed {count} images")

if __name__ == "__main__":
    main()



# Example script cli:

# (.venv) ➜  mit-65940 git:(main) ✗ python scripts/rename_images.py src/Lecture\ 02/images