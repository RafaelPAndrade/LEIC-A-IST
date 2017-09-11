#coding:utf-8
#para fazer load de forma dinâmica dentro da shell do python, correr
# >>>exec(open("./exerciciosfp_9-X.py").read())
#no diretório que contém o ficheiro


#1
"""
def cinco(a):
	return a == 5
"""

#2
"""
def horas_dias(horas):
	return horas/24
"""

#3
"""
def area_circulo(raio):
	PI=3.14
	return PI*raio**2
"""

#4-(deixar #3 sem comentário)
#duvida- como se lança um value error-vide p 210 pavao
"""
def area_coroa(r1, r2):
	if r2>r1:
		return (area_circulo(r2) - area_circulo(r1))
	else:
		raise ValueError('r2 tem de ser maior do que r1')
"""


#5-1ª tentativa
"""
def trocos(dinheiro):
	dinheiro = dinheiro*100
	print("São precisas:")
	for i in (5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1):
		n_monetario = dinheiro//i
		print(n_monetario, "de", i/100)
		dinheiro = dinheiro%i
	return True
"""


#5-2ª tentativa

def trocos(dinheiro):
	res=()
	dinheiro = dinheiro*100
	for i in (5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1):
		n_monetario = dinheiro//i
		res=res+(n_monetario,)
		dinheiro = dinheiro%i
	return res








#6

def bissexto(ano):
	if ano%4==0:
		if ano%100==0 and ano%400!=0:
			return False
		else:
			return True
	else:
		return False


#7-deixar o 6 descomentado E no input, usar [""], se não NameError

def dia_mes(mes, ano):
	if mes=="jan" or mes=="mar" or mes=="mai" or mes=="jul" or mes=="ago" or mes=="out" or mes=="dez":
		return 31
	if mes=="fev":
		if bissexto(ano):
			return 29
		else:
			return 28
	if mes=="abr" or mes=="jun" or mes=="set" or mes=="nov":
		return 30
	else:
		raise ValueError('Mês inválido')



#8a
"""
def valor(q,j,n):
	if j <= 0 or j >= 1:
		raise ValueError('Juros fora de limites')
	if q <= 0:
		raise ValueError('Capital fora de limites')
	if n%1 != 0 or n<0:
		raise ValueError('Anos fora de limites')

	return q*(1+j)**n
"""

#8b-deixar 8a descomentado
"""
def duplicar(q,j):
	resultado = 2*q
	n=1
	while valor(q,j,n)< resultado:
		n += 1
	return n
"""


#9-deixar 6 descomentado (bissexto)


def dia_mes(mes, ano): #ve quantos dias ha num ano
	if mes==1 or mes==3 or mes==5 or mes==7 or mes==8 or mes==10 or mes==12:
		return 31
	if mes==2:
		if bissexto(ano)==True:
			return 29
		else:
			return 28
	if mes==4 or mes==6 or mes==9 or mes==11:
		return 30
	else:
		raise ValueError('Mês inválido')


def check(dia,mes,ano): #verifica se nao ha value errors
	if dia>dia_mes(mes,ano):
		raise ValueError("Dia inválido")
	else:
		return True


def chão(a): #faz o chao
	a= int(a)
	return a

def contas(dia, mes, ano): #aplica a formula, em que a,b,c,... são as parcelas a somar e fazer mod 7
	if mes==1:
		ano=ano-1
		mes=13

	if mes==2:
		ano=ano-1
		mes=14


	J = (ano//100) #ERRO DE ENUNCIADO-J é o século - 1
	K = ano % 100


	a = dia
	b = chão((13*(mes+1))/5)
	c = K
	d = chão(K/4)
	e = chão(J/4)
	f = (-2)*J

	return (a+b+c+d+e+f)%7


def dia_da_semana(dia, mes, ano): #faz tudo
	if check(dia,mes,ano) != True:
		print("Deu erro")
	else:
		resposta = contas(dia,mes,ano)
		if resposta==0:
			print("Sábado")
		if resposta==1:
			print("Domingo")
		if resposta==2:
			print("Segunda")
		if resposta==3:
			print("Terça")
		if resposta==4:
			print("Quarta")
		if resposta==5:
			print("Quinta")
		if resposta==6:
			print("Sexta")

