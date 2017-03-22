# coding: utf-8
# Here your code !

import sys
import re

'''
【使い方】
コマンドプロンプト:
python Preprocess.py [オプション] <入力ファイル >出力先
[オプション]の部分には
-e  改行を除去
-p  行の終端に句点がなければ、句点を挿入
-f  半角文字を全角文字に変換
-s  全角スペースを除去
-h  見出しを除去
-r  ルビを除去
-x  冒頭と末尾の本文でない部分を除去
-n  注を除去
-c  外字の含まれる文を除去
-b  「」（）の含まれる文を除去
のうち使いたいものを入力してください。(順不同)
またオプションの部分に
--aozora
と入力すると青空文庫向けのオプションが全部有効になります。
(つまり -e -s -h -r -x -n -c -b と指定するのと同じです)
--aozora はほかのオプションと併用可能です。
山月記でしか試してないので今後アップデートされる可能性は大いにあります。
例1 青空文庫の小説aozora.txtを整形してaozora-format.txtに出力
python Preprocess.py --aozora <aozora.txt >aozora-fotmar.txt
例2 input.txtの改行と全角スペースを除去し、句点を付加したものをoutput.txtに出力
python Preprocess.py -e -p -s
などなど。
'''


rmvrtrn='-e' in sys.argv    #改行を除去
appprd='-p' in sys.argv     #行の終端に句点がなければ、句点を挿入
rplhlf='-f' in sys.argv     #半角文字を全角文字に変換
rmvspc='-s' in sys.argv     #全角スペースを除去
rmvhead='-h' in sys.argv    #見出しを除去
rmvrby='-r' in sys.argv     #ルビを除去
rmvexpl='-x' in sys.argv    #冒頭と末尾の本文でない部分を除去
rmvnote='-n' in sys.argv    #注を除去
rmvbrk='-b' in sys.argv     #「」（）の含まれる文を除去
rmveudc='-c' in sys.argv    #外字の含まれる文を除去
extwords='-w' in sys.argv   #セリフ(「」『』内の文章)を抽出
#rpleudc='-d' in sys.argv    #未実装

if '--aozora' in sys.argv:
    rmvspc=True
    rmvhead=True
    rmvrtrn=True
    rmveudc=True
    rmvrby=True
    rmvexpl=True
    rmvnote=True
    rmvbrk=True

if '--extserif' in sys.argv:
    rmvrtrn=True
    rmvhead=True
    rmvrby=True
    rmvexpl=True
    rmvnote=True
    rmveudc=True
    extwords=True

#if rpleudc:
#    sys.stderr.write('Error:option -c is not available.')

reruby=re.compile(u'《.+?》')
rehead=re.compile(u'(.+?)［＃「\1」は.?見出し］')
reeudc=re.compile(u'(.*)((。|^).*?※［＃「.+?」.*?、.+?］.*?(。|$))')
renote=re.compile(u'［＃.+?］')
reexpl=re.compile(u'''\A.+?-------------------------------------------------------.+?-------------------------------------------------------(.+)底本：.+\Z''', re.M|re.S)
rebrk=[re.compile(u'(.*)((。|^).*?「.*?」.*?(。|$))'), re.compile(u'(.*)((。|^).*?（.*?）.*?(。|$))'),re.compile(u'(.*)((。|^).*?『.*?』.*?(。|$))')]
reserif=[re.compile(u'「.+?」'), re.compile(u'『.+?』')]

f=open(sys.argv[1])
g=open(sys.argv[2], "w")
hrcnt=0

for line in f:
    if hrcnt<2:
        continue
    if line.find(u'----------------------------------------------'):
        hrcnt+=1
    if line[:2]==u'底本':
        break
    #if rmvrtrn:
        #line=line.replace(u'\n',u'')
    if rmvhead:
        if rehead.search(line)!=None:
            continue
    if rmvspc:
        line=line.replace(u'　',u'')
    if rmveudc:
        while reeudc.search(line):
            #print u'before:',line.encode('utf-8')
            #print u'result:','\n'.join([s[1].encode('utf-8') for s in reeudc.findall(line)])
            line=reeudc.sub(u'\\1\\3', line,count=1)
            #print u'after:', line.encode('utf-8')
            #print''
        #while reeudc.search(line):
            #print u'before:',line.encode('utf-8')
            #print u'result:','\n'.join([s[1].encode('utf-8') for s in reeudc.findall(line)])
            #line=reeudc.sub(ur'\1\3', line,count=1)
            #print u'after:', line.encode('utf-8')
            #print''
    if rmvrby:
        line = reruby.sub(u'', line).replace(u'｜',u'')
    if rmvnote:
        line = renote.sub(u'',line)
    if rplhlf:
        line=convert(line, ZK, ZAC)
    if rmvbrk:
        for r in rebrk:
            while r.search(line):
                #print u'before:',line.encode('utf-8')
                #print u'result:','\n'.join([s[3].encode('utf-8') for s in r.findall(line)])
                line=r.sub(u'\\1\\3',line,count=1)
                #print u'after:', line.encode('utf-8')
                #print''
    if appprd:
        if len(line)==0:
            continue
        if line[-1]!=u'。':
            #print 'no period'
            line+=u'。'
    if extwords:
        tmpl=''
        for r in reserif:
            tmpl+='\n'.join(['\t'+s[1:-1] for s in r.findall(line)])
        tmpl+='\n' if tmpl!='' else ''
        line=tmpl
    g.write(line.encode('shift-jis'))