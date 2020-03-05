#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
template <typename T>
void push_verts(vector<vector<T>> vec, ofstream &os)
{
    int i = 1;
    for (auto vf : vec)
    {
        for (auto f : vf)
        {

            os << f << endl;
            os << (i < vec.size() * vf.size() ? "," : "");
            i++;
        }
    }
}
int main(int argc, char *argv[])
{
    vector<vector<float>> verts;
    vector<vector<float>> normals;
    vector<vector<int>> faces;

    ifstream ifs;
    ofstream of;
    cout << argc << endl;
    if (argc >= 2)
    {
        string filename = argv[1];
        string out_name = "";
        if (argc == 3)
        {
            out_name = argv[2];
        }
        ifs.open(filename);
        if (ifs.is_open())
        {
            string ln;
            while (getline(ifs, ln))
            {
                istringstream iss(ln);
                string frst_word = "";
                iss >> frst_word;
                if (frst_word == "v")
                {
                    vector<float> vertex;
                    do
                    {
                        string word = "";

                        iss >> word;
                        if (word != "v" && !word.empty())
                        {
                            vertex.push_back(stof(word));
                        }

                    } while (iss);
                    verts.push_back(vertex);
                }
                else if (frst_word == "vn")
                {
                    vector<float> normal;
                    do
                    {
                        string word = "";

                        iss >> word;
                        if (word != "vn" && !word.empty())
                        {
                            normal.push_back(stof(word));
                        }

                    } while (iss);
                    normals.push_back(normal);
                }
                else if (frst_word == "f")
                {
                    vector<int> face;
                    do
                    {
                        string word = "";

                        iss >> word;
                        if (word != "f" && !word.empty())
                        {
                            stringstream face_ss;
                            for (char c : word)
                            {
                                if (c != '/')
                                    face_ss << c;
                                else
                                {
                                    break;
                                }
                            }
                            face.push_back(stoi(face_ss.str()));
                        }

                    } while (iss);
                    faces.push_back(face);
                }
            }
            of.open((out_name.empty() ? filename : out_name) + ".json");
            if (of.is_open())
            {
                of << "{\"meshes\":{\"plane\":{"
                   << "\"vertices\":[";
                push_verts(verts, of);
                of << "]," << endl;
                of << "\"normals\":[" << endl;
                push_verts(normals, of);
                of << "]," << endl;
                of << "\"faces\":[" << endl;
                push_verts(faces, of);
                of << "]" << endl;
                of << "}" << endl
                   << "}" << endl
                   << "}" << endl;
            }
        }
        else
        {
            cout << "Could not open file" << endl;
        }
    }
    else
    {
        cout << "No path specified. The format is\n objson -obj file path [optional] -output json file name" << endl;
    }
}
