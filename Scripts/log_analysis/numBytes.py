# used Python3

readfile = open("/home/user/Competitions/ncl/preSeason/logAnalysis/temp", "r")

lines = readfile.readlines()

numBytes = 0

for line in lines:
    numBytes += int(line)

print(numBytes)
