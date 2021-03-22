# used python3

import os
import gnupg

newFile = open("outputFile", "w")

# for i in range(2):
#     run = "gpg -d checkFile" + str(i) + ".txt"
#     newFile.write(str(os.system(run)))
#     newFile.write('\n')

for i in range(10000):
    run = "gpg --verify checkFile" + str(i) + ".txt"
    newFile.write(str(os.system(run)))
    newFile.write(" ")
    newFile.write("Flag")
    newFile.write(str(i))
    newFile.write('\n')

# key_file_name = open("liber8tion.gpg", "rb")
# gpg = gnupg.GPG()
# encryptedFile = "checkFile0.txt"
# keys = gpg.scan_keys(key_file_name)

# public_keys = gpg.list_keys()
# print(public_keys)
# print(keys)
# for i in range(10000):
#     filename = "checkFile" + str(i) + ".txt"
#     stream = open("checkFile0.txt", "rb")
#     verified = gpg.verify_file(stream)

#     if not verified:
#         pass
#     else:
#         print("Found the fucker")
#         print(filename)
#         break
