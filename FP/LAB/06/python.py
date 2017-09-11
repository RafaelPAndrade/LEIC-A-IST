#coding:utf8
#Rafael Pestana de Andrade
#5/XI/16


#1
#a)
#    i)Soma dos números entre 4 e 500
#   ii)Soma dos quadrados dos números de 5 em 5, entre 5 e 500
#  iii)Soma dos somatórios entre 1 a 5, i.e., somatório de 1 a 1+ somatório de 1 a 2+ somatório de 1 a 3...
#
#b)

def piatoria(inf,sup,calc_term,prox):
	produto=1
	while inf<=sup:
		produto = produto*calc_term(inf)
		inf = prox(inf)
	return produto
#c)
#por exemplo, 5!=
piatoria(1,5,lambda x: x, lambda x:x+1)

#
#-------------------//---------------------
#


#2-sem recursão
#a)

def filtra(tst,lst):
	res=[]
	for e in lst:
		if tst(e):
			res+=[e]
	return res

#b)

def transforma(fn,lst):
	res=[]
	for e in lst:
		res+= [fn(e)]

#c)

def acumula(fn,lst):
	soma=0
	for e in lst:
		soma+= fn(e)


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

#3

def soma_quadrados_impares(lst):
	return acumula(lambda x:x**2, filtra(lambda x: x%2!= 0, lst ) )



#4
#usando funcionais sobre listas=usando filtra,transforma e acumula

def todos_lista(lst,tst):
	return len(filtra(tst,lst))==len(lst)



#5

#função concentra-aplica a operação op a todos os algarismos de o número dado
def concentra(op, num):
	if num < 10:
		return num
	else:
		return op(num % 10, concentra(op, num // 10))

def produto(n):
	return (concentra(lambda x,y: x*y,n))


#6
#def muda:aplica fn a cada um dos algarismos individuais de num
#def num_digitos: para saber qual a potência de 10 a aplicar
def muda(fn, num):
	if num < 10:
		return fn(num)
	else:
		nn = fn(num % 10)
		return nn + 10 ** num_digitos(nn) * muda(fn, num // 10)
def num_digitos(n):
	if n < 10:
		return 1
	else:
		return 1 + num_digitos(n // 10)



def soma_dois(num):
	return(muda(lambda x:x+2,num))


#7??

"""
def junta_listas(lst):
	return acumula(lambda x:x, lst)
"""






#8
#talvez não seja assim

def nenhum_p(n,tst):
	if n==0:
		return True
	if tst(n):
		return False
	else:
		return nenhum_p(n-1,tst)

#9

def soma_quadrados(n):
	return acumula(lambda x:x,transforma(lambda x:x**2,list(range(1,n+1))))







#10-doubts; sei fazer sem funções de ordem superior

















































