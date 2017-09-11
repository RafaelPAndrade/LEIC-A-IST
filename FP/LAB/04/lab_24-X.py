#Rafael Pestana de Andrade
#rafael.pestana.andrade@tecnico.ulisboa.pt


#coding:utf-8
#para fazer load de forma dinâmica dentro da shell do python, correr
# >>>exec(open("./lab_24-X.py").read())
#no diretório que contém o ficheiro

#Livro

#1)
def pertence(a,l):
	indice=len(l)-1
	while indice >=0:
		if a==l[indice]:
			return True
		indice-=1
	return False

#2)
def substitui(lst,velho,novo):
	for i in range(len(lst)):
		if lst[i]==velho:
			lst[i]=novo
	return lst


#3)

def posicoes_lista(l,a):
	res=[]
	for i in range(len(l)):
		if l[i]==a:
			res+=[i]
	return res

#4)

def parte(l,a):
	menores=[]
	maiores=[]

	for e in l:
		if e>=a:
			maiores+=[e]
		else:
			menores+=[e]
	return [menores, maiores]


#5)

def inverte(l):
	a=0
	b=len(l)-1
	while a<len(l)//2:
		l[a],l[b]=l[b],l[a]
		a+=1
		b-=1
	
	return l

