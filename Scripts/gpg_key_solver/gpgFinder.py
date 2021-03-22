# used python3

import os

flagFile = open('FlagInHaystack.txt', 'r')
lines = flagFile.readlines()

path = "checkFile"
filenum = 0
end = ".txt"
currentFile = path + str(filenum) + end
newFile = open(currentFile, "w")
filenum += 1
substring = "END PGP SIGNATURE"

for line in lines:
    if(line.find(substring) == -1):
        newFile.write(line)
    else:
        newFile.write(line)
        currentFile = path + str(filenum) + end
        newFile.close()
        newFile = open(currentFile, "w")
        filenum += 1



# current = 1
# p = input()
# while(p != 'q'):
#     print(current, " out of ", filenum)
#     run = "gpg -d checkFile" + str(current) + end
#     os.system(run)
#     current += 1
#     p = input()

flagFile.close()
