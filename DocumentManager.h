#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

struct Document {
    std::string name;
    int id;
    int license_limit;
    int borrowed_count;
};

class DocumentManager {
public:
    void addDocument(std::string name, int id, int license_limit);

    void addPatron(int patronID);

    int search(const std::string& name);

    bool borrowDocument(int docid, int patronID);

    void returnDocument(int docid, int patronID);

private:
    std::unordered_map<int, Document> documents_;

    std::unordered_map<std::string, int> name_to_id_;

    std::unordered_set<int> patrons_;

    std::unordered_map<int, std::unordered_set<int>> borrowed_docs_;
};

#endif // DOCUMENT_MANAGER_H
