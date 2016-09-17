
f=open("F:\\Programming\\Desktop\\cpp\\Bungo\\Bungo_2008\\aozora\\kokoro\\kokoroserif.txt", "r")
w=open("F:\\Programming\\Desktop\\cpp\\Bungo\\Bungo_2008\\aozora\\kokoro\\temp.txt", "w")
res=''
for (i, line) in enumerate([l.decode('shift-jis') for l in f]):
    res +=((u'a\t'+line) if line[0]!='#' else (u'\t'+line[1:]))

w.write(res.encode('shift-jis'))