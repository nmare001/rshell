# Assignment 3
## In this project we wrote a program which would create an command shell called rshell. In this particular assignment we added piping, input redirection, and output redirection functionality.
### List of bugs
* can't take in echo arguments that come after connectors
* can't read in commands that come right after semicolons (ie date;ls will be 
* read as only command attempt)
* can't read in exit when it is linked with other commands
* doesnt accept parentheses with redirect
