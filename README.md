compilers_lab_02
================
This is the lexeme scanner and parser for subset of HTML, which describes with this grammatic productions:

1) <HTML> -> ‘<html’ <Parameters> ‘>’ <WebpageBody> ‘</html>’
2) <WebpageBody> -> <Head><Body> 
3) <Head> -> ‘<head’ <Parameters> ‘>’ <HeadItems> ‘</head>’
4) <Head> -> EMPTY
5) <HeadItems> -> <HeadItem><HeadItems> 
6) <HeadItems> -> EMPTY
7) <HeadItem> -> ‘<title’ <Parameters> ’>’ <Content> ‘</title>’ 
8) <HeadItem> -> ‘<meta’ <Parameters> ‘>’ 
9) <HeadItem> -> ‘<link <Parameters> ‘>’ 
10) <HeadItem> -> ‘<base <Parameters> ‘>’ 
11) <HeadItem> -> ‘<basefont’ <Parameters> ‘>’ 
12) <Body> -> ‘<body’ <Parameters> ‘>’ <Content> ‘</body>’ 
13) <Content> -> <Tag><Content> 
14) <Content> -> <Word><Content> 
15) <Content> -> EMPTY 
16) <Parameters> -> <Parameter><Parameters> 
17) <Parameters> -> EMPTY 
18) <Parameter> -> id ‘=‘ STRING 
19) <Parameter> -> id ‘=‘ COLOR 
20) <Parameter> -> id ‘=‘ id 
21) <Parameter> -> id ‘=‘ INT
22) <Parameter> -> id
23) <Parameter> -> STRING
24) <Tag> -> ‘<img’ <Parameters> ‘>’ 
25) <Tag> -> ‘<br <Parameters> ‘>’ 
26) <Tag> -> ‘<p <Parameters> ‘>’ 
27) <Tag> -> ‘<h1 <Parameters> ‘>’ <Content> ‘</h1>’ 
28) <Tag> -> ‘<h2 <Parameters> ‘>’ <Content> ‘</h2>’ 
29) <Tag> -> ‘<h3 <Parameters> ‘>’ <Content> ‘</h3>’ 
30) <Word> -> STRING 
