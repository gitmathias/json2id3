#include <getopt.h>
#include <iostream>
#include <fstream>
using namespace std;

/* TagLib */
#include <aifffile.h>
#include <id3v2header.h>
#include <tag.h>
#include <fileref.h>
#include <tbytevector.h>

/* LibJson */
#include <json/json.h>


static struct option long_options[] = {
    {"help",  no_argument,       0, 'h'},
    {"file",  required_argument, 0, 'f'},
    {"tags",  required_argument, 0, 't'},
    {0, 0, 0, 0}
};

string read_file(string file_name)
{
    ifstream input(file_name.c_str());
    string line;
    string contents;
    if (input.is_open()) {
        while (input.good()) {
            getline(input, line);
            contents += line;
        }
        input.close();
    } else {
        cerr << "File not found: " << file_name << endl;
    }
    return contents;
}

void usage(char **argv)
{
    cerr << "Usage: ./" << *argv << " -h --help -f --file [file] -t --tags [file]" << endl;
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
    int return_code;
    int option_index = 0;
    string file_name;
    string tag_file;

    while(42) {
        return_code = getopt_long(argc, argv, "hf:o:a:", long_options, 
                        &option_index);
        if(return_code == -1)
            break;

        switch(return_code) {
            case 'h': /* --help */
                usage(argv);
                return 0;
            case 'f': /* --file*/
                cout << "Tagging file: " << optarg << endl;
                file_name = optarg;
                break;
            case 't': /* --file*/
                cout << "Using tag file: " << optarg << endl;
                tag_file = optarg;
                break;
            default: /* ??? */
                usage(argv);
                return 1;
        }
    }

    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;

    //string json_tags = read_file(tag_file);
	//json::Value *v = json::parse(json_tags);
	//json::Object *obj = dynamic_cast<json::Object *>(v);

    //for (json::Object::const_iterator i = obj->begin(); i != obj->end(); ++i) {
        //if (i.key() == "tags") {
            //json::Object tags_obj = dynamic_cast<const json::Object &>(i.value());
            //for (json::Object::const_iterator j = tags_obj.begin(); j != tags_obj.end(); ++j) {
                //if (j->type() == json::TYPE_STRING) {
                    //string tag_value = j.key() + " => " + dynamic_cast<const json::String &>(*j).value();
                    //cout << tag_value << endl;
                //}
            //}
        //}
        //cout << i.key() << endl;
    //}


    TagLib::FileRef f(file_name.c_str());
    f.tag()->setAlbum("Album");
    f.tag()->setArtist("Foobar");
    f.save();

    return 0;
}