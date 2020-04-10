# This MakeFile has solely
# been created to be used by Unix users, or users whose system is based on Unix
# Now Windows compilers may automatically add .exe behind the created executable
# however Make will then not see that the executable exists... 
# (Not that it really matters due to the simplicity of this particular project)
#
# If you use Visual Studio, this file will be ignored! VS will follow its
# own course!

ubin/tbfc: ubin src/TBFC.cpp
	g++ -o ubin/tbfc src/TBFC.cpp

ubin:
	mkdir ubin
