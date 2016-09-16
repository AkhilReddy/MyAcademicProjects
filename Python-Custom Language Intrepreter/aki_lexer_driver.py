import sys
from aki_lexer import *

if __name__ == '__main__':
    filename = sys.argv[1]
    file = open(filename)
    characters = file.read()
    print characters
    file.close()
    tokens = imp_lex(characters)
    print tokens
    print '\n'
    for token in tokens:
        print token
