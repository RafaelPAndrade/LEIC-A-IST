


def c_l_mul(n):

	def aux(n,lista,termo):
		if termo==10:
			return lista
		else:
			return aux(n, lista+[n*termo], termo+1)

	if not isinstance(n,int):
		raise TypeError("Número inteiro")
	elif n<=0:
		raise ValueError("Número inteiro positivo")
		
	return aux(n,[],0)
