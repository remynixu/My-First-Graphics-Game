# For the png-to-xd image format converter xd

import struct
from PIL import Image

# To enable taking command-line arguments...

import os
import sys

def png_to_xd(png_path, out_path):
    image = Image.open(png_path).convert('RGBA')
    if image.width > 65_535 or image.height > 65_535:
        return -1
    header = struct.pack('<HH', *image.size)
    buffer = image.tobytes()
    with open(out_path, 'wb') as f:
        f.write(header)
        f.write(buffer)
    return 0

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: python {sys.argv[0]} <in.png> <out.xd>")
        sys.exit(-1)
    print(f"Converting:{sys.argv[1]} -> {sys.argv[2]}")
    if png_to_xd(sys.argv[1], sys.argv[2]) != 0:
        print("[PNG_TO_XD]:\'Image too big!\'")
    else:
        print("Converting succeeded!")