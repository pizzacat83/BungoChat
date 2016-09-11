src=[s.decode('utf-8') for s in open(r"F:\aozora\kokoro\kokoroserif.txt", "r") if s[0]!="#"]
from random import choice
while True:
	raw_input("user: ")
	print "soseki:", choice(src).encode('shift-jis')