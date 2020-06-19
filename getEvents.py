# Your list of file names here
FILES = ['/LHCb/Collision17/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo04/94000000/CHARMCHARGED.MDST']

if __name__ == '__main__':
    from subprocess import call
    from sys import argv

    n_files = len(FILES)
    if len(argv) > 1:
        n_files = int(argv[1])

    files = FILES[:n_files]
    for f in files:
        print('Getting file {0}.'.format(f))
        call('dirac-dms-get-file {0}'.format(f), shell=True)
    print('Done getting {0} files.'.format(n_files))