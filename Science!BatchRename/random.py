import uuid
import os

n = 100
dir = 'data'

one = 'first'
two = 'second'

if not os.path.isdir(dir):
    os.mkdir(dir)
os.chdir(dir)
for f in os.listdir():
    os.remove(os.path.join(f))

for i in range(n):
    r = str(uuid.uuid4()).split('-')
    filename = f'{one}-{r[0]}-{r[1]}-{r[2]}-{two}-{r[3]}-{r[4]}.png'
    f = open(filename, 'x')
    f.close()
