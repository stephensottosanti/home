# used python3

text = input("Enter string in all lowercase for reverse rot for second input: ")
reverseRot = int(input("integer for reverseRot: "))

for x in text:
    new = ord(x) - reverseRot
    if (new < 97):
        new += 26

    x = chr(new)
    print(x, end = "")

print("\n")
