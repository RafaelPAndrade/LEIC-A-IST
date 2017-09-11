r_0_0=[[0,1,2,3,4],[15,16,17,18,5],[14,23,34,19,6],[13,22,21,20,7],[12,11,10,9, 8]]
r_4_0=[[4,5,6,7,8],[ 3,18,19,20,9],[2,17,24,21,10],[1,16,23,22,11],[0,15,14,13,12]]


def index(s,pos):
	def espelho_linhas(lst):
		"""
		Pega numa chave e inverte cada linha, mantendo a sua ordem na chave
		"""
		res=[]
		for linha in lst:
			linha_res= linha[::-1]
			res+= [linha_res]
		return res

	def espelho_colunas(lst):
		"""
		Pega numa chave e inverte a ordem das linhas na chave
		"""
		res=[]
		for linha in lst:
			res= [linha]+res
		return res

	def linha_pos(p):
		"""
		-Seletor da componente 'linha' do tipo abstrato posicao

		Input:
		-p: um elemento do tipo posicao

		Output:
		-Valor numerico entre 0 e 4 correspondente ao componente 'linha' de <p> 
		
		Funcoes externas ao Python usadas: --
		
		"""
		return  p[0]

	def coluna_pos(p):
		"""
		-Seletor da componente 'coluna' do tipo abstrato posicao

		Input:
		-p: um elemento do tipo posicao

		Output:
		-Valor numerico entre 0 e 4 correspondente ao componente 'coluna' de <p> 

		Funcoes externas ao Python usadas: --

		"""
		return p[1]





	if s=='r':
		if coluna_pos(pos)==0:
			if linha_pos(pos)== 0:
				#'r', (0,0)
				chave=r_0_0
			else:
				#'r', (4,0)
				chave=r_4_0			
		else:
			if linha_pos(pos)==4:
				#'r', (4,4)
				chave=espelho_linhas(espelho_colunas(r_0_0))
			else:
				#'r', (4,0)
				chave=espelho_linhas(espelho_colunas(r_4_0))
	elif s=='c':
		if coluna_pos(pos)==4:
			if linha_pos(pos)==0:
				#'c', (0,4)
				chave= espelho_linhas(r_0_0)
			else:
				#'c', (4,4)
				chave= espelho_linhas(r_4_0)
		else:
			if linha_pos(pos)==4:
				#'c',(4,0)
				chave= espelho_colunas(r_0_0)
			else:
				#'c',(0,0)
				chave= espelho_colunas(r_4_0)

	return chave