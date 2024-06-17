#include "LinearSearch.h"
#include "Processing_Tree.h"
#include <vector>

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////

// ����Ž��
vector<node> linearSearch(string Folder_Name) {

    vector<node> duplicates; // �̸� �ߺ� ���� ������ ����

    for (const auto& folder : Folder_List) { // Ÿ�� ������ �̸��� ���� �������� ã��

        if (folder.Folder_Name.compare(Folder_Name) == 0)
            duplicates.push_back(folder);
    }

    // cout << "�ߺ� ���� ���� : " << duplicates.size() << endl;

    return duplicates;

}

// ���� ���� ��ȯ�ϴ� �Լ�
//node parent(node child) {
//
//    string childName = child.Folder_Name;
//    string childPath = child.path;
//
//    string parentName, parentPath;
//
//    // �ڽ� ��θ� '\' �� �����ڷ� �и�
//    istringstream iss(childPath);
//    string token;
//    vector<string> tokens;
//    while (getline(iss, token, '\\')) {
//        tokens.push_back(token);
//    }
//
//    // cout << "�ڽ� ���� ��� ��ū" << endl;
//    // for (const auto& t : tokens) {
//    //     cout << t << endl;
//    // }
//
//    if (tokens.size() >= 2) {
//        ostringstream oss;
//        for (size_t i = 0; i < tokens.size() - 1; ++i) {
//            oss << tokens[i] << "\\";
//        }
//        parentPath = oss.str();
//    }
//    else {
//        // ��� ���ڿ��� ��ȿ�� ������ ���� ��� �� ���ڿ� ��ȯ
//        parentPath = "";
//    }
//
//    // cout << "������� ��� : " << parentPath << endl;
//
//    tokens.pop_back();
//    if (!tokens.empty()) {
//        parentName = tokens.back();
//    }
//    else {
//        // ��� ���ڿ��� ��ȿ�� ������ ���� ��� �� ���ڿ� ��ȯ
//        parentName = "";
//    }
//
//    node temp;
//    temp.Folder_Name = parentName;
//    temp.path = parentPath;
//
//    return temp;
//
//}