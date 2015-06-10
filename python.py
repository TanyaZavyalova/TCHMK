#!/Library/Frameworks/Python.framework/Versions/2.7
import sys
import verylong as lib

try:
	a=sys.argv[4]
except:
	print "Enter correct Parameters"
	exit()

first=lib.veryLong()
second=lib.veryLong()
third=lib.veryLong()
fourth=lib.veryLong()
binary=False

arg=6
try:
	a=sys.argv[6]
	arg=6
except:
	arg=5

if arg==6:
	binary=True
	module=True
	fourth.rdb(sys.argv[6])
else:
	try:
		a=sys.argv[5]
		arg=5
	except:
		arg=4

	if arg==5:
		if sys.argv[5]=="-b":
			binary=True
			module=False
		else:
			binary=False
			module=True
			fourth.rd(sys.argv[5])
	else:
		binary=False
		module=False

first.binary=binary
second.binary=binary
fourth.binary=binary

if binary == False:
	first.rd(sys.argv[1])
	second.rd(sys.argv[3])
else:
	first.rdb(sys.argv[1])
	second.rdb(sys.argv[3])

sign=sys.argv[2]

if sign=="+":
	third=first+second
elif sign=="-":
	third=first-second
elif sign=="*":
	third=first*second
elif sign=="/":
	third=first/second
elif sign=="%":
	third=first%second
elif sign=="^":
	third=first^second

if module==True:
	third=third%fourth;

third.out(sys.argv[4])
print "Success"
