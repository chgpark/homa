def calu(n, timeStam):
	arrT = []
	maxn = 0
	for tmp in timeStam:
		ptime = tmp[0]
		arrT.append(tmp[1])
		arrT = [elem for elem in arrT if elem >= ptime]
		k = len(arrT)
		if maxn < k:
			maxn = k
	return(maxn - n)
tarr = [[0, 3],[1, 2],[1, 4]]
print(calu(1, tarr))