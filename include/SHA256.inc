/* SHA-256 - cryptographic hash function
 *
 * Implemented by dwd222
 * designed by the National Security Agency
 * and published in 2001 by the NIST as a U.S. Federal Information Processing Standard
 *
 * This file is provided as is (no warranties).
 */

#define SHA256(%0) SHA_256(%0)
#define SHA2(%0) SHA_256(%0)
#define SHA_2(%0) SHA_256(%0)

stock powerint(val, n)
{
	if (n == 0) return 1;
	new w = val;
	for (new i = 1; i < n; i++)
		w = w*val;
	return w;
}

stock UINT8NaBity(c)
{
	new str[] = "00000000";
	new i = strlen(str) - 1;
	while(c)
	{
	    str[i] = (c%2) + 48;
	    c = c/2;
		i--;
	}
	return str;
}

stock UINT64NaBity(c)
{
	new str[] = "0000000000000000000000000000000000000000000000000000000000000000";
	new i = strlen(str) - 1;
	while(c)
	{
	    str[i] = (c%2) + 48;
	    c = c/2;
		i--;
	}
	return str;
}

stock BityNaUINT32(str[])
{
	new wynik = 0, j, fx = 0;
	new len = strlen(str);
	if (len > 32) len = 32;
	j = len - 1;
	while (str[j] && j > -1)
	{
	    wynik += (str[j--] - 48) * powerint(2, fx);
	    fx++;
	}
	return wynik;
}

stock TextNaBity(text[], bittext[], len)
{
	new i = 0, n = 0;
	while (text[i] && n < len)
	{
	    new j = 0;
	    new tmp[9];
		tmp = UINT8NaBity(text[i++]);
		while (tmp[j]) bittext[n++] = tmp[j++];
	}
	bittext[n] = '\0';
	return n;
}

stock TextNaBityCnt(text[])
{
	new i = 0, n = 0;
	while (text[i])
	{
	    new j = 0;
	    new tmp[9];
		tmp = UINT8NaBity(text[i++]);
		while (tmp[j])
		{
			n++;
			j++;
		}
	}
	return n;
}

stock RotateRight(value, rot)
{
	return (value >>> rot) | (value << (32 - rot));
}

stock SHA_256(str[])
{
    new H[] =  {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	new k[] =  {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
				0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
				0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
				0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
				0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
				0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
				0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
				0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

 	new it, length = TextNaBityCnt(str);
	length++;
	while ((length%512) != 448)
	    length++;
	length += 64;
	it = (length/512);
	
	for (new n = 0; n < it; n++)
	{
	    new sha_256[128*4+1], s0, s1, w[64] = 0;
	 	new len = TextNaBity(str[n*64], sha_256, 512);
		if (len < 512)
		{
			new plen = strlen(str)*8;
			sha_256[len++] = '1';

			while ((len%512) != 448)
			    sha_256[len++] = '0';
			{
				new tmp[65];
				tmp = UINT64NaBity(plen);
				new i = 0;
				while (tmp[i])
			 		sha_256[len++] = tmp[i++];
  				sha_256[len] = '\0';
			}
		}

  		new a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
 		{
			new j = 32;
			for (new x = 0; x < 16; x++)
  				w[x] = BityNaUINT32(sha_256[(j*x)]);

			for (new i = 16; i <= 63; i++)
			{
			    s0 = RotateRight(w[i - 15], 7)^RotateRight(w[i - 15], 18)^(w[i - 15] >>> 3);
			    s1 = RotateRight(w[i - 2], 17)^RotateRight(w[i - 2], 19)^(w[i - 2] >>> 10);
			    w[i] = (w[i - 16] + s0 + w[i - 7] + s1)&0xffffffff;
			}
		}
		for (new i = 0; i < 64; i++)
		{
		    s0 = RotateRight(a, 2)^RotateRight(a, 13)^RotateRight(a, 22);
		    new maj = (a&b)^(a&c)^(b&c);
		    new t2 = s0 + maj;
		    s1 = RotateRight(e, 6)^RotateRight(e, 11)^RotateRight(e, 25);
		    new ch = (e&f)^((~e)&g);
		    new t1 = h + s1 + ch + k[i] + w[i];
		    h = g;
		    g = f;
		    f = e;
		    e = (d + t1)&0xffffffff;
		    d = c;
		    c = b;
		    b = a;
		    a = (t1 + t2)&0xffffffff;
		}

		H[0] = (H[0] + a)&0xffffffff;
		H[1] = (H[1] + b)&0xffffffff;
		H[2] = (H[2] + c)&0xffffffff;
		H[3] = (H[3] + d)&0xffffffff;
		H[4] = (H[4] + e)&0xffffffff;
		H[5] = (H[5] + f)&0xffffffff;
		H[6] = (H[6] + g)&0xffffffff;
		H[7] = (H[7] + h)&0xffffffff;
	}

	new ret[65];
	{
	    new HTemp[8]; HTemp = H;
		new z = sizeof(ret) - 2;
		for (new i = 7; i >= 0; i--)
		{
			new j = 0;
			while (j < 8)
		    {
				new mod = HTemp[i]&0xf;
				ret[z--] = (mod<10?(mod+'0'):(mod+'a'-10));
				HTemp[i] >>>= 4;
				j++;
		    }
		}
	}
	ret[sizeof(ret) - 1] = '\0';
	return ret;
}
