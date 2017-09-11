#Rafael P Andrade
#n. 86503


#a
"""
Tipo tempo


-Contrutor

faz_tempo: inteiro x inteiro --> tempo
faz_tempo(h,m) recebe dois argumentos do tipo inteiro: h, hora e m, minuto
e devolve um elemento do tipo tempo


-Seletores

h_tempo:  tempo ---> inteiro
h_tempo(t) recebe um elemento do tipo tempo (t)
e devolve um elemento do tipo inteiro correspondendo às horas

m_tempo:  tempo ---> inteiro
m_tempo(t) recebe um elemento do tipo tempo (t)
e devolve um elemento do tipo inteiro correspondendo aos minutos


-Reconhecedor

e_tempo: universal ---> Booleano
e_tempo(x) devolve True se x fôr do tipo tempo
e False se x não fôr desse tipo


-Teste

igual_tempo: tempo x tempo ---> Booleano
igual_tempo(t1, t2) devolve True se t1 e t2 forem elementos do tipo tempo iguais
e False caso contrário


-Transformador

num_tempo:  tempo ---> inteiro
num_tempo(t) recebe um elemento do tipo tempo (t)
e devolve um elemento inteiro contendo o valor numérico total de minutos

str_tempo:  tempo ---> cadeia de caracteres
str_tempo(t) recebe um elemento do tipo tempo (t)
e devolve um elemento do tipo cadeia de caracteres que, uma vez impressa, mostra:
  hhh:mm

"""



#b
"""
R[horas:minutos]=(horas, minutos)
"""



#c


def faz_tempo(h,m):
	return (h,m)



def h_tempo(t):
	return t[0]

def m_tempo(t):
	return t[1]


def e_tempo(x):
	if not isinstance(x, tuple):
		return False
	elif len(x)!=2:
		return False
	if not isinstance(x[0], int) or not isinstance(x[1], int):
		return False	
	if h_tempo(x)<0:
		return False
	if m_tempo(x)>=60 or m_tempo(x)<0:
		return False
	return True

def igual_tempo(t1,t2):
	if h_tempo(t1)== h_tempo(t2) and m_tempo(t1)==m_tempo(t2):
		return True
	else:
		return False


def num_tempo(t):
	return h_tempo(t)*60+m_tempo(t)

def str_tempo(t):
	return str(h_tempo(t))+':'+str(m_tempo(t))




#d

def depois(t1,t2):
	return num_tempo(t1)>num_tempo(t2)
