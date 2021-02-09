import os
os.chdir('/data/home/bodensjc/ddecay')

data = open('notes.txt')
data = data.readlines()[345:-7]
data = [line.replace('\n','')[1:] for line in data]
data = [line.split('\t') for line in data]
print(data)

def separate(lst):
	return [int(item[0]) for item in lst], [int(item[1]) for item in lst], [int(item[2]) for item in lst]


mev, dm, dsm = separate(data)
print(mev)
print(dm)
print(dsm)	
print(len(mev), len(dm), len(dsm))
print(mev[80])
