#Livro-31-X


#1-já foi feito

#2



def inverte_digitos(num):
	if num< 10:
		return num
	else:
		return (num%10)*10+inverte_digitos(num//10)
