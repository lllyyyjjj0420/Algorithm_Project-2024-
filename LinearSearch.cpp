#include "LinearSearch.h"
#include "Processing_Tree.h"
#include <vector>

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////

// 순차탐색
vector<node> linearSearch(string Folder_Name) {

    vector<node> duplicates; // 이름 중복 폴더 관리할 벡터

    for (const auto& folder : Folder_List) { // 타겟 폴더와 이름이 같은 폴더들을 찾기

        if (folder.Folder_Name.compare(Folder_Name) == 0)
            duplicates.push_back(folder);
    }

    // cout << "중복 폴더 개수 : " << duplicates.size() << endl;

    return duplicates;

}

// 상위 폴더 반환하는 함수
//node parent(node child) {
//
//    string childName = child.Folder_Name;
//    string childPath = child.path;
//
//    string parentName, parentPath;
//
//    // 자식 경로를 '\' 를 구분자로 분리
//    istringstream iss(childPath);
//    string token;
//    vector<string> tokens;
//    while (getline(iss, token, '\\')) {
//        tokens.push_back(token);
//    }
//
//    // cout << "자식 폴더 경로 토큰" << endl;
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
//        // 경로 문자열에 유효한 폴더가 없을 경우 빈 문자열 반환
//        parentPath = "";
//    }
//
//    // cout << "만들어진 경로 : " << parentPath << endl;
//
//    tokens.pop_back();
//    if (!tokens.empty()) {
//        parentName = tokens.back();
//    }
//    else {
//        // 경로 문자열에 유효한 폴더가 없을 경우 빈 문자열 반환
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