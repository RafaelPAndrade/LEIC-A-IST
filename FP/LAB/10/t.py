#Rafael P Andrade
#n 86503







def divide(input, n_char):
	
	f=open(input,'r', encoding='UTF-8')
	
	ficheiro_atual=0	#indica em que ficheiro vamos


	linha=f.readline()
	while linha!='':
		n_ficheiros= len(linha[:-1])//n_char	#quantos ficheiros vão precisar de ser criados
			
		for i in range (n_ficheiros+1):	
	
			g=open(input+str(i+ficheiro_atual), 'a', encoding='UTF-8')

			g.write( linha [ (n_char*i): (n_char*i) + n_char ] )
			
			g.close()
	
		ficheiro_atual+= n_ficheiros

		linha=f.readline()
