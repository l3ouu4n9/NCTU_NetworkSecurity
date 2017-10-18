from fractions import gcd
from Crypto.PublicKey import RSA

def modulo_multiplicative_inverse(A, M):
   
    x = 0
    old_x = 1
    y = 1
    old_y = 0
    gcd = M
    old_gcd = A

    while gcd != 0:
        quotient = old_gcd / gcd
        
        old_gcd, gcd = gcd, old_gcd - quotient * gcd
        old_x, x = x, old_x - quotient * x
        old_y, y = y, old_y - quotient * y

    x = old_x

    if x < 0:
        x += M
    return x


keys = []
for i in range(1, 13):
	for j in range(i + 1, 13):
		file1 = 'publicKeys/public%s.pub' % i
		file2 = 'publicKeys/public%s.pub' % j
		f1 = open(file1, 'r')
		key1 = RSA.importKey(f1.read())
		f1.close()
		f2 = open(file2, 'r')
		key2 = RSA.importKey(f2.read())
		f2.close()
		
		p = gcd(key1.n, key2.n)
		if p != 1:
			keys.append(key1)
			keys.append(key2)
			
			for k in range(2):
				q = keys[k].n / p
				r = (p - 1) * (q - 1)
				d = modulo_multiplicative_inverse(keys[k].e, r)
				print d
				private_key = RSA.construct((keys[k].n, keys[k].e, d, p, q))

				if k == 0:
					exportfile = 'private%s.pem' % i
				else:
					exportfile = 'private%s.pem' % j
					
				f = open(exportfile, 'w')
				f.write(private_key.exportKey('PEM'))
				f.close()

			