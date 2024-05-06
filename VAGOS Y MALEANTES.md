NAME="CONTENT"; echo $NAME | cat -e
--------------  -------------------
..............  ...........  ......
	 <<<<<<<<<		 <<<<<
	 							++
jerarquia:
		lineas = ---------
		comandos = .......
		argumentos = <<<<<
		flags = ++++++++
		
char *imput = "NAME="CONTENT"; echo $NAME | cat -e"
>---->>
char *line1 = "NAME="CONTENT""
char *line2 = "echo $NAME | cat -e"
>---->>
char *comand1 =  "NAME="CONTENT""
SE EJECUTA comando1
/*Se mete a entorno bla bla bla*/
>---->>
char *command1 = "echo $NAME"
>---->> si hay pipe se redireciona command1 a command2
char *command2 = "cat -e"
SE EJECUTA comando1, comando2

--divide imput into N lineN
--expand
--divide lineN into comandN
--execute line1 to lineN
--if pipe redirect
repite


structuras:

(char **)line_sp = split(input)
while (line_sp[line])
	ft_movidas
return (0);

//function 1=
// (char **)line_sp = split(input)
//	NodoN->content = line_sp[N];
//
//function2
//	while (nodo)
//		haz cosas;

ft_movidas(char *line_sp[line])
{

}



OUTFILE E INFILE REGLAS:

Puede ir en cualquier orden (outfile comando infile || infile comando outfile)
> outfile
< infile

despues del infile/outfile simpre va el cmd a menos que el infile/outfile sea lo unico en la linea

