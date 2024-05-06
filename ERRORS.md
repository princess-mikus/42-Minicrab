<h1>ERROR MESSAGES TO DO</h1>

- [ ] Builtin Errors (Exit status == 1)
	- [ ] cd:
		- [ ] no such file or directory: $NAME (ENOENT)
		- [ ] not a directory: $NAME (ENOTDIR)
	- [ ] echo:
		- [ ] Genuinamente no se me ocurre como romper echo
	- [ ] pwd:
		- [ ] too many arguments (Maybe E2BIG?)
	- [ ] export:
		- [ ] Not technically an error but MAYBE we can use too many arguments?
	- [ ] unset:
		- [ ] not enough arguments
		- [ ] bad option: $OPTION (Technically every option is bad under our unset) (Maybe EINVAL?)
	- [ ] env: (Exit status == *)
		- [ ] no such file or directory: $NAME (ENOENT)
		- [ ] invalid option: -- $OPTION (Maybe EINVAL?)
	- [x] exit:
		- [x] It can't have errors
- [ ] Basic command integrity errors:
	- [ ] minicrab: command not found: $COMMAND
	- [ ] minicrab: parse error near '$CHARACTER'
		- [ ] For some reason on < > it gives the error on '\n'
	- [ ] minicrab: permission denied: $FILE
	- [ ] (BONUS) minicrab: no matches found: *


* = 
Exit status:
  125  if the env command itself fails
  126  if COMMAND is found but cannot be invoked
  127  if COMMAND cannot be found