value,_ =  [int(tmp) for tmp in input().strip().split(' ')]
coins = [int(tmp) for tmp in input().strip().split(' ')]

ways = [0]*(value+1)

for coin in coins:
    if coin > value:
        continue 
    ways[coin]+=1
    
    for i in range(coin+1,value+1):
        ways[i] += ways[i-coin]

print(ways[value])

