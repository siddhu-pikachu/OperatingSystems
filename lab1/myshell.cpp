#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
using namespace std;
int pd;
void my_ls()
{
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        DIR *mydir;
        struct dirent *myfile;
        mydir = opendir(cwd);
        while ((myfile = readdir(mydir)) != NULL)
        {
                string temp = myfile->d_name;
                write(1, temp.c_str(), temp.length());
                write(1, "\t", 1);
        }
        closedir(mydir);
}
void handleint(int num)
{
        write(STDOUT_FILENO, "interrupting the process!\n", 26);
        // exit(0); (doubt)
}
void handletstp(int num)
{
        write(STDOUT_FILENO, "stop the process!\n", 18);
        // exit(0); (doubt)
}
void handlechld(int num)
{
        if (pd != 1)
        {
                write(STDOUT_FILENO, "\nchild has ended!", 17);
                write(2, "\n@ ", 3);
        }
}
void my_pwd()
{
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL) // getcwd will store the current working directory in cwd
        {
                // write(1, arg.c_str(), sizeof(arg));
                write(2, "getcwd() error!\n", 16);
        }
        else
        {
                string temp = cwd;
                write(1, "path to current dir: ", 21);
                write(1, temp.c_str(), temp.length());
        }
}
void my_pwdand()
{
        int pid = fork();
        if (pid == 0)
        {
                my_pwd();
                exit(0);
        }
}
void my_cd(string arg)
{
        char cwd[1024];
        if (chdir(arg.c_str()) != 0)
        {
                write(2, arg.c_str(), arg.length());
                write(2, " doesnot exist!", 15);
        }
        else
        {
                if (getcwd(cwd, sizeof(cwd)) == NULL)
                {
                        write(2, "getcwd() error!\n", 16);
                }
                else
                {
                        string temp = cwd;
                        write(1, temp.c_str(), temp.length());
                }
        }
        write(1, "\n@ ", 3);
}
void my_cdand(string arg)
{
        int pid = fork();
        if (pid == 0)
        {
                my_cd(arg);
                exit(0);
        }
        write(1, "\n@ ", 3);
}
bool parse(string &arg1, char cmd[], int rc)
{
        char cwd[1024] = "";
        getcwd(cwd, sizeof(cwd));
        arg1 = cwd;
        arg1 += '/';
        if (cmd[rc - 2] != '&')
        {
                for (int i = 0; i < rc - 1; i++)
                {
                        arg1 += cmd[i];
                }
                return false;
        }
        else
        {
                for (int i = 0; i < rc - 2; i++)
                {
                        arg1 += cmd[i];
                }
                return true;
        }
}
void my_fork(vector<string> redarg)
{
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
        }
        else if (pid == 0)
        {
                int er = execlp(redarg[0].c_str(), redarg[0].c_str(), (char *)NULL);
                if (er == -1) // execlp returns -1 if the exec failed
                {
                        write(2, "exec() failed", 13);
                        exit(1);
                }
        }
        else
        {
                wait(0);
                //else{
                //        if(kll==1){
                //                char cnt[100];
                //                int rcnt = read(0, cnt, sizeof(cnt));
                //                //write(1,"hell",4);
                //                string tp = cnt;
                //                //cout<<tp;
                //                if(tp=="ayo\n") kill(pid_pcs, SIGCONT);
                //        }
                //}
        }
        write(1, "\n@ ", 3);
        return;
}
void my_forkbgrnd(vector<string> redarg)
{
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
        }
        else if (pid == 0)
        {
                int er = execlp(redarg[0].c_str(), redarg[0].c_str(), (char *)NULL);
                if (er == -1)
                {
                        write(2, "exec() failed", 13);
                        exit(1);
                }
        }
        write(1, "\n@ ", 3);
        return;
}
void my_fork_outredir(vector<string> redarg, bool bgrnd)
{
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
                exit(1);
        }
        else if (pid == 0)
        {
                close(1);
                int fd1 = open(redarg[1].c_str(), O_WRONLY | O_TRUNC | O_CREAT);
                if (fd1 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                int er = execlp(redarg[0].c_str(), redarg[0].c_str(), (char *)NULL);
                close(fd1);
                open("/dev/fd/1", O_WRONLY);
                if (er == -1)
                {
                        write(2, "exec() failed", 13);
                        exit(1);
                }
        }
        else
        {
                if (!bgrnd)
                {
                        wait(0);
                }
        }
        write(1, "\n@ ", 3);
        return;
}
void my_fork_inredir(vector<string> redarg, bool bgrnd)
{
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
        }
        else if (pid == 0)
        {
                close(0);
                int fd1 = open(redarg[1].c_str(), O_RDONLY);
                if (fd1 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                int er = execlp(redarg[0].c_str(), redarg[0].c_str(), (char *)NULL);
                close(fd1);
                open("/dev/fd/0", O_RDONLY);
                if (er == -1)
                {
                        write(2, "exec() failed", 13);
                        exit(1);
                }
        }
        else
        {
                if (!bgrnd)
                {
                        wait(0);
                }
        }
        write(1, "\n@ ", 3);
        return;
}
void my_fork_outandredir(vector<string> redarg, bool bgrnd)
{
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
                exit(1);
        }
        else if (pid == 0)
        {
                int fd1 = open(redarg[1].c_str(), O_WRONLY);
                dup2(fd1, 1); // duping stdout
                dup2(fd1, 2); // duping stderr
                if (fd1 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                int er = execlp(redarg[0].c_str(), redarg[0].c_str(), (char *)NULL);
                if (er == -1)
                {
                        write(2, "exec() failed", 13);
                        exit(1);
                }
                close(fd1);
        }
        else
        {
                if (!bgrnd)
                {
                        wait(0);
                }
        }
        write(1, "\n@ ", 3);
        return;
}
void my_pipe(vector<string> redarg, bool bgrnd)
{
        pd = 1;
        int nop = redarg.size(); // number of processes = number of pipes-1
        int pipefd[nop][2];      // number of pipes*2 = numbers of pipe ends
        for (int i = 0; i < nop; i++)
        {
                if (i != nop - 1)
                {
                        if (pipe(pipefd[i]) < 0) // creating the ith pipe for i-1th and ith process
                        {
                                write(2, "pipe() failed", 13);
                                return;
                        }
                }
                if (fork() == 0)
                {
                        if (i != 0)
                        {
                                dup2(pipefd[i - 1][0], 0); // taking the i-1th process's input to stdin for the ith process
                                close(pipefd[i - 1][1]);
                                close(pipefd[i - 1][0]);
                        }
                        if (i != nop - 1)
                        {
                                dup2(pipefd[i][1], 1); // sending the ith process out put (from stdout) to ith pipe
                                close(pipefd[i][0]);
                                close(pipefd[i][1]);
                        }
                        int er = execlp(redarg[i].c_str(), (char *)NULL);
                        write(2, "exec() failed", 13);
                        exit(1);
                }
                if (i != 0)
                {
                        close(pipefd[i - 1][0]); // closing the pipes in the parent process
                        close(pipefd[i - 1][1]);
                }
                if (!bgrnd)
                { // we will wait if we are not running it in background
                        wait(NULL);
                }
        }
        return;
}
void my_inpipe(vector<string> redarg, bool bgrnd)
{
        pd = 1;
        string infile;
        infile = redarg[1];
        redarg.erase((redarg.begin() + 1));
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
        }
        else if (pid == 0)
        {
                close(0);
                int fd1 = open(infile.c_str(), O_RDONLY); // close stdin and open input file in its place
                if (fd1 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                my_pipe(redarg, bgrnd);
                close(fd1);                  // close input file
                open("/dev/fd/0", O_RDONLY); // reopen the stdin
                exit(0);
        }
        else
        {
                if (!bgrnd)
                {
                        wait(0);
                }
        }
        return;
}
void my_outpipe(vector<string> redarg, bool bgrnd)
{
        pd = 1;
        string outfile;
        outfile = redarg[(redarg.size() - 1)];
        redarg.pop_back();
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
        }
        else if (pid == 0)
        {
                close(1);
                int fd1 = open(outfile.c_str(), O_WRONLY); // close stdout and open output file in its place
                if (fd1 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                my_pipe(redarg, bgrnd);
                close(fd1);                  // close output file
                open("/dev/fd/1", O_WRONLY); // reopen the stdout
                exit(0);
        }
        else
        {
                if (!bgrnd)
                {
                        wait(0);
                }
        }
        return;
}
void my_inandoutpipe(vector<string> redarg, bool bgrnd)
{
        pd = 1;
        string infile;
        infile = redarg[1];
        string outfile;
        outfile = redarg[(redarg.size() - 1)];
        redarg.pop_back();
        redarg.erase((redarg.begin() + 1));
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
        }
        else if (pid == 0)
        {
                close(0);
                int fd1 = open(infile.c_str(), O_RDONLY); // close stdin and open input file in its place
                if (fd1 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                close(1);
                int fd2 = open(outfile.c_str(), O_WRONLY); // close stdout and open output file in its place
                if (fd2 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                my_pipe(redarg, bgrnd);
                close(fd1);                  // close input file
                close(fd2);                  // close output file
                open("/dev/fd/0", O_RDONLY); // reopen the stdin
                open("/dev/fd/1", O_WRONLY); // reopen the stdout
                exit(0);
        }
        else
        {
                if (!bgrnd)
                {
                        wait(0);
                }
        }
        return;
}
void my_inandoutredir(vector<string> redarg, bool bgrnd, bool one)
{
        string infile;
        string outfile;
        if (!one)
        {
                infile = redarg[1];
                outfile = redarg[2];
        }
        else
        {
                infile = redarg[2];
                outfile = redarg[1];
        }
        pid_t pid = fork();
        if (pid < 0)
        {
                write(2, "fork() failed", 13);
        }
        else if (pid == 0)
        {
                close(0);
                int fd1 = open(infile.c_str(), O_RDONLY); // close stdin and open input file in its place
                if (fd1 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                close(1);
                int fd2 = open(outfile.c_str(), O_WRONLY); // close stdout and open output file in its place
                if (fd2 == -1)
                {
                        write(2, "open() failed", 13);
                        exit(1);
                }
                int er = execlp(redarg[0].c_str(), redarg[0].c_str(), (char *)NULL);
                close(fd1);                  // close input file
                close(fd2);                  // close output file
                open("/dev/fd/0", O_RDONLY); // reopen the stdin
                open("/dev/fd/1", O_WRONLY); // reopen the stdout
        }
        else
        {
                if (!bgrnd)
                {
                        wait(0);
                }
        }
        return;
}
int main()
{
        pd = 0;
        signal(SIGINT, handleint);
        signal(SIGTSTP, handletstp);
        signal(SIGCHLD, handlechld);
        write(1, "\nYOUR CURRENT SHELL IS TRASH \n ", 32);
        write(1, "_                 _\n| |               | |\n| |_ _ __ __ _ ___| |__\n| __| '__/ _` / __| '_ \\ \n| |_| | | (_| \\__ \\ | | |\n \\__|_|  \\__,_|___/_| |_|", 144);
        write(1, "\n\n@ ", 4);
        while (1)
        {
                char cmd[100];
                int rc = read(0, cmd, sizeof(cmd));
                string arg = "";
                string arg1 = "";
                for (int i = 0; i < rc - 1; i++)
                {
                        arg += cmd[i];
                }
                string redir1 = "";
                bool redirflag = 0;
                char red = '@';
                vector<string> redarg; // vector to store the tokenised arguments
                vector<char> ops;
                bool cd_pwdbgnd = 0;
                for (int i = 0; i < rc - 1; i++) // the tokenising loop
                {
                        if (arg[rc - 2] == '&') // checking for if the instruction should be run in background
                        {
                                cd_pwdbgnd = 1;
                                redirflag = 1;
                                if (red == '@')
                                {
                                        red = '#';
                                }
                        }
                        if (arg[i] != ' ')
                        {
                                if (arg[i] == '>' || arg[i] == '<') // checking for redirection
                                {
                                        ops.push_back(arg[i]);
                                        redirflag = 1;
                                        if (arg[i + 3] != ' ')
                                        {
                                                redarg.push_back(redir1);
                                                redir1 = "";
                                                red = arg[i];
                                                i += 3;
                                        }
                                        else if (arg[i + 3] == ' ')
                                        {
                                                redarg.push_back(redir1);
                                                redir1 = "";
                                                red = arg[i];
                                                i += 4;
                                        }
                                }
                                else if (arg[i] == '|') // checking for pipelines
                                {
                                        ops.push_back(arg[i]);
                                        redirflag = 1;
                                        if (arg[i + 2] != ' ')
                                        {
                                                redarg.push_back(redir1);
                                                redir1 = "";
                                                red = '|';
                                                i += 2;
                                        }
                                        else if (arg[i + 2] == ' ')
                                        {
                                                redarg.push_back(redir1);
                                                redir1 = "";
                                                red = '|';
                                                i += 3;
                                        }
                                }
                                else if (arg[i] == '&' && arg[i + 1] == '>') // checking for error redirection
                                {
                                        ops.push_back('%');
                                        redirflag = 1;
                                        if (arg[i + 3] != ' ')
                                        {
                                                redarg.push_back(redir1);
                                                redir1 = "";
                                                red = '%';
                                                i += 3;
                                        }
                                        else if (arg[i + 3] == ' ')
                                        {
                                                redarg.push_back(redir1);
                                                redir1 = "";
                                                red = '%';
                                                i += 4;
                                        }
                                }
                                if (arg[i] != '&')
                                {
                                        redir1 += arg[i];
                                }
                        }
                        else
                        {
                                continue;
                        }
                }
                if (redir1 != "")
                {
                        redarg.push_back(redir1);
                        redir1 = "";
                }
                if (arg.substr(0, 4) == "exit" || (arg.substr(0, 4) == "exit" && cmd[4] == ' ')) // exiting the shell
                {
                        if (cd_pwdbgnd == 1)
                        {
                                int pid = fork();
                                if (pid == 0)
                                {
                                        write(2, "exited!\n", 8);
                                        exit(0);
                                }
                        }
                        else
                        {
                                write(2, "exited myshell!\n", 16);
                                exit(0);
                        }
                }
                else if (arg == "pwd" || arg == "pwd &" || arg == "pwd&") // code for pwd
                {

                        if (cd_pwdbgnd)
                                my_pwdand();
                        else
                                my_pwd();
                        write(1, "\n@ ", 3);
                }
                else if (cmd[0] == 'c' && cmd[1] == 'd' && (cmd[2] == '\n' || cmd[2] == ' ')) // code for cd
                {
                        arg = "";
                        string temp = redarg[0];
                        for (int i = 2; i < rc - 1; i++)
                        {
                                arg += temp[i];
                        }
                        if (cmd[2] == '\n' || cmd[3] == '~' || redarg[0] == "cd")
                        {
                                arg = getenv("HOME");
                        }
                        if (cd_pwdbgnd)
                        {
                                my_cdand(arg);
                        }
                        else
                        {
                                my_cd(arg);
                        }
                }
                else if (cmd[0] == 'l' && cmd[1] == 's' && cmd[2] == '\n') // code for ls
                {
                        my_ls();
                }
                else
                {
                        bool bgrnd = parse(arg1, cmd, rc); // checking if the process should be run in the background
                        if (redirflag == 0)                // normal fork
                        {
                                my_fork(redarg); // fn call for fork
                        }
                        else if (redirflag == 1)
                        {
                                if( ops.size() >= 2 && (ops[0] == '<'||ops[0] == '>'||ops[ops.size() - 1] == '>'||ops[ops.size() - 1] == '<')){
                                        if (ops[0] == '<' && ops[1] == '>')
                                        {
                                                my_inandoutredir(redarg, bgrnd, 0);
                                        }
                                        else if (ops[0] == '>' && ops[1] == '<')
                                        {
                                                my_inandoutredir(redarg, bgrnd, 1);
                                        }
                                        else if ((ops[0] == '<' && ops[1] == '|') || (ops[ops.size() - 2] == '|' && ops[ops.size() - 1] == '>'))
                                        {
                                                if (ops[0] == '<' && ops[1] == '|' && ops[ops.size() - 1] != '>') // only input redirection for the first process in pipes
                                                {
                                                        my_inpipe(redarg, bgrnd);
                                                        write(STDOUT_FILENO, "\nchildren have ended!", 21);
                                                        write(1, "\n@ ", 3);
                                                }
                                                else if (ops[0] != '<' && ops[ops.size() - 2] == '|' && ops[ops.size() - 1] == '>') // only output redirection for the last process in pipes
                                                {
                                                        my_outpipe(redarg, bgrnd);
                                                        write(STDOUT_FILENO, "\nchildren have ended!", 21);
                                                        write(1, "\n@ ", 3);
                                                }
                                                else if (ops[0] == '<' && ops[ops.size() - 2] == '|' && ops[ops.size() - 1] == '>')
                                                {
                                                        my_inandoutpipe(redarg, bgrnd);
                                                        write(STDOUT_FILENO, "\nchildren have ended!", 21);
                                                        write(1, "\n@ ", 3);
                                                }
                                                else if (ops[0] == '<' && ops[ops.size() - 2] == '|' && ops[ops.size() - 1] == '>')
                                                {
                                                        my_inandoutpipe(redarg, bgrnd);
                                                        write(STDOUT_FILENO, "\nchildren have ended!", 21);
                                                        write(1, "\n@ ", 3);
                                                }
                                                else
                                                {
                                                        cout << ops[ops.size() - 2] << "      " << ops[ops.size() - 1] << endl;
                                                        write(1, "command not foumd", 17);
                                                }
                                        }
                                }
                                else
                                {
                                        if (red == '>') // output redirection
                                        {
                                                my_fork_outredir(redarg, bgrnd);
                                        }
                                        else if (red == '<') // input redirection
                                        {
                                                my_fork_inredir(redarg, bgrnd);
                                        }
                                        else if (red == '|') // pipeline
                                        {
                                                my_pipe(redarg, bgrnd);
                                                write(STDOUT_FILENO, "\nchildren have ended!", 21);
                                                write(1, "\n@ ", 3);
                                        }
                                        else if (red == '%') // stdout and stderror redirection
                                        {
                                                my_fork_outandredir(redarg, bgrnd);
                                        }
                                        else if (red == '#') // background fork
                                        {
                                                my_forkbgrnd(redarg);
                                        }
                                        else
                                        {
                                                write(1, "command not found", 17);
                                        }
                                }
                        }
                }
                while (!redarg.empty())
                {
                        redarg.pop_back(); // clearing the vector for the next instruction
                }
        }
}