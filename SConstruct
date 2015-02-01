# Tell SCons to create our build files in the 'build' directory
VariantDir('build', 'src', duplicate=0)


source_files = [
"Main.cpp",
"ServerSocket.cpp",
"Server.cpp",
"Socket.cpp",
"JsonControl.cpp",
"NodeHandler.cpp"]

# Set our required libraries
libraries = ['pthread', 'librf24-bcm']
library_paths = '/RF24/RPi/RF24/'

env = Environment(CPPPATH =['/rapidjson/include/rapidjson/','/RF24/RPi/RF24/'])

# Set our g++ compiler flags
env.Append( CPPFLAGS=[ '-Wall', '-g','-std=c++0x', '-pthread'] )

env.Append(LINKFLAGS = ['-std=c++11', '-pthread'])

# Tell SCons the program to build
env.Program('run', source_files, LIBS = libraries, LIBPATH = library_paths)
