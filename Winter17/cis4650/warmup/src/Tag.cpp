#include "sgml.h"

class Tag {
        tag_t tagType;
        string value;
    public:
        Tag ( string value );
        tag_t getTagType();
        string getValue();
    private:
        void NormaliseTag();
        void DetermineTagType();
}

Tag::Tag(string value) {
    this.value = value;
    NormaliseTag();
    DetermineTagType();
}

void Tag::NormaliseTag() {
    int i;
    int start = 0, end = 0;
    transform(value.begin(), value.end(), value.begin(), ::toupper);
    for (i = 0; i < value.length(); i++ ) {
        if ( start == 0 && isalnum(value.at(i)) != 0 ) {

        } else if ( start != 0 && end == 0 && isalnum(value.at(i)) == 0 ) {
            end = i;
            break;
        }
    }
    value = value.substr( start, end-start );
}

void Tag::DetermineTagType() {
    if ( this.value.compare("TEXT") == 0 ) {
        this.tagType = TEXT;
    } else if ( this.value.compare("DATE") == 0 ) {
        this.tagType = DATE;
    } else if ( this.value.compare("DOC") == 0 ) {
        this.tagType = DOC;
    } else if ( this.value.compare("DOCNO") == 0 ) {
        this.tagType = DOCNO;
    } else if ( this.value.compare("HEADLINE") == 0 ) {
        this.tagType = HEADLINE;
    } else if ( this.value.compare("LENGTH") == 0 ) {
        this.tagType = LENGTH;
    } else if ( this.value.compare("P") == 0 ) {
        this.tagType = P;
    } else {
        this.tagType = IRRELEVANT;
    }
}

tag_t Tag::getTagType() {
    return tagType;
}

string Tag::getValue() {
    return value
}
