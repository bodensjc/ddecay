import os
os.chdir('C:\\Users\\johnb\\Documents\\LHCb\\LHCb')



lfn = open('dp_lfns_raw.txt','r')
magup = open('dp_lfns_magup.txt', 'w')
magdown = open('dp_lfns_magdown.txt', 'w')

lines = lfn.readlines()


upi=0
downi=0
upj=1
downj=1
magup.write('dpmagup{0}.root\n'.format(upj))
magdown.write('dpmagdown{0}.root\n'.format(downj))
for line in lines:
    up = line.find('MagUp')
    down = line.find('MagDown')
    if up != -1:
        line = line.replace('\n',' ')
        magup.write(line[up+13:])
        upi += 1
        if upi == 60:
            upj+=1
            magup.write('\n\ndpmagup{0}.root\n'.format(upj))
            upi=0
    if down != -1:
        line = line.replace('\n',' ')
        magdown.write(line[down+15:])
        downi += 1
        if downi == 60:
            downj+=1
            magdown.write('\n\ndpmagdown{0}.root\n'.format(downj))
            downi=0
    else:
        pass




'''
#second oldest parser
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

'''
#oldest parser
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