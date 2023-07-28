# simple_shell

Learning Objectives.

At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

    General.
          Who designed and implemented the original Unix operating system.
          Who wrote the first version of the UNIX shell.
          Who invented the B programming language (the direct predecessor to the C programming language).
          Who is Ken Thompson.
          How does a shell work.
          What is a pid and a ppid.
          How to manipulate the environment of the current process.
          What is the difference between a function and a system call.
          How to create processes.
          What are the three prototypes of main.
          How does the shell use the PATH to find the programs.
          How to execute another program with the execve system call.
          How to suspend the execution of a process until one of its children terminates.
          What is EOF / “end-of-file”?.

Requirements.

General.

    Allowed editors: vi, vim, emacs
    All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
    All your files should end with a new line
    A README.md file, at the root of the folder of the project is mandatory
    Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
    Your shell should not have any memory leaks
    No more than 5 functions per file
    All your header files should be include guarded
    Use system calls only when you need to (why?)


    List of allowed functions and system calls
                          access (man 2 access)
                          chdir (man 2 chdir)
                          close (man 2 close)
                          closedir (man 3 closedir)
                          execve (man 2 execve)
                          exit (man 3 exit)
                          _exit (man 2 _exit)
                          fflush (man 3 fflush)
                          fork (man 2 fork)
                          free (man 3 free)
                          getcwd (man 3 getcwd)
                          getline (man 3 getline)
                          getpid (man 2 getpid)
                          isatty (man 3 isatty)
                          kill (man 2 kill)
                          malloc (man 3 malloc)
                          open (man 2 open)
                          opendir (man 3 opendir)
                          perror (man 3 perror)
                          read (man 2 read)
                          readdir (man 3 readdir)
                          signal (man 2 signal)
                          stat (__xstat) (man 2 stat)
                          lstat (__lxstat) (man 2 lstat)
                          fstat (__fxstat) (man 2 fstat)
                          strtok (man 3 strtok)
                          wait (man 2 wait)
                          waitpid (man 2 waitpid)
                          wait3 (man 2 wait3)
                          wait4 (man 2 wait4)
                          write (man 2 write)


Output

Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)
Example of error with sh:

    $ echo "qwerty" | /bin/sh
    /bin/sh: 1: qwerty: not found
    $ echo "qwerty" | /bin/../bin/sh
    /bin/../bin/sh: 1: qwerty: not found
    $
Same error with your program hsh:

      $ echo "qwerty" | ./hsh
      ./hsh: 1: qwerty: not found
      $ echo "qwerty" | ./././hsh
      ./././hsh: 1: qwerty: not found
      $

Compilation

Your shell will be compiled this way:

      gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Testing

Your shell should work like this in interactive mode:

      $ ./hsh
      ($) /bin/ls
      hsh main.c shell.c
      ($)
      ($) exit
      $

But also in non-interactive mode:

      $ echo "/bin/ls" | ./hsh
      hsh main.c shell.c test_ls_2
      $
      $ cat test_ls_2
      /bin/ls
      /bin/ls
      $
      $ cat test_ls_2 | ./hsh
      hsh main.c shell.c test_ls_2
      hsh main.c shell.c test_ls_2
      $

   GENERAL VIEW OF THE PROJECT.

A simple UNIX command interpreter written as part of the low-level programming and algorithm track at ALX.

Description 
Simple shell is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

Usage:
To invoke "shell(command)", compile all .c files in the repository and run the resulting executable:

    gcc *.c -o shell
    ./shell
    

"shell(command)" can be invoked both interactively and non-interactively and if invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:

    $ echo "echo 'hello'" | ./shell
    'hello'
    $
If "shell(command)" is invoked with standard input connected to a terminal (determined by isatty(3)), an interactive shell is opened. When executing interactively,  "shell(command)" hedisplays the prompt $  when it is ready to read a command.

Example:

    $./shell
    $
Alternatively, if command line arguments are supplied upon invocation, shellex treats the first argument as a file from which to read commands. The supplied file should contain one command per line.  "shell(command)" runs each of the commands contained in the file in order before exiting.

Example:

        $ cat test
        echo 'hello'
        $ ./shell test
        'hello'
        $
Environment 

Upon invocation,  "shell(command)" receives and copies the environment of the parent process in which it was executed. This environment is an array of name-value strings describing variables in the format NAME=VALUE. A few key environmental variables are:

HOME

The home directory of the current user and the default directory argument for the cd builtin command.

    $ echo "echo $HOME" | ./shell
    /home/vagrant
  
  PWD
  
The current working directory as set by the cd command.

    $ echo "echo $PWD" | ./shell
    /home/vagrant/ALX/simple_shell
    
  OLDPWD
  
The previous working directory as set by the cd command.

    $ echo "echo $OLDPWD" | ./shell
    /home/vagrant/ALX/printf

PATH

A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

    $ echo "echo $PATH" | ./shell
    /home/vagrant/.cargo/bin:/home/vagrant/.local/bin:/home/vagrant/.rbenv/plugins/ruby-build/bin:/home/vagrant/.rbenv/shims:/home/vagrant/.rbenv/bin:/home/vagrant/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/vagrant/.cargo/bin:/home/vagrant/workflow:/home/vagrant/.local/bin

Command Execution 

After receiving a command,  "shell(command)" tokenizes it into words using " " as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command.  "shell(command)" then proceeds with the following actions:

If the first character of the command is neither a slash (\) nor dot (.), the  "shell(command)" searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
If the first character of the command is none of a slash (\), dot (.), nor builtin, shellex searches each element of the PATH environmental variable for a directory containing an executable file by that name.
If the first character of the command is a slash (\) or dot (.) or either of the above searches was successful, the  "shell(command)" executes the named program with any remaining given arguments in a separate execution environment.

Exit Status 

"shell(command)" returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

If a command is not found, the return status is 127; if a command is found but is not executable, the return status is 126.

All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

Signals 

While running in interactive mode, shellex ignores the keyboard input Ctrl+c. Alternatively, an input of end-of-file (Ctrl+d) will exit the program.

User hits Ctrl+d in the third line.

    $ ./shell
    $ ^C
    $ ^C
    $

Variable Replacement\

 "shell(command)" interprets the $ character for variable replacement.

$ENV_VARIABLE

ENV_VARIABLE is substituted with its value.

Example:

    $ echo "echo $PWD" | ./shell
    /home/vagrant/ALX/simple_shell
   
  $?
    
? is substitued with the return value of the last program executed.

Example:

      $ echo "echo $?" | ./shell
      0
  
  $$
  
The second $ is substitued with the current process ID.

Example:
    
    $ echo "echo $$" | ./shell
    6494

Comments

 "shell(command)" ignores all words and characters preceeded by a # character on a line.

Example:

    $ echo "echo 'hello' #this will be ignored!" | ./shell
    'hello'

Operators

  "shell(command)"specially interprets the following operator characters:

; - Command separator

Commands separated by a ; are executed sequentially.

Example:

    $ echo "echo 'hello' ; echo 'world'" | ./shell
    'hello'
    'world'
  
  && - AND logical operator.
  
command1 && command2: command2 is executed if, and only if, command1 returns an exit status of zero.

Example:

    $ echo "error! && echo 'hello'" | ./shell
    ./shellex: 1: error!: not found
    $ echo "echo 'all good' && echo 'hello'" | ./shell
    'all good'
    'hello'
  
  || - OR logical operator.
    
command1 || command2: command2 is executed if, and only if, command1 returns a non-zero exit status.

Example:

    $ echo "error! || echo 'but still runs'" | ./shell
    ./shell: 1: error!: not found
    'but still runs'
The operators && and || have equal precedence, followed by ;.

"shell(command)" Builtin Commands.

cd

Usage: cd [DIRECTORY]
  Changes the current directory of the process to DIRECTORY.
  If no argument is given, the command is interpreted as cd $HOME.
  If the argument - is given, the command is interpreted as cd $OLDPWD and the pathname of the new working directory is printed to standad output.
  If the argument, -- is given, the command is interpreted as cd $OLDPWD but the pathname of the new working directory is not printed.
  The environment variables PWD and OLDPWD are updated after a change of directory.
  Example:

      $ ./shell
      $ pwd
      /home/vagrant/ALX/simple_shell
      $ cd ../
      $ pwd
      /home/vagrant/ALX
      $ cd -
      $ pwd
      /home/vagrant/ALX/simple_shell
alias
    Usage: alias [NAME[='VALUE'] ...]
    Handles aliases.
    alias: Prints a list of all aliases, one per line, in the form NAME='VALUE'.
    alias NAME [NAME2 ...]: Prints the aliases NAME, NAME2, etc. one per line, in the form NAME='VALUE'.
    alias NAME='VALUE' [...]: Defines an alias for each NAME whose VALUE is given. If name is already an alias, its value is replaced with VALUE.
    
Example:

$ ./shell
$ alias show=ls
$ show
AUTHORS            builtins_help_2.c  errors.c         linkedlist.c        shell.h       test
README.md          env_builtins.c     getline.c        locate.c            shellex
alias_builtins.c   environ.c          helper.c         main.c              split.c
builtin.c          err_msgs1.c        helpers_2.c      man_1_simple_shell  str_funcs1.c
builtins_help_1.c  err_msgs2.c        input_helpers.c  proc_file_comm.c    str_funcs2.c

exit.

Usage: exit [STATUS]
    Exits the shell.
    The STATUS argument is the integer used to exit the shell.
    If no argument is given, the command is interpreted as exit 0.
    Example:

      $ ./shell
      $ exit

env

  Usage: env
  Prints the current environment.
  Example:

      $ ./shell
      $ env
      NVM_DIR=/home/vagrant/.nvm
      ...

setenv

  Usage: setenv [VARIABLE] [VALUE]
  Initializes a new environment variable, or modifies an existing one.
  Upon failure, prints a message to stderr.
Example:

    $ ./shell
    $ setenv NAME KIM
    $ echo $NAME
    KIM

unsetenv

  Usage: unsetenv [VARIABLE]
  Removes an environmental variable.
  Upon failure, prints a message to stderr.
Example:

    $ ./shell
    $ setenv NAME KIM
    $ unsetenv NAME
    $ echo $NAME
    $

    AUTHORS
    1.AMAZIAH CHACHA.
    2.JACKSON NJOROGE.
