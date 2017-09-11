def triangular(n):
	soma=0
	m=0
	if n==0:
		return False
	else:
		while soma < n:
			m+=1
			soma += m
		
		return soma==n
