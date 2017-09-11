#2-com recursão, sem variáveis de estado
#a)

def filtra(tst,lst):
	if lst==[]:
		return lst
	elif tst(lst[0]):
		return [lst[0]] + filtra(tst,lst[1:])
	else:
		return filtra(tst,lst[1:])

#b)

def transforma(fn,lst):
	if lst==[]:
		return lst
	else:
		return [fn(lst[0])]+transforma(fn, lst[1:])

#c)

def acumula(fn,lst):
	if lst==[]:
		return 0
	else:
		return fn(lst[0])+acumula(fn,lst[1:])

def lista_dig(n):
    return transforma(lambda x:int(x), filtra(lambda x:x, list(str(n))))

def filtra_impares(n):
	return filtra(lambda x: x%2!=0, lista_dig(n))

