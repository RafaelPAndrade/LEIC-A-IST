#Rafael P. Andrade
#26/11/2016
#FP exercicios semanais, no 9


#1
#a)
#-cria_rac(num, den): construtor do tipo racional

#cria_rac:inteiro x inteiro --> racional
#cria_rac(num,den) recebe dois argumentos do tipo inteiro(numerador e denominador) e devolve um elemento do tipo racional


#-num_rac(r):seletor do tipo racional

#num_rac:racional-->inteiro
#num_rac(r) recebe um número racional e devolve o numerador respetivo


#-den_rac(r):seletor

#den_rac:racional-->inteiro
#den_rac(r) recebe um número racional e devolve o numerador respetivo


#-float_rac(r): Transformador, transforma em float

#float_rac:racional-->decimal 
#float_rac(r) recebe um tipo racional e devolve um tipo racional(float) com o mesmo valor numerico


#-e_rac(x):reconhecedor do tipo racional

#e_rac:universal-->Booleano
#e_rac(x) devolve True se x e um elemento do tipo Racional e False se nao o for



#-igual_rac(a,b):teste, compara igualdade




#b)tuplo de dois elementos (num, den), pois este é um tipo imutável

#R[num/den]=(num, den)


#c)

def cria_rac(num, den):
	if not isinstance((num,den), int): 
		raise TypeError('Arguments must be integers')
	return (num, den)

def num_rac(r):
	return r[0]

def den_rac(r):
	return r[1]

def float_rac(r):
	return (num_rac(r))/(den_rac(r))

def e_rac(x):
	if not isinstance(x, tuple):
		return False
	elif len(x)!= 2:
		return False
	elif not isinstance( ( num_rac(x),den_rac(x) ) ,int):
		return False
	return True

def igual_rac(a,b):
	if num_rac(a)*den_rac(b)== num_rac(b)*den_rac(a):
		return True
	return False	




#c)
def escreve_rac(r):
	print(str(num_rac(r))+'/'+str(den_rac(r)))
