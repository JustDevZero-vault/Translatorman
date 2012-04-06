Translatorman: Utility for translating or just writing, manpages into other languages.

Fuzzy instructions for compiling right now (while the code is in young state):

0. Create a folder named Proyectos
1. Download the code with a clone or tar.gz.
2. Create an outside folder, named Translatorman-build
3. Change to Translatorman-build (cd Translatorman-build)
4. Do the cmake magic. (cmake ../Translatorman/builds/CMake/)
5. Run make command. (make)
6. Go to qt4 folder. (cd qt4/)
7. Run translatormanqt4 (./translatormanqt4)
8. Try to open any manual page.




Observations:

While my objective is to do a crossplataform project ATM it will only work on GNU/Linux.
