#Rafael Pestana de Andrade
#nº86503


def inverte_dic(dic):
	res={}					#res-dicionario que vai ser retornado
	for chave in dic:			#<chave> = uma letra
		for num in dic[chave]:		#dic[<chave>] é uma lista de numeros
			if num not in res:	
				res[num]= [chave]	#cria a chave <num> com o valor [<chave>]
			else:
				res[num]+=[chave]	#adiciona ao valor associado a <num> o valor [<chave>]
				
	return res


