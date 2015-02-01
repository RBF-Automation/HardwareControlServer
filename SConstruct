# Tell SCons to create our build files in the 'build' directory
VariantDir('build', 'src', duplicate=0)


source_files = [
"Main.cpp",
"ServerSocket.cpp",
"Server.cpp",
"Socket.cpp",
"JsonControl.cpp"]

# Set our required libraries
libraries = ['pthread']
library_paths = ''

env = Environment(CPPPATH ='/rapidjson/include/rapidjson/')

# Set our g++ compiler flags
env.Append( CPPFLAGS=[ '-Wall', '-g','-std=c++0x', '-pthread'] )

env.Append(LINKFLAGS = ['-std=c++11', '-pthread'])

# Tell SCons the program to build
env.Program('run', source_files, LIBS = libraries, LIBPATH = library_paths)
