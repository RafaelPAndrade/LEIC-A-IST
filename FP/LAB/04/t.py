#Rafael Pestana de Andrade
#rafael.pestana.andrade@tecnico.ulisboa.pt



#coding:utf-8
#para fazer load de forma dinâmica dentro da shell do python, correr
# >>>exec(open("./t.py").read())
#no diretório que contém o ficheiro


def dupla_lista(l):
	res=[]

	for e in l:
		res+=[e]*2

	return res
