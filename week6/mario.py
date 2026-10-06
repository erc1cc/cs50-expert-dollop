import cs50

def print_pyramid():
    height = cs50.get_int("Height: ")
    if 0 < height < 9:
        for i in range(height):
            print((" " * (height - i - 1)) + ("#" * (i + 1)) + "  " + ("#" * (i + 1)))
    else:
        print_pyramid()


print_pyramid()
