#coding:utf-8
#para fazer load de forma dinâmica dentro da shell do python, correr
# >>>exec(open("./exerciciosfp_13-X.py").read())
#no diretório que contém o ficheiro


#1
"""
a)
output:
3
4
5
7


b)
output:
80
72
64
56
48
40
32
24


c)
output:
0 4 5
0 4 3
"""



#2
"""
soma=0
for i in range(20,0,-2):
	soma += 1
print("Soma =", soma)
"""


#3
"""
def explode(n):
	if n%1 != 0:
		raise ValueError("Nº não inteiro")

	res=()
	while n>0:
		digito=n%10
		add = (digito, )
		res= add+res
		n=n//10

	return res
"""



#4for
"""
def implode(t):
	if not isinstance(t,tuple):
		raise ValueError("Quero um tuplo,sff")
	n=0
	for e in t:
		if not isinstance(e,int):
			raise ValueError("Tuplo que só tenha inteiros, sff")
		if e<0 or e>10:
			raise ValueError("Tuplo que só contenha algarismos, sff")
		n=n*10+e
	return n

"""


#4while
"""
def implode(t):
	if not isinstance(t,tuple):
		raise ValueError("Quero um tuplo,sff")
	n=0
	i=0

	while i<len(t):
		if not isinstance(t[i],int):
			raise ValueError("Tuplo que só tenha inteiros, sff")
		if t[i]<0 or t[i]>10:
			raise ValueError("Tuplo que só contenha algarismos, sff")
		n=n*10+t[i]
		i += 1
	return n
"""



#5=3???



#6
"""
def reconhece(str):

	letra=('A','B','C','D')
	numeros=('1','2','3','4')

	for i in range(len(str)):
		if str[i] not in letra and str[i] not in numeros:
			return False
		if str[i+1] in letra and str[i] in numeros:
			return False
		if str[i] in numeros and str[i+1] in letra:
			return False
		if i == len(str)-2:
			break
	return True
"""




#7

"""
def codifica(n):

	a=str(n)
	res=()

	for e in a:
		e=int(e)
		if e%2==0:
			e=(e+2)%10
		else:
			e=(e-2)%10

		add=(e,)
		res=res+add
	return res
"""



#8
"""
def filtra_pares(t):

	if not isinstance(t,tuple):
		raise TypeError("Tuplo, sff")

	res=()
	for e in t:
		if not isinstance(e,int):
			raise TypeError("Tuplo com inteiros, sff")
		if e<0 or e>10:
			raise ValueError("Tuplo com algarismos, sff")


		if e%2==0 :
			add= (e,)
			res= add+res

	return res
"""


#9
"""
def amigas(a,b):

	if len(a) != len(b):
		raise ValueError("Palavras com comprimentos igual, sff")

	igual=0
	for i in range(len(a)):
		if a[i] == b[i]:
			igual+=1

	return igual/len(a) >= 0.9
"""


#10-funcao ord(char)

def cc_para_int(cc):


	res=0
	for e in cc:
		add=ord(e)
		res=res*1000+add

	return res





#11
"""
def reconhece(a):

	if (len(a))%2==0:
		if a[len(a)//2] != "c":
			return False

		a1=a[:(len(a)//2)]
		a2=a[(len(a)//2):]

	else:
		if a[len(a)//2] != "c":
			return False

		a1=a[:(len(a)//2)]
		a2=a[(len(a)//2)+1:]

	a3=""
	for e in a2:
		a3=e+a3
		#inversão de string

	accepted=("a","b","c")


	for i in range(len(a1)):
		if a1[i]!=a3[i]:
			return False
		if a1[i] not in	accepted:
			return False
		if i == 0 and a1[i]!="a":
			return False
		if i==len(a1)-1 and a1[i]=="a":
			return False

		if a1[i]=="b" and a1[i-1]=="c":
			return False

		if a1[i]=="c" and a1[i-1]=="a":
			return False

		if a1[i]=="a" and a1[i+1]=="c":
			return False

	return True
"""


#12
"""
def seq3(C1,C2):


	alfabeto=("a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z")

	if C1 not in alfabeto or C2 not in alfabeto:
		raise ValueError("Letras minúsculas,sff")
	i_1=0
	i_2=0
	c_escolhido=()

	for i in range(len(alfabeto)):
		if C1==alfabeto[i]:
			i_1==i
		if C2==alfabeto[i]:
			i_2=i
	if i_2<=i_1:
		raise ValueError("1º input tem de ser menor que o 2º")


	c_escolhido=alfabeto[i_1:i_2+1]
	print(c_escolhido)

	n_comb=0 #para saber o n de combinações/verificar correção da coisa
	for e in c_escolhido:
		for f in c_escolhido:
			for g in c_escolhido:
				print(e+f+g)
				n_comb+=1
	print(n_comb)
"""

#13
"""
def seq_racaman(n):

	res=()

	for i in range(n):
		if i==0:
			e=0
		elif res[i-1]>i and (res[i-1]-i) not in res:
			e=res[i-1]-i
		else:
			e=res[i-1]+i
		res=res+(e,)
	return res
"""


#14-funcao chr(n)
"""
def int_para_cc(n):

	res=''

	while n > 0:
		char= chr(n%1000)
		res= char+res
		n= n//1000
	return res
"""
#15
"""
def reconhece(str):

	if str[0] != "c":
		return False
	if str[-1] != "r":
		return False

	for e in str[1:-1]:
		if e != "a" and e!= "d":
			return False
	return True
"""



#16a
"""
def codifica(a):

	res1=""
	res2=""
	for i in range(len(a)):
		if (i+1)%2==0: #porque a primeira posição é o 0
			res2+=a[i]
		else:
			res1+=a[i]
	return res1+res2
"""

#16b
"""
def descodifica(a):

	indice_1opar=round((len(a)+1)//2)


	res1=a[:(indice_1opar)]
	res2=a[(indice_1opar):]


	res=""
	for i in range(len(a)):  #a minha res tem de ter len=len(a)
		if ((i-1)%2)==0:
			e=res2[((i-1)//2)]
		elif ((i)%2)==0:
			e=res1[(i)//2]
		res+=e
	return res
"""
