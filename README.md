# My_Shell
## The fshell

Welcome to the fshell! This shell is a lightweight, user-friendly command-line interpreter inspired by the Bash shell. It supports a range of built-in commands and can execute external commands using standard UNIX system calls.

### Features

- **Built-in Commands:** 
  - `fpwd` - print the current working directory
  - `fecho` - print a user input string
  - `fcp` - copy contents of file to another (exist or created) file
  - `fmv` - move file from directory to another (or the same directory with different name)
  - `fcd` - change the current directory
  - `ftype` - return the type of the command (internal, external or unsupported command)
  - `fenv` - print all the environment variables
  - `fexit` - Exit the fshell
  - `fhelp` - print all the supported internal commands with a brief info about each one

- **External Command Execution:**
  - Supports executing external commands using `fork` and `execvp`
  - Searches for executables in directories specified by the `PATH` environment variable

### How It Works

1. **Internal Commands:** The shell has a set of built-in commands that are implemented directly within the shell. These commands are handled internally without creating a new process.

2. **External Commands:** For commands not recognized as internal, the shell searches for the executable in the directories listed in the `PATH` environment variable. If found, it uses `fork` to create a new process and `execvp` to execute the command.

3. **Command Parsing:** The shell parses the user input to identify the command and its arguments, determining whether the command is internal or external.

### Usage

  To run the shell, compile the source code and execute the resulting binary:

```sh
gcc myshell.c -o exe
./exe
```
Once the shell is running, you can enter internal commands or external as you would in a standard Bash shell.
For example:
```
> fcd /path/to/directory
> ls
> fhelp
> fexit
```
### Sample Output

Below is a sample output demonstrating the usage and interface of the fshell:
![image](https://github.com/user-attachments/assets/ae6edeec-02ff-4542-8784-75b361af38e1)
