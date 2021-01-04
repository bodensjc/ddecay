import os
os.chdir('C:\\Users\\johnb\\Documents\\LHCb\\LHCb')



lfn = open('dplfns_dec20.txt','r')
magup = open('dplfns_magup.txt', 'w')
magdown = open('dplfns_magdown.txt', 'w')

lines = lfn.readlines()


#dplus parser
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





lfn = open('dsplfns_dec20.txt','r')
magup = open('dsplfns_magup.txt', 'w')
magdown = open('dsplfns_magdown.txt', 'w')

lines = lfn.readlines()


#dsplus parser
upi=0
downi=0
upj=1
downj=1
magup.write('dspmagup{0}.root\n'.format(upj))
magdown.write('dspmagdown{0}.root\n'.format(downj))
for line in lines:
    up = line.find('MagUp')
    down = line.find('MagDown')
    if up != -1:
        line = line.replace('\n',' ')
        magup.write(line[up+13:])
        upi += 1
        if upi == 60:
            upj+=1
            magup.write('\n\ndspmagup{0}.root\n'.format(upj))
            upi=0
    if down != -1:
        line = line.replace('\n',' ')
        magdown.write(line[down+16:])
        downi += 1
        if downi == 60:
            downj+=1
            magdown.write('\n\ndspmagdown{0}.root\n'.format(downj))
            downi=0
    else:
        pass