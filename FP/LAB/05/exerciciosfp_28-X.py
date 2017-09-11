#coding:utf-8


#1

def soma_digitos_pares(num):
    if num==0:
        return 0
    elif (num%10)%2==0:
        return (num%10)+soma_digitos_pares(num//10)
    else:
        return soma_digitos_pares(num//10)


#2

def apenas_digitos_impares(num):
    if num==0:
        return num
    elif (num%10)%2!=0:
        return num%10+10*apenas_digitos_impares(num//10)
    else:
        return apenas_digitos_impares(num//10)


#3

def sublistas(lst):
    if lst==[]:
        return 0
    elif isinstance(lst[0],list):
        return 1+sublistas(lst[0])+sublistas(lst[1:])
    else:
        return sublistas(lst[1:])


#4

def soma_n_vezes(a,b,n):
    if n==0:
        return b
    else:
        return a+soma_n_vezes(a,b,n-1)


#5

def troca_occ_lista(lst,a,b):
    if lst==[]:
        return []
    elif lst[0]== a:
        return [b]+troca_occ_lista(lst[1:],a,b)
    else:
        return [lst[0]]+troca_occ_lista(lst[1:],a,b)


#6

def inverte(lst):
    if lst==[]:
        return []
    else:
        return inverte(lst[1:])+[lst[0]]



#7

def pertence(lst,a):
    if lst==[]:
        return False
    elif lst[0]==a:
        return True
    else:
        return pertence(lst[1:],a)


#8-usando in

def subtrai(lst1,lst2):
    if lst1==[]:
        return []
    elif lst1[0] in lst2:
        return subtrai(lst1[1:],lst2)
    else:
        return [lst1[0]]+subtrai(lst1[1:],lst2)



#8-usando a função pertence

def subtrai(lst1,lst2):
	if lst1==[]:
		return []
	elif pertence(lst2,lst1[0]):
		return subtrai(lst1[1:],lst2)
	else:
		return [lst1[0]]+subtrai(lst1[1:],lst2)





#9

def parte(lst,a):
	def menores(lst,a):
		if lst==[]:
			return []
		elif lst[0]<a:
			return [lst[0]]+menores(lst[1:],a)
		else:
			return menores(lst[1:],a)
	def maiores(lst,a):
		if lst==[]:
			return []
		elif lst[0]>=a:
			return [lst[0]]+maiores(lst[1:],a)
		else:
			return maiores(lst[1:],a)


	if lst==[]:
		return []
	else:
		return [menores(lst,a),maiores(lst,a)]


#10

def maior(lst):
	def maior_aux(lst,a):
		if lst==[]:
			return a
		elif a>lst[0]:
			return maior_aux(lst[1:],a)
		else:
			return maior_aux(lst[1:],lst[0])

	if len(lst)==0:
		raise ValueError("Não pode ser vazio")
	else:
		return maior_aux(lst[1:],lst[0])
