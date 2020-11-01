import os
os.chdir('C:\\Users\\johnb\\Documents\\LHCb\\LHCb')



lfn = open('maguplfns.txt','r')
dplfn = open('dplfns.txt', 'w')
dsplfn = open('dsplfns.txt','w')

lines = lfn.readlines()

dspi=0
dpi=0
dspj=1
dpj=1

dsplfn.write('dsp{0}.root\n'.format(dspj))
dplfn.write('dp{0}.root\n'.format(dpj))

for line in lines:
    dsp = line.find('Dsp')
    dp = line.find('Dp')

    if dsp != -1:
        line=line.replace('\n',' ')
        dsplfn.write(line[dsp+21:])
        dspi += 1
        if dspi==60:
            dspj+=1
            dsplfn.write('\n\ndsp{0}.root\n'.format(dspj))
            dspi=0     
    if dp != -1:
        line=line.replace('\n',' ')
        dplfn.write(line[dp+20:])
        dpi += 1
        if dpi==60:
            dpj+=1
            dplfn.write('\n\ndp{0}.root\n'.format(dpj))
            dpi=0

    else:
        pass


'''


dplfn = open('dplfns.txt', 'r')
newdp = open('dplfns2.txt', 'w')

lines = dplfn.readlines()
soct = len(lines)//60

i=0
for line in lines:
    line = line.replace('\n',' ')
    newdp.write(line)
    i+=1
    if i==60:
        newdp.write('\n\n\n')
        i=0


'''