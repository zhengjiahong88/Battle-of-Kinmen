from PIL import Image
import math

KM = 16
WIDTH = 44
HEIGHT = 38
MAP = 1080

class Pos:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __add__(self, other):
        if isinstance(other, Pos):
            return Pos(self.x + other.x, self.y + other.y)
    def __sub__(self, other):
        if isinstance(other, Pos):
            return Pos(self.x - other.x, self.y - other.y)
    def __rsub__(self, other):
        if isinstance(other, int):
            return Pos(other - self.x, other - self.y)
    def __mul__(self, other):
        if isinstance(other, int):
            return Pos(self.x * other, self.y * other)
        elif isinstance(other, Pos):
            return Pos(self.x * other.x, self.y * other.y)
    def __truediv__(self, other):
        if isinstance(other, int):
            return Pos(self.x / other, self.y / other)
    def __eq__(self, other):
        if isinstance(other, Pos):
            return self.x == other.x and self.y == other.y
        return False
    def __str__(self):
        return f"Pos({self.x}, {self.y})"
    def __abs__(self):
        return Pos(abs(self.x), abs(self.y))

    def copy(self):
        return Pos(self.x, self.y)
    def inRange(self):
        return 0 <= self.x < WIDTH and 0 <= self.y < HEIGHT
    def toFPoint(self):
        pos = self * GAP + ORIGIN
        if self.x % 2: pos.y += GAP.y / 2
        return pos
    def toPoint(self):
        index = self - ORIGIN
        x = round(index.x / GAP.x)
        if x % 2: index.y -= GAP.y / 2
        y = round(index.y / GAP.y)
        xy = Pos(x, y)
        center = xy.toFPoint()
        rel = abs(self - center)
        if math.sqrt(3) * rel.x + rel.y > math.sqrt(3) * KM:
            xy.x += -1 if self.x < center.x else 1
            xy.y += x % 2 - (self.y < center.y)
        return xy

GAP = Pos(KM * 1.5, math.sqrt(3) * KM)
ORIGIN = (MAP - Pos(3 * (WIDTH - 1), math.sqrt(3) * (2 * HEIGHT - 1)) * KM / 2) / 2
FORM = Pos(WIDTH, HEIGHT)

class Terrain:
    def __init__(self):
        self.mountain = 0
        self.land = 0
        self.sea = 0

class Basemap:
    def __init__(self):
        self.basemap = [[Terrain() for _ in range(WIDTH)] for _ in range(HEIGHT)]
    def __getitem__(self, pos):
        return self.basemap[pos.y][pos.x]
    def __setitem__(self, pos, terrain):
        self.basemap[pos.y][pos.x] = terrain

img = Image.open("basemap.png")
basemap = Basemap()
for x in range(img.width):
    for y in range(img.height):
        pos = Pos(x, y).toPoint()
        if pos.inRange():
            r, g, b, a = img.getpixel((x, y))
            if r == 170:
                basemap[pos].mountain += 1
            elif g == 170:
                basemap[pos].land += 1
            elif b == 170:
                basemap[pos].sea += 1
            else:
                print(f"Unknown color: 0x{r:02X}{g:02X}{b:02X}{a:02X} at ({x}, {y})")
for y in range(HEIGHT):
    for x in range(WIDTH):
        pos = Pos(x, y)
        if basemap[pos].sea > (basemap[pos].land + basemap[pos].mountain) * 6: print('S', end='')
        elif basemap[pos].land > basemap[pos].mountain * 6: print('L', end='')
        else: print('M', end='')
    print()