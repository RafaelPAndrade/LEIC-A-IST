n=round(eval(input("n= ")))

n_dig=0


if n == 0:
	n_dig=1
else:

	while n != 0:
		n_dig= n_dig+1
		n= n//10

print(n_dig)
