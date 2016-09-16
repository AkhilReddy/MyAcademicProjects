import sys
import re

def lex(characters, token_exprs):
    pos = 0
    i = 0
    tokens = []
    print 'Length of Characters: \n'
    print len(characters)
    print '\n'
    while pos < len(characters):
        match = None
        for token_expr in token_exprs:
            pattern, tag = token_expr
            regex = re.compile(pattern)
            print regex
            print '\n'
            match = regex.match(characters, pos)
            print match
            print '\n'
            if match:
                print i
                i=+1
                print match
                text = match.group(0)
                if tag:
                    token = (text, tag)
                    tokens.append(token)
                break
        if not match:
            sys.stderr.write('Illegal character: %s\n' % characters[pos])
            sys.exit(1)
        else:
            pos = match.end(0)
    return tokens
