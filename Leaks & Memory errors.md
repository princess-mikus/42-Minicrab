- ls | cat -e | cat -e | wc -l > "ou"t "fi"le (Double free)
Valgrind trace = 
```
==25989== Invalid free() / delete / delete[] / realloc()
==25989==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==25989==    by 0x10E8D3: free_array (free.c:22)
==25989==    by 0x10CA7D: trim_blocks (line.c:82)
==25989==    by 0x10CB5E: get_blocks (line.c:101)
==25989==    by 0x10CBB0: make_line (line.c:113)
==25989==    by 0x10C4CE: clean_outfile (cleaning.c:139)
==25989==    by 0x10C681: cleaning (cleaning.c:168)
==25989==    by 0x10CC98: clean (parse_commands.c:22)
==25989==    by 0x10CD66: parse_commands (parse_commands.c:43)
==25989==    by 0x10B2A3: execute (main.c:33)
==25989==    by 0x10B36A: main (main.c:56)
==25989==  Address 0x4b66ae0 is 0 bytes inside a block of size 2 free'd
==25989==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==25989==    by 0x10CB4A: get_blocks (line.c:100)
==25989==    by 0x10CBB0: make_line (line.c:113)
==25989==    by 0x10C4CE: clean_outfile (cleaning.c:139)
==25989==    by 0x10C681: cleaning (cleaning.c:168)
==25989==    by 0x10CC98: clean (parse_commands.c:22)
==25989==    by 0x10CD66: parse_commands (parse_commands.c:43)
==25989==    by 0x10B2A3: execute (main.c:33)
==25989==    by 0x10B36A: main (main.c:56)
==25989==  Block was alloc'd at
==25989==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==25989==    by 0x10FD91: ft_strjoin (in /workspaces/42-Minicrab/minishell)
==25989==    by 0x10F0F8: line_cutter (strings.c:114)
==25989==    by 0x10C8F8: clear_line_v2 (line.c:55)
==25989==    by 0x10CB0B: get_blocks (line.c:96)
==25989==    by 0x10CBB0: make_line (line.c:113)
==25989==    by 0x10C4CE: clean_outfile (cleaning.c:139)
==25989==    by 0x10C681: cleaning (cleaning.c:168)
==25989==    by 0x10CC98: clean (parse_commands.c:22)
==25989==    by 0x10CD66: parse_commands (parse_commands.c:43)
==25989==    by 0x10B2A3: execute (main.c:33)
==25989==    by 0x10B36A: main (main.c:56)
```