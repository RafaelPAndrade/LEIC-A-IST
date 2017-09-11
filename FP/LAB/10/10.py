#Rafael PAndrade
#Leic-a 2016/17 1o semestre
#
#Exercicio semanal n. 10


#1)

def conta_linhas(file):

	f=open(file, 'r', encoding='UTF-8')
	count = 0
	linha = f.readline()
	while linha != '':
		if linha != '\n':
			count += 1
		linha=f.readline()

	f.close()
	return count

#2)

def conta_vogais(file):

	f = open(file, 'r', encoding='UTF-8')
	res = {'a':0, 'e':0, 'i':0, 'o':0, 'u':0}

	linha = f.readline()
	while linha != '':
		for char in linha:
			if char in res:
				res[char] += 1
		linha = f.readline()

	f.close()
	return res

#3)

def inverte_linhas(input,output):

	f=open(input, 'r', encoding='UTF-8')
	g=open(output, 'w', encoding='UTF-8')

	#deve ser isto feito?
	linhas = f.readlines()
	linhas = linhas[::-1]
	for l in linhas:
		g.write(l)
	g.close()
	f.close()

#4)

def concatena(lista_input, output):

	g=open(output, 'w', encoding='UTF-8')

	for file in lista_input:
		f=open(file, 'r', encoding='UTF-8')

		linha=f.readline()
		while linha != '':
			print(linha, file=g, end='')
			linha=f.readline()
		f.close()

	g.close()



#5)

def procura(search, target_file):

	def lista_palavras(str):
	#de uma linha, obtem todas as palavras separadas por ' '

		"""def aux(alvo, lista, palavra):
			if alvo=="" or alvo== '\n':
				if palavra=='':
					return lista
				else:
					return lista+[palavra]
			elif alvo[0]!=' ':
				return aux(alvo[1:], lista, palavra+alvo[0])
			elif alvo[0]==' ':
				return aux(alvo[1:], lista+[palavra], '')"""

		#return aux(str, [], '')
		return str.split(sep=" ") #Para a proxima, ler os docs...
		#Nao funciona com <search> com espacos

	f=open(target_file, 'r', encoding='UTF-8')

	linha=f.readline()
	while linha!='':
		palavras=lista_palavras(linha)
		if search in palavras:
			print(linha, end='')
		linha=f.readline()

	f.close()

#6)

def corta(input, target, n_char):

	f=open(input, 'r', encoding='UTF-8')
	g=open(target,'w', encoding='UTF-8')

	while n_char>0:	#impede coisas parvas
		linha=f.readline()
		for letra in linha:
			if n_char == 0:
				break
			else:
				print(letra, end='', file=g)
				n_char -= 1
	f.close()
	g.close()

#7)
#usando semana 5, ordenacao nao destrutiva por borbulhamento (bubblesort)
def ordena_ficheiro(input):

	def ordena(lst):
		tabela = []
		for i in range(len(lst)):
			tabela += [i]


		maior=len(lst)

		trocou=True

		while trocou:
			trocou = False
			for i in range(maior-1):
				if lst[tabela[i]]>lst[tabela[i+1]]:
					trocou = True
					tabela[i],tabela[i+1] = tabela[i+1],tabela[i]

			maior-=1
		return tabela

	f=open(input, 'r', encoding='UTF-8')
	linhas=f.readlines()
	ordem=ordena(linhas)


	for i in ordem:
		print(linhas[i], end='')

	f.close()

#8)

def junta_ordenados(input1, input2, target):

	def ordena(lst):
		tabela = []
		for i in range(len(lst)):
			tabela += [i]


		maior=len(lst)

		trocou=True

		while trocou:
			trocou = False
			for i in range(maior-1):
				if eval(lst[tabela[i]])>eval(lst[tabela[i+1]]):
					trocou = True
					tabela[i],tabela[i+1] = tabela[i+1],tabela[i]

			maior-=1
		return tabela

	f=open(input1, 'r', encoding='UTF-8')
	g=open(input2, 'r', encoding='UTF-8')
	h=open(target, 'w', encoding='UTF-8')


	nums = f.readlines()
	nums+= g.readlines()
	nums_order = ordena(nums)

	for i in nums_order:
			h.write(nums[i])

	h.close()
	g.close()
	f.close()



#9)

def divide(input, n_char):

	f=open(input,     'r', encoding='UTF-8')
	g=open(input+'0', 'w', encoding='UTF-8')
	h=open(input+'1', 'w', encoding='UTF-8')


	linha=f.readline()
	while linha!='':
		if len(linha[:-1])<=n_char:
			g.write(linha)
		else:
			g.write(linha[:n_char])

