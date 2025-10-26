#include "DocumentManager.h"

void DocumentManager::addDocument(std::string name, int id, int license_limit) {
    if (documents_.find(id) == documents_.end()) {
        documents_[id] = {name, id, license_limit, 0};
        name_to_id_[name] = id;
    }
}

void DocumentManager::addPatron(int patronID) {
    patrons_.insert(patronID);
}

int DocumentManager::search(const std::string& name) {
    if (name_to_id_.count(name)) {
        return name_to_id_.at(name); 
    }
    return 0; 
}

bool DocumentManager::borrowDocument(int docid, int patronID) {
    if (documents_.find(docid) == documents_.end() || patrons_.find(patronID) == patrons_.end()) {
        return false;
    }

    auto& doc = documents_.at(docid);

    if (doc.borrowed_count >= doc.license_limit) {
        return false;
    }

    if (borrowed_docs_.count(docid) && borrowed_docs_.at(docid).count(patronID)) {
        return false; 
    }

    doc.borrowed_count++;
    borrowed_docs_[docid].insert(patronID);
    return true;
}

void DocumentManager::returnDocument(int docid, int patronID) {
  if (documents_.find(docid) == documents_.end() || patrons_.find(patronID) == patrons_.end()) {
        return; 
    }

    if (borrowed_docs_.count(docid) && borrowed_docs_.at(docid).count(patronID)) {
        documents_.at(docid).borrowed_count--;
        borrowed_docs_.at(docid).erase(patronID);
    }
}
