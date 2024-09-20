/*
  @author: Blas - eLite (c) 2024
  @def File for working with files
  @copyright eLite (c) 2024
  @category file working
  @since 1.0
*/

#include "imports.cpp"

class FSRenameFileError : public std::exception {
    public:
char * what () {
        return "\u001B[31mFSRenameFileError Exception occured:\nAn error occured while renaming a file using File.rename() function.\u001B[0m";
    }
};

class File {
private:
    String filn = "";
    /*
    @def Function for creating a new file.
    @brief Make a new file.
    @example newf("file")
    @param filename Filename
    */
    fun newf(String filename) {
        ofstream f(filename);
        f << "";
        f.close();
    }
    /*
    @def Function for writing on a file.
    @brief Write on a file.
    @example writf("file", "Hello World!")
    @param filename Filename
    @param content Thing to write
    */
    template <typename T>
    fun writf(String filename, T content) {
        ofstream f(filename);
        f << content;
        f.close();
    }
    /*
    @def Read a file and return the content as a String.
    @brief Read a file.
    @example readf("file")
    @param filename Filename
    */
    String readf(String filename) {
        fstream f(filename);
        String ret = "", line = "";
        while(getline(f, line)) {
            ret += line + "\n";
        }
        return ret;
    }
    /*
    @def Function for appending something on a file.
    @brief Append a file.
    @example appendf("file", "Hello World!")
    @param filename Filename
    @param content Thing to append
    */
    template <typename T>
    fun appendf(String filename, T content) {
        String t = readf(filename);
        ofstream f(filename);
        f << t << content;
        f.close();
    }
    /*
    @def Function for reading only one line from the file.
    @brief Read a line from a file.
    @example readlif("file", 1)
    @param filename Filename
    @param li Line number for read
    */
    String readlif(String filename, int li) {
        int i = 0;
        fstream f(filename);
        String ret = "", line = "";
        while(getline(f, line)) {
            if(i == li) {
                return line;
            }
            i++;
        }
        return "";
    }

public: 
    File(String filename) {
        filn = filename;
    }
    function appendNewLine() {
        appendf(filn, "\n");
    }
    template <typename T>
    function write(T content) {
        writf(filn, content);
    }
    String read() {
        return readf(filn);
    }
    function createNewFile() {
        newf(filn);
    }
    String readLine(int line) {
        return readlif(filn, line);
    }
    fun rem() {
        remove(filn.c_str());
    }
    boolean compare(File of) {
        if(of.read() == this->read()) {
            return true;
        } else {
            return false;
        }
    }
    boolean exists() {
        ifstream f(filn.c_str());
        return f.good();
    }
    vector<String> readasv() {
        vector<String> ret;
        fstream f(filn.c_str());
        String line = "";
        while(getline(f, line)) {
            ret.push_back(line);
        }
        return ret;
    }
    size_t sizeb() {
        return this->read().size();
    }
    double sizemb() {
        size_t sizeInBytes = this->read().size();
        return static_cast<double>(sizeInBytes) / (1024 * 1024);
    }
    String concat(File of) {
        return this->read() + of.read();
    }
    fun move(String to) {
        // Construct full paths for source and destination files
        fs::path sourcePath = fs::current_path() / filn;
        fs::path destinationPath = fs::path(to) / filn;

        // Move the file
        try {
            fs::rename(sourcePath, destinationPath);
        } catch (const std::exception& e) {
            throw FSRenameFileError();
        }
    }
    fun rename(String nn) {
        fs::rename(filn, nn);
    }
};