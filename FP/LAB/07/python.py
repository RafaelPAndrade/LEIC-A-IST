#Rafael Pestana de Andrade
#nº86503



#1.
#
#a)
#Calcula o produto entre x e a soma dos números de 1 a n OU
#Calcula o somatório de: os produtos de x com os números de n a 1
#b) 
#misterio(2,3)
#2*3+misterio(2,2)
#2*3+(2*2+misterio(2,1))
#2*3+(2*2+(2*1+misterio(2,0)))
#2*3+(2*2+(2*1+0))
#2*3+(2*2+(2))
#2*3+(6)
#12
#
#c)f recursiva com operações adiadas, pelas várias operações adiadas 
#durante a sua execução;linear, pois o nº de processos cresce linearmente 
#com o crescimento de n
#
#d)->Dúvida:x podia ser omitido da misterio_aux, como boa prática?

def misterio(x,n):
	def misterio_aux(x,n,res):
		if n==0:
			return res
		else:
			return misterio_aux(x,n-1,res+x*n)

	return misterio_aux(x,n,0)


#-----------------------------------------------------------------------

#2

#a)
def quadrado(n):
	"""
	recursão com operações adiadas
	"""

	if n==0:
		return 0
	else:
		return  ((n+n)-1)+quadrado(n-1)

#b)
def quadrado(n):
	"""
	recursão de cauda
	"""
	def quadrado_aux(n,res):
		if n==0:
			return res
		else:
			return quadrado_aux(n-1, res+((n+n)-1))

	return quadrado_aux(n,0)
	
#c)
def quadrado(n):
	"""
	iteração
	"""
	res=0
	while n>0:
		res+= (n+n)-1	
		n-= 1
	return res


#3
#a)
def numero_digitos(n):
	"""
	recursão com operações adiadas
	"""
	if n< 10:
		return 1
	else:
		return 1+ numero_digitos(n//10)

#b)
def numero_digitos(n):
	"""
	recursão de cauda
	"""
	def numero_digitos_aux(n,res):
		if n< 10:
			return res+1
		else:
			return numero_digitos_aux(n//10, res+1)
	
	return numero_digitos_aux(n,0)

#c)
def numero_digitos(n):
	"""
	processo iterativo
	"""
	res=1
	while not n<10:
		res+= 1
		n= n//10
	return res
#-----------------------------------------------------------------------


#4-capicua ou e_capicua?

def capicua(n):
	def capicua_aux(n, n_dig):
		print(n%10, n//10**(n_dig-1),n)
		if n_dig==1 or n_dig==0:
			return True


		#verifica se o último e o primeiro são iguais
		elif n%10 != n//10**(n_dig-1): 
			return False

		else:
			return capicua_aux((n%10**(n_dig-1))//10, n_dig-2)
		#10^(n_dig-1) é a casa decimal do digito + significativo 
		#do número

	return capicua_aux(n, numero_digitos(n))


#5-pode-se usar strings? e a função numero_digitos?
#assumindo que não

def espelho(n):
	def espelho_aux(n,res):
		if n == 0:
			return res
		else:
			return espelho_aux(n//10,res*10+n%10)

	return espelho_aux(n,0)


#6-recursão de cauda, não sei como fazer recursão suspensa nisto...
def maior_inteiro(limite):	
	def maior_inteiro_aux(limite,n,soma_ns):
		if n+soma_ns > limite:
			return n-1
		else:
			return maior_inteiro_aux(limite, n+1, soma_ns+n)

	return maior_inteiro_aux(limite,1,0)





#7-needs research
"""
def num_divisores(n):
	if n==0:
		return 0
	else:
		return 
"""
#com iteração
def num_divisores(n):
	if n==0:
		return 0
	res=1 #o próprio número
	for i in range(1,n//2+1):
		if n%i==0:
			res+=1
	return res

#attempt: com 






#resposta do professor, tem bug e erro:
def num_divisores_p(n):
	

	def num_divisores_aux(m,n):
		if m==n:
			return 1
		elif n%m:
			return 1+num_divisores_aux(m+1,n)
		else:
			return num_divisores_aux(m+1,n)


	return num_divisores_aux(1,n)





#8-provavelmente não o melhor

def soma_divisores(n):

	def soma_divisores_aux(n,soma,divisor):
		if n==0 or divisor>n:
			return soma
		elif n%divisor!=0:
			return soma_divisores_aux(n, soma, divisor+1)
		else:
			return soma_divisores_aux(n, soma+divisor, divisor+1)


	return soma_divisores_aux(n,0,1)

#9
#a)usando 8b, isto não chega a ser recursão...

def perfeito(n):
	
	def perfeito_aux(n,soma):
		if n != soma-n:
			return False
		else:
			return True


	return perfeito_aux(n, soma_divisores(n))

#b)
def perfeitos_entre(n1, n2):
	if n1> n2:
		return []
	elif not perfeito(n1):
		return perfeitos_entre(n1+1,n2) 
	else:
		return [n1] + perfeitos_entre(n1+1,n2)
	
	
#10

def quicksort(list):
	if len(list)<2:
		return list


	menor=[]
	meio= list[0]
	maior=[]

	for e in list[1:]:
		if e < meio:
			menor+= [e]
		else:
			maior+= [e]
	
	return quicksort(menor)+ [meio] + quicksort(maior)
