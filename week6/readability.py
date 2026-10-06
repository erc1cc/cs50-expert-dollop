import cs50
import re

def count_letters(string):
    letters = 0
    for i in string:
        if i.isalpha() == True:
            letters += 1
    return letters

string = cs50.get_string("Text: ")
letters = count_letters(string)
words = len(string.split())
# does not do well with words like 'Dr.' and 'U.S.A', etc
sentences = len(re.split(r"[.!?]+", string)) - 1

L = 100 * (letters / words)
S = 100 * (sentences / words)

grade = round(0.0588 * L - 0.296 * S - 15.8)
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade: {grade}")

