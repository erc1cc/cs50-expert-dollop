import cs50
import re

def check_card(num):
    numstr = str(num)

    if re.match(r"^4", numstr) and (len(numstr) == 13 or len(numstr) == 16):
        print("VISA")
    elif re.match(r"^3[47]", numstr) and len(numstr) == 15:
        print("AMEX")
    elif re.match(r"^5[1-5]", numstr) and len(numstr) == 16:
        print("MASTERCARD")
    else:
        print("INVALID")


def checksum(n):
    # converts n to an array from an int
    n = [int(digit) for digit in str(n)]
    n = n[::-1]

    sum = 0
    for i in range(len(n)):
        if i % 2 != 0:
            doubled = (2 * n[i])
            if doubled > 9:
                sum += (doubled % 10) + 1
            else:
                sum += doubled
        else:
            sum += n[i]

    if sum % 10 == 0:
        return True
    else:
        return False


number = cs50.get_int("Number: ")
if checksum(number) == True:
    check_card(number)
else:
    print("INVALID")
