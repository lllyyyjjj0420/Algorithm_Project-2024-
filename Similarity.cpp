//
// Created by ���ر� on 24. 6. 16.
//

#include "Similarity.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void Similarity::MakeOrder()
{
    for(node& Folder_info : Duplicates)
    {
        CalculateSimilarity(Folder_info);
        Results.push(Folder_info);
    }
}

void Similarity::CalculateSimilarity(node& Folder_info)
{
    string Path = Folder_info.path;
    vector<directory> Folder_Split;
    double weight = 1.0;

    // ��θ� '/' ������ �и��Ͽ� ���Ϳ� ����
    vector<string> parts = splitStringByDelimiter(Path, '\\');

    // �� ��� ���ο� _ ������ �ܾ���� �и��Ͽ�, ���� ����� ���� ����ġ ����
    for (auto it = parts.rbegin(); it != parts.rend(); ++it) {
        vector<string> subparts = splitStringByDelimiter(*it, '_');
        for (const string& subpart : subparts) {
            directory dir;
            dir.weight = weight;
            dir.word = subpart;
            Folder_Split.push_back(dir);
        }
        weight = weight * 0.7;
    }


    // ������ ����ϰ�, Folder_info�� update.
    vector<string> File_Split = splitStringByDelimiter(Path, '_');

    double point = 0;
    for (directory dir : Folder_Split)
    {
        for ( string file : File_Split)
        {
            point += calculateTokenSimilarity(dir.word, file) * dir.weight;
        }
    }

    Folder_info.Similarity = point;
}

// '/' �������� ���ڿ��� �и��Ͽ� ���Ϳ� �����ϴ� �Լ�
vector<string> Similarity::splitStringByDelimiter(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);

    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
        //cout << token << endl;
    }

//    for ( string str : tokens)
//    {
//        cout << "word : " << str << endl;
//    }
    return tokens;
}
// �����Ÿ��� �̿��� �� string�� ���絵 ����
int Similarity::calculateLevenshteinDistance(const string& s1, const string& s2)
{
    const size_t len1 = s1.size(), len2 = s2.size();
    vector<vector<unsigned int>> d(len1 + 1, vector<unsigned int>(len2 + 1));

    d[0][0] = 0;
    for(size_t i = 1; i <= len1; ++i) d[i][0] = i;
    for(size_t i = 1; i <= len2; ++i) d[0][i] = i;

    for(size_t i = 1; i <= len1; ++i)
        for(size_t j = 1; j <= len2; ++j)
            d[i][j] = min({d[i-1][j] + 1
                           , d[i][j-1] + 1
                           , d[i-1][j-1] + (s1[i-1] == s2[i-1] ? 0 : 1)});

    return d[len1][len2];
}

double Similarity::calculateStringSimilarity(const string& token1, const string& token2)

{
    int distance = calculateLevenshteinDistance(token1, token2);
    int maxLen = max(token1.size(), token2.size());

    return 1.0 - (static_cast<double>(distance) / maxLen);
}

double Similarity::calculateTokenSimilarity(const string& token1, const string& token2) {
    return calculateStringSimilarity(token1, token2);
}

priority_queue<node> Similarity:: getResult()
{
    return Results;
}
