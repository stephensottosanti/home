flag = input("Enter flag to rotate: ")
x = flag[0]
rot = 0

while (x != 'S'):
    if ((ord(x) + 1) > 90):
        new = ((ord(x) + 1) % 90) + 64
    else:
        new = ord(x) + 1

    x = chr(new)
    rot += 1


for letter in flag:
    if (letter.isalpha()):
        if ((ord(letter) + rot) > 90):
            new = ((ord(letter) + rot) % 90) + 64
        else:
            new = ord(letter) + rot

        letter = chr(new)

    print(letter, end = "")

print("\n")
