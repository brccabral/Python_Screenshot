import screenshot as sc
import ctypes
from PIL import Image


x = 10
y = 10
w = 500
h = 200
size = w * h
objlength = size * 3
result = (ctypes.c_ubyte * objlength)()

sc.take(x, y, w, h, result)
print(result[objlength // 2])
# print(sc.display)
image = Image.frombuffer("RGB", (w, h), result, "raw", "RGB", 0, 1)
image.show()
