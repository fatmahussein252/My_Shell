# This script prints the following:
# - The arguments stored for each command line
# - The new and old path for the move and copy commands

# set breakpont to get the arguments
break myshell.c:42
commands 1
    silent
    printf "myargc = %d\nmyargv:\n", myargc
    set $x=0
    while ($x < myargc)
	printf "%s\n",myargv[$x++]
    end
    continue
end

# Set breakpoints at the functions called for the internal commands

## break the move function when called
break mv

# When the breakpoint at mv is hit, watch pathes
commands 2
    silent
    printf "At function mv, watching the pathes...\n"
    continue 
end
break move.c:78
command 3
    silent
    printf "oldpath = %s\nnewpath = %s\n",srcpath,dispath
    continue
end

#################################
## break the cp function when called
break cp

# When the breakpoint at mv is hit, watch pathes
commands 4
    silent
    printf "At function cp, watching the pathes...\n"
    continue
end
break copy1.c:90
command 5
    silent
    printf "oldpath = %s\nnewpath = %s\n",srcpath,dispath
    continue
end
################################
## break the chdir function when called
break fcd

# When the breakpoint at chdir is hit, watch the new directory
commands 6
    silent
    printf "At function chdir, watching the the new directory...\n"
    continue
end
break chdir.c:22
command 7
    silent
    printf "new dir = %s\n",path
    continue
end


info breakpoints
# Run the program
run
bt
