myshell: TRASH - Designed by Siddhu and Surya  
Designed in C++

1. cd,pwd and exit work in background mode too with an addition of "&" at the end of the command.
2. "@" is the prompt.
3. "cd\n", "cd ~" will take you to home directory.
4. signals (SIGINT,SIGTSTP) work just as in the bash shell, using CTRL+C or CTRL+Z will kill the child if any.
5. For executing an executable add "./" in front the file name.
6. For executing an executable in the background, add "./" in front and add "&" at the end of the file name.
7. Input redirection and output redirection can be used through <<< and >>> respectively in between the file names.
8. myshell only supports input redirection or output redirection, it also supports combination of the both.
9. pipelining can be done between multiple processes with the help of "||" in between every two executables (processes). eg ./1 || ./2 or ./1 || ./2 || ./3 etc
10. myshell supports the following combinations of redirection and pipeline:
11. myshell supports input redirection to the first process of a pipeline and/or output redirection to the last file of the pipeline.