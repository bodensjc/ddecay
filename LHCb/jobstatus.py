#print out the count of subjob statuses, ex: "ganga jobstatus.py 73" 73 is job#

import sys
from collections import Counter
list=[]
jobNumber = int(sys.argv[1])
for sj in jobs(jobNumber).subjobs:
    list = list+[sj.status]
length = len(list)
a = dict(Counter(list))
print("Total of {0} subjobs\n".format(length))
print(a)