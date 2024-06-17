
#include "Processing_Tree.h"
#include "Similarity.h"
#include "HashFunc.h"
#include "SplayTree.h"
#include "LinearSearch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>
#include <vector>
#include <sstream>
#include <direct.h>
#include <filesystem>
#include <cstddef>
#include <chrono>


namespace fs = std::filesystem;

//////////////////////////////////////////////////////////////////////////////////////////////////////

// <����>

const char* rootPath = "C:\\Users\\dazzl"; // tree.txt ������ ����� ���� ��ġ(���� ���) �Է��ϼ���
const char* src = "C:\\Users\\dazzl\\Downloads"; // �ٿ�ε� ���� ��� �Է��ϼ���

vector<node> linearSearch(string Folder_Name); // ��ǥ ���� ����Ʈ(�̸� �ߺ�) ��ȯ
node parent(node child); // ���� ������ ��ȯ���ִ�
node select(vector<node> duplicate, string Folder_Name); // �ߺ��� ���� �߿��� ����
void moveFile(const char* fileName, const char* src, const char* dest);

//////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {

    /* tree.txt ���� �����ؼ� �Űܿ���*/
    /*--------------------------------------------------------------------------------------------------------------------------------*/

    char originalDir[_MAX_PATH];

    // ���� �۾� ���丮�� ���ɴϴ�.
    
    if (_getcwd(originalDir, _MAX_PATH) == nullptr) {
        std::cerr << "���� �۾� ���丮�� �����µ� �����߽��ϴ�." << std::endl;
        return 1;
    }

        const char* orginal = originalDir;

        // file.txt ������ �����մϴ�.
        string command = "tree /a > file.txt"; /* �͹̳� ��ɾ� */
        if (_chdir(rootPath) == 0) {

            system(command.c_str());

        }

        // ���� �۾� ���丮�� ���ư��ϴ�.
        if (_chdir(originalDir) != 0) {
            std::cerr << "���� �۾� ���丮�� ���ƿ��µ� �����߽��ϴ�." << std::endl;
            return 1;
        }
    
        /*--------------------------------------------------------------------------------------------------------------------------------*/

    std::string path = "file.txt";
    std::string Current_Path = "current.txt";
    std::string line;


    // file.txt ���� �Űܿ��� & current.txt�� ������ ����
    /*--------------------------------------------------------------------------------------------------------------------------------*/

     moveFile(path.c_str(), rootPath, originalDir); // file.txt ���� �۾� ���丮�� �Űܿ���

    // ���� ��� ��Ʈ�� ��ü ���� �� ���� ����
    ofstream currentTXT("current.txt");

    // ������ ���������� ���ȴ��� Ȯ��
    if (!currentTXT) {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
        return 1;
    }

    // ���Ͽ� ���ڿ� ����
    currentTXT << rootPath;

    // ���� �ݱ�
    currentTXT.close();

    /*--------------------------------------------------------------------------------------------------------------------------------*/

    
        std::ifstream START(Current_Path);
        if (!START) {
            std::cout << "������ �� �� �����ϴ�." << std::endl;
            return 1;
        }
        getline(START, start_directory);
        START.close();

        std::cout << start_directory << std::endl;

        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cout << "������ �� �� �����ϴ�." << std::endl;
            return 1;
        }

        int index = 0;
        while (getline(inputFile, line)) {
            index++;
            if (index == 1 || index == 2)
                continue;
            ProcessingLine(line);
        }
        inputFile.close();

        std::cout << endl;
        std::cout << "�̵���ų ���� �Է� : ";
        std::string fileName;
        std::cin >> fileName;
        const char* fileToMove = fileName.c_str();

        std::cout << "��ǥ ���� �Է� : ";
        string target;
        std::cin >> target;
        std::cout << std::endl;
    

    
    auto start = std::chrono::high_resolution_clock::now(); // ���� �ð� ���� 


    /*--------------------------------------------------------------------------------------------------------------------------------*/
    // 01. HashMap
    
        HashFunc HashMap;
        for (const auto& item : Folder_List)
            HashMap.insert(item.Folder_Name, item.path);

        HashMap.searchAllPaths(target);
        vector<node> Result = HashMap.getResult();
    

        /*--------------------------------------------------------------------------------------------------------------------------------*/
    // 02. Linear Search
    //vector<node> Result(linearSearch(target));

    /*--------------------------------------------------------------------------------------------------------------------------------*/
    // 03. Binary Search Tree
    //{
    //    vector<node> Result;
    //    hash<string> hash_fn;
    //    SplayTree tree;
    //    splay* root = NULL;
    //    for (auto item : Folder_List)
    //    {
    //        root = tree.Insert(hash_fn(item.Folder_Name), root, item);
    //    }
    //    KEY_TYPE hashValue = hash_fn(target);
    //    root = tree.Search(hashValue, root);
    //    if (root && root->key == hashValue)
    //    {

    //        for (node n : root->items)
    //        {
    //            // cout << "folder name: " << n.Folder_Name << " Path: " << n.path << endl;
    //            Result.push_back(n);
    //        }
    //    }
    //    else
    //        cout << "File doesn't exist" << endl;
    //}
    /*--------------------------------------------------------------------------------------------------------------------------------*/


    // Similarity ����
    
        string File_Name = "";
        Similarity sim(Result, File_Name);
        sim.MakeOrder();
        priority_queue<node> final_result = sim.getResult();
        vector<node> Real_Result;
        while (!final_result.empty()) {
            Real_Result.push_back(final_result.top());
            final_result.pop();
        }
    
    
    auto end = std::chrono::high_resolution_clock::now(); // �Ϸ� �ð� ����


    /*--------------------------------------------------------------------------------------------------------------------------------*/
    cout << "�ߺ� ���� ���� : " << Result.size() << endl;

    node dest = select(Real_Result, target); // �̸��� �ߺ��Ǵ� ���� �߿� ����
    cout << "Ÿ�� ������ ��� -> " << dest.path << endl; // ���� ���� ��� ���

    moveFile(fileToMove, src, dest.path.c_str()); // ���� �̵�

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;

}


node select(vector<node> duplicates, string Folder_Name) {

    int i = 1;

    cout << "[���� ���� ���]" << endl;
    for (const auto& d : duplicates) {
        // node p = parent(d);
        node p = d;
        cout << i++ << ": " << p.Folder_Name << endl;
        cout << "-> path : " << p.path << endl << endl;
    }
    cout << endl;

    cout << "��ȣ �Է� : ";
    int input;
    cin >> input;

    node temp;
    temp = duplicates[input - 1];

    return temp;

}
void moveFile(const char* fileName, const char* src, const char* dest) {

    // ���� ���� ���
    fs::path source(string(src) + "\\" + string(fileName));
    // ��� ���� ���
    fs::path destination(string(dest) + "\\" + string(fileName));

    try {
        // ���� �̵�
        fs::rename(source, destination);
        std::cout << "������ ���������� �Ű���ϴ�." << std::endl;
    }
    catch (fs::filesystem_error& e) {
        std::cerr << "������ �ű�µ� �����߽��ϴ�: " << e.what() << std::endl;
    }

}
